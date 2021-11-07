#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int g_s = 2;
int * g_d;

int main()
{
	pid_t pid;

	g_d = malloc(sizeof(int));
	g_d[0] = 3;

	int l_s = 4;
	int * l_d;
	l_d = malloc(sizeof(int));
	l_d[0] = 5;

	FILE * fptr = fopen("./test.txt", "w");
	char c;

	// fork a child process
	pid = fork();

	if (pid < 0) { // error occurred
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) { // child process
		// execlp("/bin/ls", "ls", NULL);
		
		int a;
		scanf("%d", &a);
		printf("CHILD = %d\n", a);
		
		printf("\nCHILD:\n");
		printf("pid = %ld\n", (long) getpid());
		printf("ppid = %ld\n", (long) getppid());

		/**/
		g_s = 0;
		g_d[0] = 0;
		l_s = 0;
		l_d[0] = 0;
		printf("g_s = %d\n", g_s);
		printf("g_d = %d\n", g_d[0]);
		printf("l_s = %d\n", l_s);
		printf("l_d = %d\n", l_d[0]);
		/**/
		/**/
		// Read contents from file
		fputs("CHILD - test put\n", fptr);
		fclose(fptr);
		/**/
	}
	else { // parent process
		// parent will wait for child to complete
		// wait(NULL);

		// getchar();
		
		// return 0;
		
		int b;
		scanf("%d", &b);
		printf("PARENT = %d\n", b); 

		printf("\nPARENT:\n");
		printf("pid = %ld\n", (long) getpid());
		printf("cpid = %ld\n", (long) pid);
		
		/**/
		printf("g_s = %d\n", g_s);
		printf("g_d = %d\n", g_d[0]);
		printf("l_s = %d\n", l_s);
		printf("l_d = %d\n", l_d[0]);
		/**/
		/**/
		// Read contents from file
		fputs("PARENTS - test put\n", fptr);
		fclose(fptr);
		/**/
	}

	return 0;
}
