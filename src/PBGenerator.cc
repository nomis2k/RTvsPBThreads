/**
 * ProtoBuf Events generator
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <TRandom3.h>

#include "interface/PBGenerator.h"
#include "interface/PBWriter.h"
#include "pb/Event.pb.h"

pb::Generator::Generator()
{
    _randomizer.reset(new TRandom3());
    _randomizer->SetSeed(time(0));
}

void pb::Generator::init(const fs::path &file)
{
    _writer.reset(new Writer(file));
}

void pb::Generator::generateEvents(const uint32_t &events,
                                   const uint32_t &jets,
                                   const uint32_t &muons)
{
    if (!_writer)
        return;

    Event event;

    for(uint32_t i = 0; events > i; ++i)
    {
        // Generate Jets
        //
        for(uint32_t j = 0; jets > j; ++j)
        {
            Jet *jet = event.add_jets();
            LorentzVector *p4 = jet->mutable_p4();

            p4->set_e(_randomizer->Gaus(45, 5));
            p4->set_px(_randomizer->Gaus(45, 5));
            p4->set_py(_randomizer->Gaus(45, 5));
            p4->set_pz(_randomizer->Gaus(172, 10));

            Vertex *vertex = jet->mutable_vertex();

            vertex->set_x(_randomizer->Gaus(6, 1));
            vertex->set_y(_randomizer->Gaus(7, 1));
            vertex->set_z(_randomizer->Gaus(8, 1));

            jet->set_flavor(Jet::Flavor(static_cast<int>(
                            _randomizer->Uniform(Jet::UNKNOWN, Jet::T))));
        }

        // Generate Muons
        //
        for(uint32_t m = 0; muons > m; ++m)
        {
            Lepton *muon = event.add_muons();
            LorentzVector *p4 = muon->mutable_p4();

            p4->set_e(_randomizer->Gaus(200,10));
            p4->set_px(_randomizer->Gaus(100,10));
            p4->set_py(_randomizer->Gaus(100,10));
            p4->set_pz(_randomizer->Gaus(100,10));

            Vertex *vertex = muon->mutable_vertex();

            vertex->set_x(_randomizer->Gaus(1, 1));
            vertex->set_y(_randomizer->Gaus(2, 1));
            vertex->set_z(_randomizer->Gaus(3, 1));
        }

        _writer->write(event);

        event.Clear();
    }

    _writer.reset();
}
