/**
 * Generate fixed number of events and save in specified format:
 * ROOT or ProtoBuf
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include "interface/PBGenerator.h"
#include "interface/RTGenerator.h"

using namespace std;

namespace fs = boost::filesystem;
using boost::lexical_cast;

void printUsage(const string &);

uint32_t MAX_EVENTS = 10000;
uint32_t MAX_JETS = 10;

int main(int argc, char *argv[])
try
{
    if (2 > argc)
    {
        printUsage(argv[0]);

        return 1;
    }

    fs::path file_path(argv[1]);
    const string extension(fs::extension(file_path));

    if (2 < argc)
        ::MAX_EVENTS = lexical_cast<uint32_t>(argv[2]);

    try
    {
        boost::shared_ptr<Generator> generator;
        if (".pb" == extension)
        {
            cout << "Generate ProtoBuf" << endl;

            generator.reset(new pb::Generator(file_path));
        }
        else if (".root" == extension)
        {
            cout << "Generate ROOT Tree" << endl;

            generator.reset(new rt::Generator(file_path));
        }
        else
        {
            printUsage(argv[0]);

            return 1;
        }

        generator->generateEvents(::MAX_EVENTS, ::MAX_JETS);
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
    cout << "Usage: " << executable << " output_file [events]" << endl;
    cout << endl;
    cout << "Output format will be selected depending on the exension:"
        << endl;
    cout << "  pb     ProtoBuf" << endl;
    cout << "  root   TTree" << endl;
    cout << endl;
}
