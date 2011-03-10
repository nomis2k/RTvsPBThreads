/**
 * Processor Interface
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor
{
    public:
        virtual ~Processor() {}

        virtual void processEvents() = 0;
};

#endif
