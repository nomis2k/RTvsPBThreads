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
            Results();
            virtual ~Results();

            virtual void add(const ::Results &);

            virtual void print() const;
            virtual void save() const;

        private:
            typedef boost::shared_ptr<H1> H1Ptr;
            
            H1Ptr _jets;
    };
}

#endif
