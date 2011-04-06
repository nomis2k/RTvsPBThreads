/**
 * ROOT Writer
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>

#include "interface/RTEvent.h"
#include "interface/RTWriter.h"

using namespace std;

using rt::Writer;

Writer::Writer(const fs::path &output_file):
    _events_written(0)
{
    _output.reset(new TFile(output_file.string().c_str(), "recreate"));
    if (!_output->IsOpen())
    {
        cerr << "Failed to open output TFile" << endl;

        _output.reset();
    }

    _output->SetCompressionLevel(0);
    _tree.reset(new TTree("rt", "ROOT Tree"));
    _event.reset(new Event());

    _tree->Branch("event", _event.get());
}

Writer::~Writer()
{
    _output->Write();
}

bool Writer::write()
{
    if (!_output)
        return false;

    _tree->Fill();

    ++_events_written;

    return true;
}

Writer::EventPtr Writer::event() const
{
    return _event;
}
