/**
 * Process ROOT file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/RTEvent.h"
#include "interface/RTProcessor.h"
#include "interface/RTReader.h"

rt::Processor::Processor(const fs::path &file)
{
    _reader.reset(new Reader(file));
}

void rt::Processor::processEvents()
{
    Event *event = 0;

    while(_reader->good())
        _reader->read(event);
}
