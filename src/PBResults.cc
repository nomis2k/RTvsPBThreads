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
}

void pb::Results::print() const
{
    cout << " [ JETS ]" << endl;
    cout << *_jets << endl;
}

void pb::Results::save() const
{
    H1::TH1Ptr h1;
   
    h1 = _jets->convert("jets", "Number of jets");
    h1->Write();
}
