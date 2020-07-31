#include "types.h"
#include "user.h"

int WaitPidTest(void);

int main(int argc, char *argv[])
{
  printf(1, "\n This program tests the correctness of the new waitpid systemcalls\n");
  
	WaitPidTest();
	exit(0);
	return 0;
 }
  
int WaitPidTest(void) {
	int pid, ret_pid, exit_status;
       	int i;
	printf(1, "\n  Parts c) testing waitpid(int pid, int* status, int options):\n");

  	for (i = 0; i < 4; i++) {
    		pid = fork();
    		if (pid == 0) {
			if (i == 0) {
      				printf(1, "\nThis is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      				exit(0);
      			}
    		}
	//}
	if (pid != 0) {
		printf(1, "\nWaiting for child PID# %d\n", pid);
		ret_pid = waitpid(pid, &exit_status, 0);
      		printf(1, "\n This is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
  	}
	}
	return 0;
}
