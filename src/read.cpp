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
    if (2 > argc)
    {
        printUsage(argv[0]);

        return 1;
    }

    try
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
                printUsage(argv[0]);

                return 1;
            }
        }

        for(int arg = 1; argc > arg; ++arg)
        {
            fs::path file_path(argv[arg]);

            processor->init(file_path);
            processor->processEvents();
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

void printUsage(const string &executable)
{
    cout << "Usage: " << executable << " inputs" << endl;
    cout << endl;
    cout << "Inputs should be space separated" << endl;
    cout << endl;
}
