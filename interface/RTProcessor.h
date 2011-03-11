/**
 * Process ROOT file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_PROCESSOR_H
#define ROOT_PROCESSOR_H

#include <boost/shared_ptr.hpp>

#include "interface/Processor.h"

namespace rt
{
    class Reader;

    class Processor : public ::Processor
    {
        public:
            Processor();

            virtual void init(const fs::path &file);
            virtual void processEvents();

            virtual uint32_t eventsRead();
            virtual uint32_t eventsReadInLastFile();

        private:
            boost::shared_ptr<Reader> _reader;

            uint32_t _events_read;
            uint32_t _events_read_in_last_file;
    };
}

#endif
