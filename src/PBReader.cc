/**
 * ProtoBuf Reader
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <math.h>

#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "interface/PBReader.h"

using namespace std;

using pb::Reader;

Reader::Reader(const fs::path &input_file):
    _input(input_file.string().c_str(), ios::in | ios::binary),
    _is_good(true),
    _events_read(0)
{
    _raw_in.reset(new ::google::protobuf::io::IstreamInputStream(&_input));
    _coded_in.reset(new ::google::protobuf::io::CodedInputStream(_raw_in.get()));

    // Push limit of read bytes
    //
    _coded_in->SetTotalBytesLimit(pow(1024,3), 900*pow(1024,2));
    _coded_in->ReadLittleEndian32(&_events_stored);
}

Reader::~Reader()
{
}

bool Reader::good() const
{
    return _is_good;
}

uint32_t Reader::eventsRead() const
{
    return _events_read;
}

bool Reader::read(Event &event)
{
    if (!good())
        return false;

    uint32_t message_size;
    if (!_coded_in->ReadVarint32(&message_size))
    {
        _is_good = false;

        return false;
    }

    if (0 < message_size)
    {
        string message;
        if (!_coded_in->ReadString(&message, message_size) ||
            !event.ParseFromString(message))

            return false;
    }
    
    ++_events_read;

    return true;
}
