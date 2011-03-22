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

#include "interface/RTJet.h"
#include "interface/RTLepton.h"
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

    _tree.reset(new TTree("rt", "ROOT Tree"));

    _jets.reset(new Jets());
    _muons.reset(new Leptons());

    _tree->Branch("jets", _jets.get());
    _tree->Branch("muons", _muons.get());
}

Writer::~Writer()
{
    _output->Write();
}

bool Writer::write(const Jets &jets, const Leptons &muons)
{
    if (!_output)
        return false;

    *_jets = jets;
    *_muons = muons;

    _tree->Fill();

    ++_events_written;

    return true;
}
