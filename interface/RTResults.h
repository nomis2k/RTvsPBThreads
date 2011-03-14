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

        private:
            TH1Ptr _jets;
    };
}

#endif
