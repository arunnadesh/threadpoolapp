#include <iostream>
#include <pthread.h>
#include "Mutex.h"

using namespace std;

Mutex::Mutex():mlock(PTHREAD_MUTEX_INITIALIZER)
{
  cout<<"Mutex initialized"<<endl;
}

void Mutex::lock()
{
  if(!pthread_mutex_lock(&mlock))
     cout<<"Mutex locked"<<endl;
}

void Mutex::unlock()
{
   if(!pthread_mutex_unlock(&mlock))
     cout<<"Mutex locked"<<endl;

}

pthread_mutex_t* Mutex::getMutex()
{
   return &mlock;
}

