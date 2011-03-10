/**
 * Process ROOT file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_PROCESSOR_H
#define ROOT_PROCESSOR_H

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

#include "interface/Processor.h"

namespace fs = boost::filesystem;

namespace rt
{
    class Reader;

    class Processor : public ::Processor
    {
        public:
            Processor(const fs::path &file);

            virtual void processEvents();

        private:
            boost::shared_ptr<Reader> _reader;
    };
}

#endif
