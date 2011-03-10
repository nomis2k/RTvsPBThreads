/**
 * Process ProtoBuf file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef PROTOBUF_PROCESSOR_H
#define PROTOBUF_PROCESSOR_H

#include <boost/shared_ptr.hpp>

#include "interface/Processor.h"

namespace pb
{
    class Reader;

    class Processor : public ::Processor
    {
        public:
            Processor();

            virtual void init(const fs::path &file);
            virtual void processEvents();

        private:
            boost::shared_ptr<Reader> _reader;
    };
}

#endif
