/**
 * ROOT Jet
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_JET_H
#define ROOT_JET_H

#include <TLorentzVector.h>
#include <TVector3.h>

namespace rt
{
    class Jet
    {
        public:
            enum Flavor
            {
                UNKNOWN = 0,
                D = 1,
                U = 2,
                S = 3,
                C = 4,
                B = 5,
                T = 6
            };

            Jet();

            const TLorentzVector &p4() const;
            const TVector3 &vertex() const;
            const Flavor &flavor() const;

            void setP4(const TLorentzVector &);
            void setVertex(const TVector3 &);
            void setFlavor(const Flavor &);

        private:
            TLorentzVector _p4;
            TVector3 _vertex;
            Flavor _flavor;
    };
}

#endif
