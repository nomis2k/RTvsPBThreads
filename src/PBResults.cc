/**
 * ProtoBuf Results container: all histograms are kept in the H1 form
 *
 * Created by Samvel Khalatyan on Mar 13, 2011
 * Copyright 2011, All rights reserved
 */

#include <iostream>

#include <TH1.h>

#include "interface/H1.h"
#include "interface/PBResults.h"

using namespace std;

pb::Results::Results():
    ::Results(PROTO_BUF)
{
    _jets.reset(new H1(20, 0, 20));
    _jet_e.reset(new H1(100, 100, 300));
    _jet_px.reset(new H1(50, 50, 150));
    _jet_py.reset(new H1(50, 50, 150));
    _jet_pz.reset(new H1(50, 50, 150));
}

pb::Results::~Results()
{
}

void pb::Results::add(const ::Results &results)
{    
    if (PROTO_BUF != results.type())
        return;

    const Results source = dynamic_cast<const Results &>(results);

    // Add results
    //
    _jets->add(*source._jets);
    _jet_e->add(*source._jet_e);
    _jet_px->add(*source._jet_px);
    _jet_py->add(*source._jet_py);
    _jet_pz->add(*source._jet_pz);
}

void pb::Results::print() const
{
    cout << " [ JETS ]" << endl;
    cout << *_jets << endl;
    cout << *_jet_e << endl;
    cout << *_jet_px << endl;
    cout << *_jet_py << endl;
    cout << *_jet_pz << endl;
}

void pb::Results::save() const
{
    H1::TH1Ptr h1;
   
    h1 = _jets->convert("jets", "Number of jets");
    h1->Write();

    h1 = _jet_e->convert("jet_e", "Jets e");
    h1->Write();

    h1 = _jet_px->convert("jet_px", "Jets px");
    h1->Write();

    h1 = _jet_py->convert("jet_py", "Jets py");
    h1->Write();

    h1 = _jet_pz->convert("jet_pz", "Jets pz");
    h1->Write();
}

pb::Results::H1Ptr pb::Results::jets() const
{
    return _jets;
}

pb::Results::H1Ptr pb::Results::jet_e() const
{
    return _jet_e;
}

pb::Results::H1Ptr pb::Results::jet_px() const
{
    return _jet_px;
}

pb::Results::H1Ptr pb::Results::jet_py() const
{
    return _jet_py;
}

pb::Results::H1Ptr pb::Results::jet_pz() const
{
    return _jet_pz;
}
