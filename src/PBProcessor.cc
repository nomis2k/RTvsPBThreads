/**
 * Process ProtoBuf file: read events
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/H1.h"
#include "interface/PBProcessor.h"
#include "interface/PBReader.h"
#include "interface/PBResults.h"
#include "pb/Event.pb.h"

pb::Processor::Processor():
    _events_read(0),
    _events_read_in_last_file(0)
{
    _results.reset(new Results());
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

        const int number_of_jets = event.jets_size();
        _results->jets()->fill(number_of_jets);

        for(int i = 0; i < number_of_jets; ++i)
        {
            const Jet &jet = event.jets(i);

            _results->jet_flavor()->fill(jet.flavor());
            _results->jet_e()->fill(jet.p4().e());
            _results->jet_px()->fill(jet.p4().px());
            _results->jet_py()->fill(jet.p4().py());
            _results->jet_pz()->fill(jet.p4().pz());
            _results->jet_x()->fill(jet.vertex().x());
            _results->jet_y()->fill(jet.vertex().y());
            _results->jet_z()->fill(jet.vertex().z());
        }

        const int number_of_muons = event.muons_size();
        _results->muons()->fill(number_of_muons);

        for(int i = 0; i < number_of_muons; ++i)
        {
            const Lepton &muon = event.muons(i);

            _results->muon_e()->fill(muon.p4().e());
            _results->muon_px()->fill(muon.p4().px());
            _results->muon_py()->fill(muon.p4().py());
            _results->muon_pz()->fill(muon.p4().pz());
            _results->muon_x()->fill(muon.vertex().x());
            _results->muon_y()->fill(muon.vertex().y());
            _results->muon_z()->fill(muon.vertex().z());
        }
    }

    _events_read_in_last_file = _reader->eventsRead();
    _events_read += _events_read_in_last_file;

    _reader.reset();
}

pb::Processor::ResultsPtr pb::Processor::results() const
{
    return _results;
}

uint32_t pb::Processor::eventsRead() const
{
    return _events_read;
}

uint32_t pb::Processor::eventsReadInLastFile() const
{
    return _events_read_in_last_file;
}
