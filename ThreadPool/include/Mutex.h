#ifndef MUTEX_H
#define MUTEX_H

class Mutex
{
   pthread_mutex_t mlock;
  public:

   Mutex();
   void lock();
   void unlock();
   pthread_mutex_t* getMutex();
};
#endif
