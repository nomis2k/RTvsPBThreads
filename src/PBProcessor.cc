/**
 * Process ProtoBuf file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/H1.h"
#include "interface/PBProcessor.h"
#include "interface/PBReader.h"
#include "pb/Event.pb.h"

pb::Processor::Processor():
    _events_read(0),
    _events_read_in_last_file(0)
{
    _jets.reset(new H1(20, 0, 20));
}

void pb::Processor::init(const fs::path &file)
{
    _reader.reset(new Reader(file));
    _events_read_in_last_file = 0;
}

void pb::Processor::processEvents()
{
    if (!_reader)
        return;

    Event event;

    while(_reader->good())
    {
        _reader->read(event);

        _jets->fill(event.jets_size());
    }

    _events_read_in_last_file = _reader->eventsRead();
    _events_read += _events_read_in_last_file;

    _reader.reset();
}

uint32_t pb::Processor::eventsRead() const
{
    return _events_read;
}

uint32_t pb::Processor::eventsReadInLastFile() const
{
    return _events_read_in_last_file;
}
