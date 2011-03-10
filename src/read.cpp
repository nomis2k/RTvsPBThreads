/**
 * Read from file saved events (format is extracted from extension):
 * ROOT or ProtoBuf
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <iostream>

#include <boost/filesystem.hpp>

#include "interface/PBProcessor.h"
#include "interface/RTProcessor.h"

using namespace std;

namespace fs = boost::filesystem;

void printUsage(const string &);

int main(int argc, char *argv[])
try
{
    if (2 != argc)
    {
        printUsage(argv[0]);

        return 1;
    }

    fs::path file_path(argv[1]);
    const string extension(fs::extension(file_path));

    try
    {
        boost::shared_ptr<Processor> processor;
        if (".pb" == extension)
        {
            cout << "Read ProtoBuf" << endl;

            processor.reset(new pb::Processor(file_path));
        }
        else if (".root" == extension)
        {
            cout << "Read ROOT Tree" << endl;

            processor.reset(new rt::Processor(file_path));
        }
        else
        {
            printUsage(argv[0]);

            return 1;
        }

        processor->processEvents();
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

void printUsage(const string &executable)
{
    cout << "Usage: " << executable << " input_file" << endl;
    cout << endl;
    cout << "Input file format will be selected depending on the exension:"
        << endl;
    cout << "  pb     ProtoBuf" << endl;
    cout << "  root   TTree" << endl;
    cout << endl;
}
