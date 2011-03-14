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
}

void rt::Results::print() const
{
    cout << " [ JETS ]" << endl;
    _jets->Print("all");
}

void rt::Results::save() const
{
    _jets->Write();
}
