#include <iostream>
using namespace std;


#include "Job.h"
#include "Threadpool.h"


int jobID[10]={0,1,2,3,4,5,6,7,8,9};
void  testFun(void* jobno)
{
   cout<<"Executing job.....:"<< *((int*)jobno) <<endl;
   sleep(10);
}

int main()
{
    Threadpool thPool(3);

    if(TH_POOL_CREATE_SUCCESS == thPool.threadpool_create()) {

        for(int i=0; i<10; i++){

              Job* jb =  new Job(&testFun, &jobID[i]);
              if(jb){
                 cout<<"Adding new job index: "<<jobID[i]<<endl;
                 thPool.threadpool_add_job(jb);
              }
        }
    }


   sleep(30);

   thPool.threadpool_destroy();

   // TODO: delete worker objects

   cout << "Exiting app..." << endl;

   return 0;


}

