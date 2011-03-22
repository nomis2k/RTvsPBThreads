/**
 * ROOT Events generator
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <TRandom3.h>

#include "interface/RTEvent.h"
#include "interface/RTGenerator.h"
#include "interface/RTWriter.h"

rt::Generator::Generator()
{
    _randomizer.reset(new TRandom3());
    _randomizer->SetSeed(time(0));
}

void rt::Generator::init(const fs::path &file)
{
    _writer.reset(new Writer(file));
}

void rt::Generator::generateEvents(const uint32_t &events,
                                   const uint32_t &jets,
                                   const uint32_t &muons)
{
    if (!_writer)
        return;

    for(uint32_t i = 0; events > i; ++i)
    {
        // Generate Jets
        //
        Event::Jets jet_collection;
        for(uint32_t j = 0; jets > j; ++j)
        {
            rt::Jet jet;

            jet.setP4(TLorentzVector(_randomizer->Gaus(80, 15),
                                     _randomizer->Gaus(80, 15),
                                     _randomizer->Gaus(80, 15),
                                     _randomizer->Gaus(4, 2)));

            jet.setVertex(TVector3(_randomizer->Gaus(1, 10),
                                   _randomizer->Gaus(2, 10),
                                   _randomizer->Gaus(3, 10)));

            jet.setFlavor(Jet::Flavor(static_cast<int>(
                            _randomizer->Uniform(Jet::UNKNOWN,
                            Jet::T))));

            jet_collection.push_back(jet);
        }

        // Generate Muons
        //
        Event::Leptons muon_collection;
        for(uint32_t m = 0; muons > m; ++m)
        {
            rt::Lepton muon;

            muon.setP4(TLorentzVector(_randomizer->Gaus(50, 5),
                                      _randomizer->Gaus(50, 5),
                                      _randomizer->Gaus(50, 5),
                                      _randomizer->Gaus(105, 2)));

            muon.setVertex(TVector3(_randomizer->Gaus(6, 5),
                                    _randomizer->Gaus(5, 5),
                                    _randomizer->Gaus(4, 5)));

            muon_collection.push_back(muon);
        }

        _writer->write(jet_collection, muon_collection);
    }

    _writer.reset();
}
