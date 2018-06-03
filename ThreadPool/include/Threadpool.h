#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <deque>
#include <unistd.h>

#include "Mutex.h"
#include "Waitsignal.h"
#include "Thread.h"

typedef enum thread_pool_retval{
    TH_POOL_CREATE_SUCCESS = 0,
    TH_POOL_CREATE_FAILURE
} thread_pool_retval;

typedef enum thread_pool_state{
    TH_POOL_INIT=0,
    TH_POOL_STARTED,
    TH_POOL_STOPPED
}thread_pool_state;

class Threadpool{

      std::vector<Thread*> thVector;
      int numThrds;
      Mutex jobMutex;
      Waitsignal condVar;
      std::deque<Job*>   jobQ;
      thread_pool_state thState;
   protected:
      friend void* thread_fun(void*);
      void processingLoop();
   public:
      Threadpool(int poolSize);
      thread_pool_retval threadpool_create();
      thread_pool_retval threadpool_add_job(Job* task);
      void threadpool_destroy();
      
};

#endif
