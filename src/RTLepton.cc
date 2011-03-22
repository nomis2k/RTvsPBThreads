/**
 * ROOT Lepton
 *
 * Created by Samvel Khalatyan on Mar 22, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/RTLepton.h"

using rt::Lepton;

Lepton::Lepton()
{
}

const TLorentzVector &Lepton::p4() const
{
    return _p4;
}

const TVector3 &Lepton::vertex() const
{
    return _vertex;
}

void Lepton::setP4(const TLorentzVector &p4)
{
    _p4 = p4;
}

void Lepton::setVertex(const TVector3 &vertex)
{
    _vertex = vertex;
}
