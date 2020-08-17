#include "types.h"
#include "user.h"

int InheritanceTest(void);

int main(int argc, char *argv[])
{
  printf(1, "\n This program tests the correctness of the new updatepriority systemcall and scheduling\n");
  
	InheritanceTest();
	exit(0);
	return 0;
 }
  
int InheritanceTest(void) {
	int pid, exit_status, i;
	int ret_pid = 1;
	printf(1, "\n  Lab 2 testing priority scheduling:\n");
	int temppid;
	pid = fork();
	if (pid == 0) {
		printf(1, "This is process PID# %d and I have priority 1\n", getpid()); 
		updatepriority(1, getpid());
		temppid = fork();
		if (temppid == 0) {
			printf(1, "This is process PID# %d and I inherited priority 1\n", getpid());
			updatepriority(3, getpid());
			int j;
                	for (j = 0; j < 50000000; j++) {}
                	exit(0);
		}
	}
	
	if (pid > 0) {
	for (i = 0; i < 3; i++) {
    		pid = fork();
    		if (pid == 0) {
			int j;
			for (j = 0; j < 50000000; j++) {}
			exit(0);
		}
	}
	}
	if (pid == 0) {
		int j;
		for (j = 0; j < 50000000; j++) {}
      		exit(0);
      	}
	
	while (ret_pid > 0) {
			ret_pid = wait(&exit_status);
                        printf(1, "\nThis is process PID# %d and I finished.\n", ret_pid);
	}
	printf(1, "DONE");
	exit(0);
	return 0;
}
