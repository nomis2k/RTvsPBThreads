/**
 * Process ProtoBuf file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/PBProcessor.h"
#include "interface/PBReader.h"
#include "pb/Event.pb.h"

pb::Processor::Processor()
{
}

void pb::Processor::init(const fs::path &file)
{
    _reader.reset(new Reader(file));
}

void pb::Processor::processEvents()
{
    if (!_reader)
        return;

    Event event;

    while(_reader->good())
        _reader->read(event);

    _reader.reset();
}
