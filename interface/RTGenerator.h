/**
 * ROOT Events generator
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef ROOT_GENERATOR_H
#define ROOT_GENERATOR_H

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

#include "interface/Generator.h"

namespace fs = boost::filesystem;

class TRandom;

namespace rt
{
    class Writer;

    class Generator : public ::Generator
    {
        public:
            Generator(const fs::path &file);

            virtual void generateEvents(const uint32_t &events,
                                        const uint32_t &jets);

        private:
            boost::shared_ptr<TRandom> _randomizer;
            boost::shared_ptr<Writer> _writer;
    };
}

#endif
