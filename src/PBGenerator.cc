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

pb::Generator::Generator(const fs::path &file)
{
    _randomizer.reset(new TRandom3());
    _randomizer->SetSeed(time(0));

    _writer.reset(new Writer(file));
}

void pb::Generator::generateEvents(const uint32_t &events, const uint32_t &jets)
{
    Event event;

    for(uint32_t i = 0; events > i; ++i)
    {
        // Generate Jets
        //
        for(uint32_t j = 0; jets > j; ++j)
        {
            Jet *jet = event.add_jets();
            LorentzVector *p4 = jet->mutable_p4();

            p4->set_e(_randomizer->Gaus(200,10));
            p4->set_px(_randomizer->Gaus(100,10));
            p4->set_py(_randomizer->Gaus(100,10));
            p4->set_pz(_randomizer->Gaus(100,10));
        }

        _writer->write(event);

        event.Clear();
    }
}
