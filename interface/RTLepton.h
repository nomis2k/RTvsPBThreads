/**
 * ROOT Lepton
 *
 * Created by Samvel Khalatyan on Mar 22, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_LEPTON_H
#define ROOT_LEPTON_H

#include <TLorentzVector.h>
#include <TVector3.h>

namespace rt
{
   class Lepton : public TObject
    {
        public:
            Lepton();

            const TLorentzVector &p4() const;
            const TVector3 &vertex() const;
            
            TLorentzVector *mutable_p4() { return &_p4; }
            TVector3 *mutable_vertex() { return &_vertex; }
            
            void setP4(const TLorentzVector &);
            void setVertex(const TVector3 &);

        private:
            TLorentzVector _p4;
            TVector3 _vertex;
            ClassDef(Lepton,1);
    };
}

#endif
