/**
 * ROOT Writer
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_WRITER_H
#define ROOT_WRITER_H

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

namespace fs = boost::filesystem;

class TFile;
class TTree;

namespace rt
{
    class Event;

    class Writer
    {
        public:
            typedef boost::shared_ptr<Event> EventPtr;

            Writer(const fs::path &output_file);
            ~Writer();

            bool write();

            EventPtr event() const;

        private:
            typedef boost::shared_ptr<TFile> TFilePtr;
            typedef boost::shared_ptr<TTree> TTreePtr;

            TFilePtr _output;
            TTreePtr _tree;
            EventPtr _event;

            uint32_t _events_written;
    };
}

#endif
