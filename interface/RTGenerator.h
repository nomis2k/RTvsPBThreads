/**
 * ROOT Events generator
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_GENERATOR_H
#define ROOT_GENERATOR_H

#include <boost/shared_ptr.hpp>

#include "interface/Generator.h"

class TRandom;

namespace rt
{
    class Writer;

    class Generator : public ::Generator
    {
        public:
            Generator();

            virtual void init(const fs::path &file);
            virtual void generateEvents(const uint32_t &events,
                                        const uint32_t &jets,
                                        const uint32_t &muons);

        private:
            boost::shared_ptr<TRandom> _randomizer;
            boost::shared_ptr<Writer> _writer;
    };
}

#endif
