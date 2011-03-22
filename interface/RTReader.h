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

#include "interface/RTEvent.h"

namespace fs = boost::filesystem;

class TFile;
class TTree;

namespace rt
{
    class Reader
    {
        public:
            typedef Event::Jets Jets;
            typedef Event::Leptons Leptons;

            Reader(const fs::path &input_file);
            ~Reader();

            bool good() const;
            uint32_t eventsRead() const;

            bool read(Jets * &, Leptons * &);

        private:
            typedef boost::shared_ptr<TFile> TFilePtr;

            TFilePtr _input;
            TTree *_tree;
            Jets *_jets;
            Leptons *_muons;

            bool _is_good;
            uint32_t _events_in_tree;
            uint32_t _events_read;
    };
}

#endif
