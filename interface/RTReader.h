/**
 * ROOT Reader
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_READER_H
#define ROOT_READER_H

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

namespace fs = boost::filesystem;

class TFile;
class TTree;

namespace rt
{
    class Event;

    class Reader
    {
        public:
            Reader(const fs::path &input_file);
            ~Reader();

            bool good() const;
            uint32_t eventsRead() const;

            bool read(Event * &);

        private:
            typedef boost::shared_ptr<TFile> TFilePtr;

            TFilePtr _input;
            TTree *_tree;
            Event *_event;

            bool _is_good;
            uint32_t _events_in_tree;
            uint32_t _events_read;
    };
}

#endif
