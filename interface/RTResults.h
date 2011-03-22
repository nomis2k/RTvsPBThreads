/**
 * ROOT Results container: all histograms are kept in the H1 form
 *
 * Created by Samvel Khalatyan on Mar 13, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_RESULTS_H
#define ROOT_RESULTS_H

#include <boost/shared_ptr.hpp>

#include "interface/Results.h"

class TH1;

namespace rt
{
    class Results : public ::Results
    {
        public:
            typedef boost::shared_ptr<TH1> TH1Ptr;
            
            Results();
            virtual ~Results();

            virtual void add(const ::Results &);

            virtual void print() const;
            virtual void save() const;

            // Accessors
            //
            TH1Ptr jets() const;
            TH1Ptr jet_flavor() const;
            TH1Ptr jet_e() const;
            TH1Ptr jet_px() const;
            TH1Ptr jet_py() const;
            TH1Ptr jet_pz() const;
            TH1Ptr jet_x() const;
            TH1Ptr jet_y() const;
            TH1Ptr jet_z() const;

            TH1Ptr muons() const;
            TH1Ptr muon_e() const;
            TH1Ptr muon_px() const;
            TH1Ptr muon_py() const;
            TH1Ptr muon_pz() const;
            TH1Ptr muon_x() const;
            TH1Ptr muon_y() const;
            TH1Ptr muon_z() const;

        private:
            TH1Ptr _jets;
            TH1Ptr _jet_flavor;
            TH1Ptr _jet_e;
            TH1Ptr _jet_px;
            TH1Ptr _jet_py;
            TH1Ptr _jet_pz;
            TH1Ptr _jet_x;
            TH1Ptr _jet_y;
            TH1Ptr _jet_z;

            TH1Ptr _muons;
            TH1Ptr _muon_e;
            TH1Ptr _muon_px;
            TH1Ptr _muon_py;
            TH1Ptr _muon_pz;
            TH1Ptr _muon_x;
            TH1Ptr _muon_y;
            TH1Ptr _muon_z;
    };
}

#endif
