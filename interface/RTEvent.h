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

namespace rt
{
    class Event : public TObject
    {
        public:
            typedef std::vector<Jet> Jets;

            Event();
            virtual ~Event() {}

            const Jets &jets() const;

            void addJet(const Jet &);

        private:
            Jets _jets;

        ClassDef(Event, 1);
    };
}

#endif
