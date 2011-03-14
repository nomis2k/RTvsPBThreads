/**
 * ProtoBuf Results container: all histograms are kept in the H1 form
 *
 * Created by Samvel Khalatyan on Mar 13, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef PROTOBUF_RESULTS_H
#define PROTOBUF_RESULTS_H

#include <boost/shared_ptr.hpp>

#include "interface/Results.h"

class H1;

namespace pb
{
    class Results : public ::Results
    {
        public:
            typedef boost::shared_ptr<H1> H1Ptr;
            
            Results();
            virtual ~Results();

            virtual void add(const ::Results &);

            virtual void print() const;
            virtual void save() const;

            // Accessors
            //
            H1Ptr jets() const;
            H1Ptr jet_e() const;
            H1Ptr jet_px() const;
            H1Ptr jet_py() const;
            H1Ptr jet_pz() const;

        private:
            H1Ptr _jets;
            H1Ptr _jet_e;
            H1Ptr _jet_px;
            H1Ptr _jet_py;
            H1Ptr _jet_pz;
    };
}

#endif
