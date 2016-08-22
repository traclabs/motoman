#ifndef FAKE_MOTOPLUS_TASK_CTRL_H__
#define FAKE_MOTOPLUS_TASK_CTRL_H__


#include "mptypes.h"

// TODO: unfortunately needed (mpExitUsrRoot)
#include <pthread.h>


// Task Control API ////////////////////////////////////////////////////////////

typedef int SEM_ID;
typedef int SEM_B_STATE;


// TODO: these values are guesses
#define MP_PRI_TIME_NORMAL 0
#define MP_PRI_IP_CLK_TAKE 3

#define MP_STACK_SIZE (20 * 1024) // 20 kB

// TODO: bit of a kludge
#define mpExitUsrRoot do { \
  pthread_exit(NULL); \
} while(0);

// TODO: kludge 2
#define mpDeleteSelf mpExitUsrRoot

// TODO: move this somewhere else
#define FOREVER for (;;)

#define SEM_EMPTY      0
#define SEM_FULL       1
#define SEM_Q_FIFO     0x0
#define SEM_Q_PRIORITY 0x1


int    mpCreateTask(int priority, int stackSize, FUNCPTR entryPt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10);
STATUS mpDeleteTask(int tid);
SEM_ID mpSemBCreate(int options, SEM_B_STATE initialState);
STATUS mpSemGive(SEM_ID semId);
STATUS mpSemTake(SEM_ID semId, int timeout);
STATUS mpTaskDelay(int ticks);
STATUS mpClkAnnounce(int clk_id);


#endif // FAKE_MOTOPLUS_TASK_CTRL_H__
