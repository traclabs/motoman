
#include <stdio.h>
#include <sysexits.h>
#include <signal.h>


// declared in mpMain.c
extern void mpUsrRoot(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10);


void sig_handler(int signum)
{
  printf("main: sig_handler: caught SIGPIPE (%d)\n", signum);
}


int main(int argc, char *argv[])
{
  // install global signal handler for SIGPIPE, so we can avoid
  // closing/closed sockets from terminating the entire process.
  // StateServer does this
  // TODO: this is a bit of a hack
  signal(SIGPIPE, sig_handler);

  // start main MotoRos task
  printf("main: MotoRosEmu for " MRE_CTRLR "\n"
    "main: use ctrl+c to quit\n"
    "main: jumping to mpUsrRoot(..) entry-point ..\n"
    "--------------------------------------------------------------------------------\n");

  mpUsrRoot(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  // probably unreachable
  printf("--------------------------------------------------------------------------------\n"
    "main: exit\n");

  return EX_OK;
}
