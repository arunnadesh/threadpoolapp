#ifndef THREAD_H
#define THREAD_H

typedef enum thread_detach_state{
    TH_JOINABLE = 0,
    TH_DETACHED
} thread_detach_state;

typedef enum thread_scope{
    TH_SYSTEM_SCOPE= 0,
    TH_PROCESS_SCOPE
}thread_scope;

typedef enum  thread_cancel_state{
    TH_CANCEL_ENABLE,
    TH_CANCEL_DISABLE,
    TH_CANCEL_DEFERRED,
    TH_CANCEL_ASYNCHRONOUS
}thread_cancel_state;

typedef enum thread_ret_val{
    TH_SUCCESS =0,
    TH_FAILURE,
    TH_CANCELLED,
    TH_ERR_INSUFFICIENT_RESOURCE,
    TH_ERR_INVALID_ATTR,
    TH_ERR_PERMISSION_ERROR,
    TH_ERR_NOMEM,
    TH_ERR_DEADLOCK,
    TH_ERR_NOTFOUND,
    TH_ERR_NOTSUPPORTED
}thread_ret_val;

class Thread
{
    pthread_t  tId;
    pthread_attr_t tattr;
   public:
    thread_ret_val thread_attr_init(thread_detach_state edetachState=TH_JOINABLE, thread_scope eScope=TH_SYSTEM_SCOPE);
    thread_ret_val thread_create(void* (*funcPtr)(void*), void *funArg);
    thread_ret_val thread_join();
    thread_ret_val thread_cancel();
    static void thread_exit();
    thread_ret_val thread_detach();
    thread_ret_val thread_set_detachstate(thread_detach_state edetachState);
    thread_ret_val thread_set_scope(thread_scope eScope);
    thread_detach_state thread_get_detachstate();
    thread_scope thread_get_scope(thread_scope eScope);
    static unsigned long thread_query_id(void);
};

#endif //THREAD_H

