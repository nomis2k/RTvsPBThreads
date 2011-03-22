/**
 * Generator Interface
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class Generator
{
    public:
        virtual ~Generator() {}

        virtual void init(const fs::path &file) = 0;
        virtual void generateEvents(const uint32_t &events,
                                    const uint32_t &jets = 10,
                                    const uint32_t &muons = 5) = 0;
};

#endif
