//#include "types.h"
//#include "stat.h"
//#include "user.h"

//int main () {
//	printf(1, "Works\n");
//	exit(0);
//}

#include "types.h"
#include "user.h"

int exitWait(void);

int main(int argc, char *argv[])
{
  printf(1, "\n This program tests the correctness of the new wait and exit systemcalls\n");
  
	exitWait();
	exit(0);
	return 0;
 }
  
int exitWait(void) {
	  int pid, ret_pid, exit_status;
       int i;
	printf(1, "\n  Parts a & b) testing exit(int status) and wait(int* status):\n");

  for (i = 0; i < 2; i++) {
    pid = fork();
    if (pid == 0) {
	if (i == 0)
      {
      printf(1, "\nThis is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      exit(0);
      }
      else
      {
	    printf(1, "\nThis is child with PID# %d and I will exit with status %d\n" ,getpid(), -1);
      exit(-1);
      } 
    }else if (pid > 0) {
	ret_pid = wait(&exit_status);
      printf(1, "\n This is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
    } else{
	printf(2, "\nError using fork\n");
    exit(-1);
    }
  }
  return 0;
}
