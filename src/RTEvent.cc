/**
 * ROOt Event
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include "interface/RTEvent.h"

using rt::Event;

ClassImp(Event)

Event::Event()
{
}

const Event::Jets &Event::jets() const
{
    return _jets;
}

const Event::Leptons &Event::muons() const
{
    return _muons;
}

void Event::addJet(const Jet &jet)
{
    _jets.push_back(jet);
}

void Event::addMuon(const Lepton &lepton)
{
    _muons.push_back(lepton);
}
