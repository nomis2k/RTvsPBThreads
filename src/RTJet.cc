/**
 * ROOT Jet
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/RTJet.h"

using rt::Jet;

Jet::Jet()
{
}

const TLorentzVector &Jet::p4() const
{
    return _p4;
}

void Jet::setP4(const TLorentzVector &p4)
{
    _p4 = p4;
}
