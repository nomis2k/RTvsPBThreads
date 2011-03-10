/**
 * ROOT Jet
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_JET_H
#define ROOT_JET_H

#include <TLorentzVector.h>

namespace rt
{
    class Jet
    {
        public:
            Jet();

            const TLorentzVector &p4() const;

            void setP4(const TLorentzVector &);

        private:
            TLorentzVector _p4;
    };
}

#endif
