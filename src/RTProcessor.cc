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

        _results->jets()->Fill(event->jets().GetEntries());

        TIter next( & event->jets() );
        rt::Jet *jet;
        while ( jet = (rt::Jet*)next() )
        {
            _results->jet_flavor()->Fill(jet->flavor());
            _results->jet_e()->Fill(jet->p4().E());
            _results->jet_px()->Fill(jet->p4().Px());
            _results->jet_py()->Fill(jet->p4().Py());
            _results->jet_pz()->Fill(jet->p4().Pz());
            _results->jet_x()->Fill(jet->vertex().x());
            _results->jet_y()->Fill(jet->vertex().y());
            _results->jet_z()->Fill(jet->vertex().z());
        }

        _results->muons()->Fill(event->muons().GetEntries());

        TIter next2( & event->muons() );
        rt::Lepton *muon;
        while ( muon = (rt::Lepton*)next2() )
        {
            _results->muon_e()->Fill(muon->p4().E());
            _results->muon_px()->Fill(muon->p4().Px());
            _results->muon_py()->Fill(muon->p4().Py());
            _results->muon_pz()->Fill(muon->p4().Pz());
            _results->muon_x()->Fill(muon->vertex().x());
            _results->muon_y()->Fill(muon->vertex().y());
            _results->muon_z()->Fill(muon->vertex().z());
        }
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
