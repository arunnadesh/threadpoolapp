#include <iostream>
#include <pthread.h>
#include "Mutex.h"
#include "Waitsignal.h"

using namespace std;

Waitsignal::Waitsignal():condvar(PTHREAD_COND_INITIALIZER)
{
  cout<<"Initializing conditional variable"<<endl;
}

void Waitsignal::wait(Mutex *mux)
{
  cout<<"Cond. Waiting....."<<endl;

  if(!pthread_cond_wait( &condvar,mux->getMutex() ))
  cout<<"Cond. wait returned.."<<endl;
}


void Waitsignal::signal()
{
  cout<<"Cond. Signalling....."<<endl;

  if(!pthread_cond_signal( &condvar))
    cout<<"Cond. signal returned.."<<endl;
}

void Waitsignal::broadcast()
{
  cout<<"Cond. Broadcasting....."<<endl;

  if(!pthread_cond_broadcast( &condvar))
    cout<<"Cond. Broadcast returned.."<<endl;

}

