/**
 * Process ROOT file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <TH1I.h>

#include "interface/RTEvent.h"
#include "interface/RTProcessor.h"
#include "interface/RTReader.h"
#include "interface/RTResults.h"

rt::Processor::Processor():
    _events_read(0),
    _events_read_in_last_file(0)
{
    _results.reset(new Results());
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
    {
        if (!_reader->read(event) ||
            !event)

            continue;

        _results->jets()->Fill(event->jets().size());
    }

    _events_read_in_last_file = _reader->eventsRead();
    _events_read += _events_read_in_last_file;

    _reader.reset();
}

rt::Processor::ResultsPtr rt::Processor::results() const
{
    return _results;
}

uint32_t rt::Processor::eventsRead() const
{
    return _events_read;
}

uint32_t rt::Processor::eventsReadInLastFile() const
{
    return _events_read_in_last_file;
}
