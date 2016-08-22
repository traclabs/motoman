
#include <mprtl/task_ctrl.h>

#include <stdio.h>  // printf
#include <stdlib.h> // malloc, free
#include <string.h> // strerror
#include <unistd.h> // usleep
#include <errno.h>  // errno

#include <pthread.h>
#include <semaphore.h>


#include "robot_config.h" // max num tasks



#define LOCAL_SEMA 0



// Helpers /////////////////////////////////////////////////////////////////////


__attribute__((constructor))
static void __init_task_list()
{
  // TODO: start periodic timer thread here as well
}


__attribute__((destructor))
static void __deinit_task_list()
{
}





// make these lists
pthread_t tasks_prio_high[FAKE_ROBOT_MAX_NUM_TASKS_PRIO_HIGH];
pthread_t tasks_prio_norm[FAKE_ROBOT_MAX_NUM_TASKS_PRIO_NORMAL];


#define MAX_NUM_SEMA 10
sem_t semaphores[MAX_NUM_SEMA];


typedef struct
{
  int task_nr;
  int args[10];
  FUNCPTR func;
} task_struct_t;


void* thread_wrapper(void* arg)
{
  task_struct_t* task = (task_struct_t*) arg;

  printf("thread_wrapper(%d): starting wrapped task ..\n", task->task_nr);

  task->func(task->args[0], task->args[1], task->args[2], task->args[3],
    task->args[4], task->args[5], task->args[6], task->args[7],
    task->args[8], task->args[9]);

  printf("thread_wrapper(%d): wrapped task exited\n", task->task_nr);
  pthread_exit(NULL);
}


static task_struct_t* new_task(FUNCPTR func, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10)
{
  task_struct_t* task = (task_struct_t*) calloc(sizeof(task_struct_t), 1);

  task->func    = func;
  task->args[0] = arg1;
  task->args[1] = arg2;
  task->args[2] = arg3;
  task->args[3] = arg4;
  task->args[4] = arg5;
  task->args[5] = arg6;
  task->args[6] = arg7;
  task->args[7] = arg8;
  task->args[8] = arg9;
  task->args[9] = arg10;

  return task;
}




// Task Control API ////////////////////////////////////////////////////////////

int mpCreateTask(int priority, int stackSize, FUNCPTR entryPt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10)
{
  int ret_;
  static int num_tasks_ = 0;
  pthread_attr_t attr_;

  // TODO: make sure we are not > MAX_NUM_TASKS

  printf("mpCreateTask(%d): prio: %d, stackSz: %d, args: 0x%x, 0x%x, 0x%x, 0x%x\n",
         num_tasks_, priority, stackSize, arg1, arg2, arg3, arg4);

  // according to the docs, this would be an error
  if (stackSize != MP_STACK_SIZE)
  {
    printf("mpCreateTask(%d): ERROR, stackSize (%d) != MP_STACK_SIZE (%d)\n",
      num_tasks_, stackSize, MP_STACK_SIZE);
    return ERROR;
  }

  // TODO: this leaks, but ok
  task_struct_t* task = new_task(entryPt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
  task->task_nr = num_tasks_;

  pthread_attr_init(&attr_);
  pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_DETACHED);
  pthread_attr_setstacksize(&attr_, MP_STACK_SIZE);

  if ((ret_ = pthread_create(&tasks_prio_norm[num_tasks_], &attr_, thread_wrapper, (void*) task)) != 0)
  {
    printf("mpCreateTask(%d): failed to create task: %s (%d)\n",
      num_tasks_, strerror(ret_), ret_);
    return ERROR;
  }

  printf("mpCreateTask(%d): created task\n", num_tasks_);

  // use the task nr as TID for now
  return num_tasks_++;
}


STATUS mpDeleteTask(int tid)
{
  int ret;

  printf("mpDeleteTask(%d): trying to stop and delete task/thread\n", tid);

  if ((ret = pthread_cancel(tasks_prio_norm[tid])) != 0)
  {
    printf("mpDeleteTask(%d): error cancelling thread: %d\n", tid, ret);
    return ERROR;
  }

  printf("mpDeleteTask(%d): stopped thread\n", tid);

  return OK;
}


STATUS mpTaskDelay(int ticks)
{
  // for DEBUG
  if (ticks == 10000)
  {
    printf("mpTaskDelay: ignoring request for delay of %d ticks (controller init)\n", ticks);
    return OK;
  }

  unsigned int ms = ticks * MP_MS_PER_TICK;
  //printf("mpTaskDelay: %d ms\n", ms);
  return usleep(ms * 1000);
}


SEM_ID mpSemBCreate(int options, SEM_B_STATE initialState)
{
  int ret;
  static int num_sems = 0;

  printf("mpSemBCreate(%d): options: %d, initialState: %d\n",
    num_sems, options, initialState);

  if (num_sems == MAX_NUM_SEMA)
  {
    printf("mpSemBCreate(%d): failed to create semaphore: limit reached (%d)\n",
      num_sems, MAX_NUM_SEMA);

    // 0 is error for this function according to docs
    return 0;
  }

  if ((ret = sem_init(&semaphores[num_sems], LOCAL_SEMA, initialState)) != 0)
  {
    printf("mpSemBCreate(%d): error creating semaphore: %s (%d)\n",
           num_sems, strerror(errno), errno);
    // 0 is error for this function according to docs
    return 0;
  }

  printf("mpSemBCreate(%d): initialised semaphore\n", num_sems);

  return num_sems++;
}


STATUS mpSemTake(SEM_ID semId, int timeout)
{
  // http://www.vxdev.com/docs/vx55man/vxworks/ref/semLib.html#semTake
  //printf("mpSemTake(%d): timeout: %d\n", semId, timeout);

  // TODO: use sem_timedwait() here instead
  //printf("mpSemTake(%d): WARN: ignoring timeout\n", semId);

  return sem_wait(&semaphores[semId]);
}


STATUS mpSemGive(SEM_ID semId)
{
  // http://www.vxdev.com/docs/vx55man/vxworks/ref/semLib.html#semGive
  //printf("mpSemGive(%d)\n", semId);
  return sem_post(&semaphores[semId]);
}


STATUS mpClkAnnounce(int clk_id)
{
  //printf("mpClkAnnounce - no-op?\n");
  // TODO: for a periodic task, this probably yields the CPU, then expects
  //       the OS to suspend the task until its period runs to its end

  // TODO: fake some sort of periodic task system using a mutex or
  //       condition variable.
  mpTaskDelay(10);

  return ERROR;
}
