/**
 * Process ROOT file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/RTEvent.h"
#include "interface/RTProcessor.h"
#include "interface/RTReader.h"

rt::Processor::Processor():
    _events_read(0),
    _events_read_in_last_file(0)
{
}

void rt::Processor::init(const fs::path &file)
{
    _reader.reset(new Reader(file));
    _events_read_in_last_file = 0;
}

void rt::Processor::processEvents()
{
    if (!_reader)
        return;

    Event *event = 0;

    while(_reader->good())
        _reader->read(event);

    _events_read_in_last_file = _reader->eventsRead();
    _events_read += _events_read_in_last_file;

    _reader.reset();
}

uint32_t rt::Processor::eventsRead()
{
    return _events_read;
}

uint32_t rt::Processor::eventsReadInLastFile()
{
    return _events_read_in_last_file;
}
