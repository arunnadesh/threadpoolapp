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
            cout<<"Argument: "<<arg<<endl;
            cout<<"Value: "<<*(int*)arg<<endl;
        }

        void operator()(){
          cout<<"Argument: "<<arg<<endl;
          cout<<"Value: "<<*(int*)arg<<endl;
          (*func)(arg);
        }

};

#endif /* JOB_H */
