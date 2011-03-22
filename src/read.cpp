/**
 * Read from file saved events (format is extracted from extension):
 * ROOT or ProtoBuf
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <TFile.h>

#include "interface/PBInstructor.h"
#include "interface/PBProcessor.h"
#include "interface/RTProcessor.h"
#include "interface/Results.h"
#include "pb/Event.pb.h"

using namespace std;

namespace fs = boost::filesystem;
namespace po = boost::program_options;

typedef vector<string> Inputs;

int THREADS = 0;

int main(int argc, char *argv[])
try
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against
    //
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    po::options_description description("Allowed options");
    description.add_options()
        ("help", "produce help message")

        ("threads", po::value<int>(),
         "run N multi-threads (works only with ProtoBuf) [-1 for cores]")

        ("input,i", po::value<Inputs>(), "input file(s)")
    ;

    po::positional_options_description positional_options;
    positional_options.add("input", -1);

    po::variables_map arguments;
    po::store(po::command_line_parser(argc, argv).
            options(description).positional(positional_options).run(),
            arguments);

    if (2 > argc ||
        arguments.count("help") ||
        !arguments.count("input"))
    {
        cout << "Usage: " << argv[0] << " [Options] input(s)" << endl;
        cout << description << endl;

        return 1;
    }

    if (arguments.count("threads"))
        ::THREADS = arguments["threads"].as<int>();

    try
    {
        if (::THREADS)
        {
            Inputs inputs(arguments["input"].as<Inputs>());
            fs::path file_path(*inputs.begin());
            const string extension(fs::extension(file_path));

            if (".pb" != extension)
            {
                cout << "Usage: " << argv[0] << " [Options] input(s)" << endl;
                cout << description << endl;

                return 1;
            }

            boost::shared_ptr<pb::Instructor> instructor(new pb::Instructor(-1 == ::THREADS ? 0 : ::THREADS));
            instructor->processFiles(inputs);

            boost::shared_ptr<TFile> output(new TFile("out_pb_threads.root", "recreate"));
            if (!output->IsOpen())
            {
                cerr << "Failed to save results" << endl;

                return 1;
            }

            instructor->results()->save();
        }
        else
        {
            boost::shared_ptr<Processor> processor;
            string results_file;
            {
                fs::path file_path(argv[1]);
                const string extension(fs::extension(file_path));

                if (".pb" == extension)
                {
                    cout << "Read ProtoBuf" << endl;

                    results_file = "out_pb";

                    processor.reset(new pb::Processor());
                }
                else if (".root" == extension)
                {
                    cout << "Read ROOT Tree" << endl;

                    results_file = "out_rt";

                    processor.reset(new rt::Processor());
                }
                else
                {
                    cout << "Usage: " << argv[0] << " [Options] input(s)" << endl;
                    cout << description << endl;

                    return 1;
                }
            }

            Inputs inputs(arguments["input"].as<Inputs>());
            for(Inputs::const_iterator input = inputs.begin();
                inputs.end() != input;
                ++input)
            {
                fs::path file_path(*input);

                processor->init(file_path);
                processor->processEvents();
            }

            cout << "Processed events: "
                << processor->eventsRead() << endl;

            boost::shared_ptr<TFile> output(new TFile((results_file + ".root").c_str(), "recreate"));
            if (!output->IsOpen())
            {
                cerr << "Failed to save results" << endl;

                return 1;
            }

            processor->results()->save();
        }
    }
    catch(const exception &error)
    {
        cerr << "error: " << error.what() << endl;

        // Clean Up any memory allocated by libprotobuf
        //
        google::protobuf::ShutdownProtobufLibrary();

        return 1;
    }

    // Clean Up any memory allocated by libprotobuf
    //
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
catch(...)
{
    // Clean Up any memory allocated by libprotobuf
    //
    google::protobuf::ShutdownProtobufLibrary();

    cerr << "Unknown error" << endl;

    return 1;
}
