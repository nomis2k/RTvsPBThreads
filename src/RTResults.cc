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

    _jet_flavor.reset(new TH1D("jet_flavor", "Flavor of jets", 20, 0, 20));
    _jet_flavor->SetDirectory(0);

    _jet_e.reset(new TH1D("jet_e", "Jets e", 10, 0, 10));
    _jet_e->SetDirectory(0);

    _jet_px.reset(new TH1D("jet_px", "Jets px", 50, 50, 150));
    _jet_px->SetDirectory(0);

    _jet_py.reset(new TH1D("jet_py", "Jets py", 50, 50, 150));
    _jet_py->SetDirectory(0);

    _jet_pz.reset(new TH1D("jet_pz", "Jets pz", 50, 50, 150));
    _jet_pz->SetDirectory(0);

    _jet_x.reset(new TH1D("jet_x", "Jets x", 10, -5, 5));
    _jet_x->SetDirectory(0);

    _jet_y.reset(new TH1D("jet_y", "Jets y", 10, -5, 5));
    _jet_y->SetDirectory(0);

    _jet_z.reset(new TH1D("jet_z", "Jets z", 10, -5, 5));
    _jet_z->SetDirectory(0);

    _muons.reset(new TH1D("muons", "Number of muons", 20, 0, 20));
    _muons->SetDirectory(0);

    _muon_e.reset(new TH1D("muon_e", "Muons e", 50, 50, 150));
    _muon_e->SetDirectory(0);

    _muon_px.reset(new TH1D("muon_px", "Muons px", 50, 0, 100));
    _muon_px->SetDirectory(0);

    _muon_py.reset(new TH1D("muon_py", "Muons py", 50, 0, 100));
    _muon_py->SetDirectory(0);

    _muon_pz.reset(new TH1D("muon_pz", "Muons pz", 50, 0, 100));
    _muon_pz->SetDirectory(0);

    _muon_x.reset(new TH1D("muon_x", "Muons x", 10, 0, 10));
    _muon_x->SetDirectory(0);

    _muon_y.reset(new TH1D("muon_y", "Muons y", 10, 0, 10));
    _muon_y->SetDirectory(0);

    _muon_z.reset(new TH1D("muon_z", "Muons z", 10, 0, 10));
    _muon_z->SetDirectory(0);
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
    _jet_flavor->Add(source._jet_flavor.get());
    _jet_e->Add(source._jet_e.get());
    _jet_px->Add(source._jet_px.get());
    _jet_py->Add(source._jet_py.get());
    _jet_pz->Add(source._jet_pz.get());
    _jet_x->Add(source._jet_x.get());
    _jet_y->Add(source._jet_y.get());
    _jet_z->Add(source._jet_z.get());

    _muons->Add(source._muons.get());
    _muon_e->Add(source._muon_e.get());
    _muon_px->Add(source._muon_px.get());
    _muon_py->Add(source._muon_py.get());
    _muon_pz->Add(source._muon_pz.get());
    _muon_x->Add(source._muon_x.get());
    _muon_y->Add(source._muon_y.get());
    _muon_z->Add(source._muon_z.get());
}

void rt::Results::print() const
{
    cout << " [ JETS ]" << endl;
    _jets->Print("all");
    _jet_flavor->Print("all");
    _jet_e->Print("all");
    _jet_px->Print("all");
    _jet_py->Print("all");
    _jet_pz->Print("all");
    _jet_x->Print("all");
    _jet_y->Print("all");
    _jet_z->Print("all");
    cout << endl;
    cout << " [ MUONS ]" << endl;
    _muons->Print("all");
    _muon_e->Print("all");
    _muon_px->Print("all");
    _muon_py->Print("all");
    _muon_pz->Print("all");
    _muon_x->Print("all");
    _muon_y->Print("all");
    _muon_z->Print("all");
}

void rt::Results::save() const
{
    _jets->Write();
    _jet_flavor->Write();
    _jet_e->Write();
    _jet_px->Write();
    _jet_py->Write();
    _jet_pz->Write();
    _jet_x->Write();
    _jet_y->Write();
    _jet_z->Write();

    _muons->Write();
    _muon_e->Write();
    _muon_px->Write();
    _muon_py->Write();
    _muon_pz->Write();
    _muon_x->Write();
    _muon_y->Write();
    _muon_z->Write();
}

rt::Results::TH1Ptr rt::Results::jets() const
{
    return _jets;
}

rt::Results::TH1Ptr rt::Results::jet_flavor() const
{
    return _jet_flavor;
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

rt::Results::TH1Ptr rt::Results::jet_x() const
{
    return _jet_x;
}

rt::Results::TH1Ptr rt::Results::jet_y() const
{
    return _jet_y;
}

rt::Results::TH1Ptr rt::Results::jet_z() const
{
    return _jet_z;
}

rt::Results::TH1Ptr rt::Results::muons() const
{
    return _muons;
}

rt::Results::TH1Ptr rt::Results::muon_e() const
{
    return _muon_e;
}

rt::Results::TH1Ptr rt::Results::muon_px() const
{
    return _muon_px;
}

rt::Results::TH1Ptr rt::Results::muon_py() const
{
    return _muon_py;
}

rt::Results::TH1Ptr rt::Results::muon_pz() const
{
    return _muon_pz;
}

rt::Results::TH1Ptr rt::Results::muon_x() const
{
    return _muon_x;
}

rt::Results::TH1Ptr rt::Results::muon_y() const
{
    return _muon_y;
}

rt::Results::TH1Ptr rt::Results::muon_z() const
{
    return _muon_z;
}
