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

    Writer::EventPtr event = _writer->event();;
    event->Clear();

    for(uint32_t i = 0; events > i; ++i)
    {
        // Generate Jets
        //
        for(uint32_t j = 0; jets > j; ++j)
        {
           rt::Jet *jet = event->add_jets();
           TLorentzVector *p4 = jet->mutable_p4();

           p4->SetE(_randomizer->Gaus(172, 10));
           p4->SetPx(_randomizer->Gaus(45, 5));
           p4->SetPy(_randomizer->Gaus(45, 5));
           p4->SetPz(_randomizer->Gaus(45, 5));

           TVector3 *vertex = jet->mutable_vertex();
           
           vertex->SetX(_randomizer->Gaus(6, 1));
           vertex->SetY(_randomizer->Gaus(7, 1));
           vertex->SetZ(_randomizer->Gaus(8, 1));

          jet->setFlavor(Jet::Flavor(static_cast<int>(
                            _randomizer->Uniform(Jet::UNKNOWN,
                            Jet::T))));

        }

        // Generate Muons
        //
        for(uint32_t m = 0; muons > m; ++m)
        {
           rt::Lepton * muon = event->add_muons();

             TLorentzVector *p4 = muon->mutable_p4();

            p4->SetE(_randomizer->Gaus(200,10));
            p4->SetPx(_randomizer->Gaus(100,10));
            p4->SetPy(_randomizer->Gaus(100,10));
            p4->SetPz(_randomizer->Gaus(100,10));

            TVector3 *vertex = muon->mutable_vertex();

            vertex->SetX(_randomizer->Gaus(1, 1));
            vertex->SetY(_randomizer->Gaus(2, 1));
            vertex->SetZ(_randomizer->Gaus(3, 1));
        }

        _writer->write();

        event->Clear();
    }

    _writer.reset();
}
