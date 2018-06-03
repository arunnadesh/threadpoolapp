#include <iostream>

using namespace std;

#include "Job.h"
#include "Threadpool.h"


Threadpool::Threadpool(int poolSize):
numThrds(poolSize),
jobMutex(),
condVar(),
thState(TH_POOL_INIT)
{
   cout<<"Initializing Threadpool..."<<endl;

}

void* thread_fun(void* args)
{
   ((Threadpool*)args)->processingLoop();
   
   return NULL;

}


void Threadpool::processingLoop()
{
   Job* currJob= NULL;

   cout<<"Threadpool: Entering processing loop..."<<endl;
   cout<<"Threadpool: Thread ID:"<<Thread::thread_query_id() <<endl;

   while(true){
     
        jobMutex.lock();

        while(thState != TH_POOL_STOPPED && jobQ.empty()){
              cout<<"Threadpool: Unlocking Job Mutex and Waitig... Thread ID:"<<Thread::thread_query_id() <<endl;
 
              condVar.wait(&jobMutex);
 
              cout<<"Threadpool: Signalled..Locking Job Mutex Thread ID:"<<Thread::thread_query_id() <<endl;
        }
 
        if(thState == TH_POOL_STOPPED){
              cout<<"Threadpool: Thread woken up due to broadcast:"<<Thread::thread_query_id() <<endl;
              jobMutex.unlock();
              Thread::thread_exit();
        }
        else{
          currJob = jobQ.front();
          jobQ.pop_front();
          jobMutex.unlock();

          cout<<"Threadpool: Executing Job Thread ID:"<<Thread::thread_query_id() <<endl;

          (*currJob)();
          
          delete currJob;
        }

  }
       
}


thread_pool_retval Threadpool::threadpool_create()
{

    for(int i=0; i < numThrds; i++){

           Thread* th =  new Thread();

           if(!th){
             cout<<"Thread object allocation failed...";
             return TH_POOL_CREATE_FAILURE;
           }
           else{

	             if(!th->thread_create(thread_fun, this)) {
        	       cout<<"Thread created successfully...."<<endl;
               	       thVector.push_back(th);
             	     }
             	     else {
              	       cout<<"Thread creation Failed...."<<endl;
               	       return TH_POOL_CREATE_FAILURE;
             	     }
           }
   }

    cout <<"Threadpool: threads created by the thread pool:"<<numThrds << endl;
    thState = TH_POOL_STARTED;
    cout <<"Threadpool: Started...."<<endl;

    return TH_POOL_CREATE_SUCCESS;
}


thread_pool_retval Threadpool::threadpool_add_job(Job* task)
{
      jobMutex.lock();
        

       if (thState != TH_POOL_STOPPED){
     		 jobQ.push_back(task);
     		 condVar.signal();
       }
       else
          cout<<"Threadpool: Stopped. Not adding jobs"<<endl;

      jobMutex.unlock();

      return TH_POOL_CREATE_SUCCESS;
}

void Threadpool::threadpool_destroy()
{
     jobMutex.lock();

       cout<<"Threadpool: Stopping Thread Poool"<<endl;
       thState = TH_POOL_STOPPED;

     jobMutex.unlock();

     cout << "Threadpool: Broadcasting STOP signal to all threads..." << endl;
     condVar.broadcast();

     
	  for (int i = 0; i < numThrds; i++) {
                 thread_ret_val ret;
  		 ret = thVector[i]->thread_join();

		 cout << "Threadpool: thread joined... :" << thVector[i] << endl;
		 condVar.broadcast();
  	  }
 

         cout <<"Threadpool: threads exited from the thread pool:"<<numThrds << endl;

}

