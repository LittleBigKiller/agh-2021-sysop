#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
	long long int ctr = 1;
	pid_t pid;

	while (1) {
		pid = fork();
		
		if (pid == 0) {
			while (1)
				sleep(1);
				
		} else if (pid > 0) {
			ctr += 1;
			printf("procesy: %d\n", ctr);
	
		} else {
			printf("fork failed!\tprocesy: %d\n", ctr);
			printf("fork() error: %s\n", strerror(errno));
			sleep(1);
		}

		usleep(1000);
	}

	return 0;
}
