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

#include "interface/RTEvent.h"

namespace fs = boost::filesystem;

class TFile;
class TTree;

namespace rt
{
    class Writer
    {
        public:
            typedef Event::Jets Jets;
            typedef Event::Leptons Leptons;

            Writer(const fs::path &output_file);
            ~Writer();

            bool write(const Jets &, const Leptons &);

        private:
            typedef boost::shared_ptr<TFile> TFilePtr;
            typedef boost::shared_ptr<TTree> TTreePtr;
            typedef boost::shared_ptr<Jets> JetsPtr;
            typedef boost::shared_ptr<Leptons> LeptonsPtr;

            TFilePtr _output;
            TTreePtr _tree;
            JetsPtr _jets;
            LeptonsPtr _muons;

            uint32_t _events_written;
    };
}

#endif
