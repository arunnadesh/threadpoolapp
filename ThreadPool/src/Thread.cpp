#include <iostream>
#include <pthread.h>
#include "Thread.h"

using namespace std;

thread_ret_val Thread::thread_attr_init(thread_detach_state edetachState, thread_scope eScope)
{
  if(!pthread_attr_init(&tattr))
    cout<<"pthread init success"<<endl;
  
  return TH_SUCCESS;
}


thread_ret_val Thread::thread_create(void* (*funcPtr)(void*), void *funArg)
{
 if(!pthread_create(&tId, &tattr, funcPtr, funArg));
    cout<<"pthread create success and thread id is: "<< tId <<endl; 

 return TH_SUCCESS;
}


thread_ret_val Thread::thread_join()
{
 void* result = NULL;

 if(!pthread_join(tId,&result))
    cout<<"pthread join success for thread: "<< tId <<endl;

 return TH_SUCCESS;
}


thread_ret_val Thread::thread_cancel()
{
  cout<<"thread_cancel not implemented"<<endl;
  return TH_SUCCESS;
}


void Thread::thread_exit()
{
  cout<<"thread exitting..... "<<endl;
  pthread_exit(NULL);
}


thread_ret_val Thread::thread_detach()
{
  cout<<"thread_detach not implemented"<<endl;
  return TH_SUCCESS;
}


thread_ret_val Thread::thread_set_detachstate(thread_detach_state edetachState)
{
  cout<<"thread_set_detachstate not implemented"<<endl;
  return TH_SUCCESS;
}


thread_ret_val Thread::thread_set_scope(thread_scope eScope)
{
  cout<<"thread_set_scope not implemented"<<endl;
  return TH_SUCCESS;
}


thread_detach_state Thread::thread_get_detachstate()
{
  cout<<"thread_set_scope not implemented"<<endl;
  return TH_JOINABLE;
}


thread_scope Thread::thread_get_scope(thread_scope eScope)
{
  cout<<"thread_set_scope not implemented"<<endl;
  return TH_SYSTEM_SCOPE;
}

unsigned long Thread::thread_query_id(void)
{
   return pthread_self();
}

