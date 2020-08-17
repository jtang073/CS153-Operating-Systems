#include "types.h"
#include "user.h"

int priorityTest(void);

int main(int argc, char *argv[])
{
  printf(1, "\n This program tests the correctness of the new updatepriority systemcall and scheduling\n");
  
	priorityTest();
	exit(0);
	return 0;
 }
  
int priorityTest(void) {
	int pid, exit_status, i;
	int ret_pid = 1;
	printf(1, "\n  Lab 2 testing priority scheduling:\n");

	pid = fork();
	for (i = 0; i < 3; i++) {
    		pid = fork();
    		if (pid == 0) {
			if (getpid() == 6) {
      				printf(1, "\nThis is process PID# %d and I have priority of 1\n", getpid());
				updatepriority(1, getpid());
			}
			int j;
			for (j = 0; j < 25000000; j++) {}
			exit(0);
		}
	}
	if (pid == 0) {
		int j;
		for (j = 0; j < 25000000; j++) {}
      		exit(0);
      	}
	
	while (ret_pid > 0) {
			ret_pid = wait(&exit_status);
                        printf(1, "\nThis is process PID# %d and I finished.\n", ret_pid);
	}
	exit(0);
	return 0;
}
