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

rt::Generator::Generator(const fs::path &file)
{
    _randomizer.reset(new TRandom3());
    _randomizer->SetSeed(time(0));

    _writer.reset(new Writer(file));
}

void rt::Generator::generateEvents(const uint32_t &events, const uint32_t &jets)
{
    for(uint32_t i = 0; events > i; ++i)
    {
        Event event;

        // Generate Jets
        //
        for(uint32_t j = 0; jets > j; ++j)
        {
            rt::Jet jet;

            jet.setP4(TLorentzVector(_randomizer->Gaus(100, 10),
                                     _randomizer->Gaus(100, 10),
                                     _randomizer->Gaus(100, 10),
                                     _randomizer->Gaus(200, 10)));

            event.addJet(jet);
        }

        _writer->write(event);
    }
}
