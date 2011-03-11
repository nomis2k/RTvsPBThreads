/**
 * ProtoBuf Thread(s) Instructor:
 *  - Create threads
 *  - synchronize
 *
 * Created by Samvel Khalatyan on Mar 10, 2011
 * Copyright 2011, All rights reserved
 */

#ifndef PROTOBUF_INSTRUCTOR_H
#define PROTOBUF_INSTRUCTOR_H

#include <queue>
#include <string>
#include <vector>

#include "interface/PBThread.h"

namespace pb
{
    class Instructor
    {
        public:
            typedef std::vector<std::string> Files;
            typedef ::Thread::ConditionPtr ConditionPtr;
            typedef ::Thread::Lock Lock;

            Instructor();

            void processFiles(const Files &files);

            // Communication with Thread
            //
            ConditionPtr condition() const;

            void notify(Thread *thread);

        private:
            void process();

            // Create threads
            //
            void init();

            // Start threads
            //
            void start();

            // Run threads
            //
            void loop();

            // Wait for any thread to finish
            //
            void wait();

            // threads manipulation
            //
            void processCompleteThreads();
            void stopThread();
            void continueThread();

            // Inputs to be processed
            //
            Files _input_files;
            Files::const_iterator _next_file;

            typedef boost::shared_ptr<Thread> ThreadPtr;
            typedef std::vector<ThreadPtr> Threads;
            typedef std::queue<Thread *> ThreadsFIFO;

            Threads _threads;
            ThreadsFIFO _complete_threads;
            int _running_threads;

            // Instructor Mutex
            //
            ConditionPtr _condition; 
    };
}

#endif
