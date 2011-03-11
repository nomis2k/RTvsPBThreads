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

#include "interface/PBInstructor.h"
#include "interface/PBProcessor.h"
#include "interface/RTProcessor.h"

using namespace std;

namespace fs = boost::filesystem;
namespace po = boost::program_options;

typedef vector<string> Inputs;

int THREADS = 0;

int main(int argc, char *argv[])
try
{
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
        }
        else
        {
            boost::shared_ptr<Processor> processor;
            {
                fs::path file_path(argv[1]);
                const string extension(fs::extension(file_path));

                if (".pb" == extension)
                {
                    cout << "Read ProtoBuf" << endl;

                    processor.reset(new pb::Processor());
                }
                else if (".root" == extension)
                {
                    cout << "Read ROOT Tree" << endl;

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
        }
    }
    catch(const exception &error)
    {
        cerr << "error: " << error.what() << endl;

        return 1;
    }

    return 0;
}
catch(...)
{
    cerr << "Unknown error" << endl;
}
