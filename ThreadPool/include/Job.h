#ifndef JOB_H
#define JOB_H


class Job
{
  private:
      void (*func)(void*);
      void* arg;
       
  public:
        Job(void (*funcptr)(void*),void* funarg)
        {  
            func= funcptr;
            arg = funarg;
        }

        void operator()(){
          (*func)(arg);
        }

};

#endif /* JOB_H */
