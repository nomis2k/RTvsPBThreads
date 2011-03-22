/**
 * ROOT Jet
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/RTJet.h"

using rt::Jet;

Jet::Jet():
    _flavor(UNKNOWN)
{
}

const TLorentzVector &Jet::p4() const
{
    return _p4;
}

const TVector3 &Jet::vertex() const
{
    return _vertex;
}

const Jet::Flavor &Jet::flavor() const
{
    return _flavor;
}

void Jet::setP4(const TLorentzVector &p4)
{
    _p4 = p4;
}

void Jet::setVertex(const TVector3 &vertex)
{
    _vertex = vertex;
}

void Jet::setFlavor(const Flavor &flavor)
{
    _flavor = flavor;
}
