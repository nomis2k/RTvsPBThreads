/**
 * ROOT Results container: all histograms are kept in the H1 form
 *
 * Created by Samvel Khalatyan on Mar 13, 2011
 * Copyright 2011, All rights reserved
 */

#include <iostream>

#include <TH1D.h>

#include "interface/RTResults.h"

using namespace std;

rt::Results::Results():
    ::Results(PROTO_BUF)
{
    _jets.reset(new TH1D("jets", "Number of jets", 20, 0, 20));
    _jets->SetDirectory(0);

    _jet_e.reset(new TH1D("jet_e", "Jets e", 100, 100, 300));
    _jet_px.reset(new TH1D("jet_px", "Jets px", 50, 50, 150));
    _jet_py.reset(new TH1D("jet_py", "Jets py", 50, 50, 150));
    _jet_pz.reset(new TH1D("jet_pz", "Jets pz", 50, 50, 150));
}

rt::Results::~Results()
{
}

void rt::Results::add(const ::Results &results)
{    
    if (ROOT != results.type())
        return;

    const Results source = dynamic_cast<const Results &>(results);

    // Add results
    //
    _jets->Add(source._jets.get());
    _jet_e->Add(source._jet_e.get());
    _jet_px->Add(source._jet_px.get());
    _jet_py->Add(source._jet_py.get());
    _jet_pz->Add(source._jet_pz.get());
}

void rt::Results::print() const
{
    cout << " [ JETS ]" << endl;
    _jets->Print("all");
    _jet_e->Print("all");
    _jet_px->Print("all");
    _jet_py->Print("all");
    _jet_pz->Print("all");
}

void rt::Results::save() const
{
    _jets->Write();
    _jet_e->Write();
    _jet_px->Write();
    _jet_py->Write();
    _jet_pz->Write();
}

rt::Results::TH1Ptr rt::Results::jets() const
{
    return _jets;
}

rt::Results::TH1Ptr rt::Results::jet_e() const
{
    return _jet_e;
}

rt::Results::TH1Ptr rt::Results::jet_px() const
{
    return _jet_px;
}

rt::Results::TH1Ptr rt::Results::jet_py() const
{
    return _jet_py;
}

rt::Results::TH1Ptr rt::Results::jet_pz() const
{
    return _jet_pz;
}
