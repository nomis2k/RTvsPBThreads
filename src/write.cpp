/**
 * Generate fixed number of events and save in specified format:
 * ROOT or ProtoBuf
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include "interface/PBGenerator.h"
#include "interface/RTGenerator.h"

using namespace std;

namespace fs = boost::filesystem;
using boost::lexical_cast;

void printUsage(const string &);

uint32_t MAX_FILES = 10;
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

    string format(argv[1]);
    boost::to_lower(format);

    if (2 < argc)
        ::MAX_FILES = lexical_cast<uint32_t>(argv[2]);

    if (3 < argc)
        ::MAX_EVENTS = lexical_cast<uint32_t>(argv[3]);

    try
    {
        boost::shared_ptr<Generator> generator;
        if ("pb" == format)
        {
            cout << "Generate ProtoBuf" << endl;

            generator.reset(new pb::Generator());
        }
        else if ("root" == format)
        {
            cout << "Generate ROOT Tree" << endl;

            generator.reset(new rt::Generator());
        }
        else
        {
            printUsage(argv[0]);

            return 1;
        }

        for(uint32_t file_id = 1; ::MAX_FILES >= file_id; ++file_id)
        {
            ostringstream file_name;
            file_name << "data_" << file_id << "." << format;
            fs::path file_path(file_name.str());
            generator->init(file_path);
            generator->generateEvents(::MAX_EVENTS, ::MAX_JETS);
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
    cout << "Usage: " << executable << " format [files] [events]" << endl;
    cout << endl;
    cout << " format  ROOT or PB" << endl;
    cout << " files   Number of files to generate [default: "
        << ::MAX_FILES << "]" << endl;
    cout << " events  Number of events to generated in each file [default: "
       << ::MAX_EVENTS << "]" << endl;
    cout << endl;
}
