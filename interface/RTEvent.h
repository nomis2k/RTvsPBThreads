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
#include "TClonesArray.h"

#include "interface/RTJet.h"
#include "interface/RTLepton.h"

namespace rt
{
    class Event : public TObject
    {
        public:
            typedef TClonesArray Jets;
            typedef TClonesArray Leptons;

            Event();
            virtual ~Event() {}

            const Jets &jets() const;
            const Leptons &muons() const;

            Jet *add_jets() {
               return new (_jets[_jets.GetEntriesFast()]) Jet();
            }

            Lepton * add_muons() {
               return new (_muons[_jets.GetEntriesFast()]) Lepton();
            }
            
            void Clear() {
               _jets.Clear();
               _muons.Clear();
            }

        private:
            Jets _jets;
            Leptons _muons;

        ClassDef(Event, 1);
    };
}

#endif
