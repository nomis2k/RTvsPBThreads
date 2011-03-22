/**
 * ROOT Event
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_EVENT_H
#define ROOT_EVENT_H

#include <vector>

#include <TObject.h>

#include "interface/RTJet.h"
#include "interface/RTLepton.h"

namespace rt
{
    class Event : public TObject
    {
        public:
            typedef std::vector<Jet> Jets;
            typedef std::vector<Lepton> Leptons;

            Event();
            virtual ~Event() {}

            const Jets &jets() const;
            const Leptons &muons() const;

            void addJet(const Jet &);
            void addMuon(const Lepton &);

        private:
            Jets _jets;
            Leptons _muons;

        ClassDef(Event, 1);
    };
}

#endif
