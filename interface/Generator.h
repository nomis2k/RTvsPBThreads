/**
 * Generator Interface
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef GENERATOR_H
#define GENERATOR_H

class Generator
{
    public:
        virtual ~Generator() {}

        virtual void generateEvents(const uint32_t &events,
                                    const uint32_t &jets) = 0;
};

#endif
