#ifndef WAITSIGNAL_H
#define WAITSIGNAL_H

class Waitsignal{
         pthread_cond_t condvar;
      public:
         Waitsignal();
         void wait(Mutex *mux);
         void signal();
         void broadcast();
};

#endif
