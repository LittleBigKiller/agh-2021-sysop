#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo)
{
	printf("CAPTURE");
}

// Nie da się: SIGKILL, SIGSTOP

int main(void)
{
	if (signal(SIGHUP, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGHUP\n");
	
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGINT\n");

	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGQUIT\n");

	if (signal(SIGILL, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGILL\n");


	if (signal(SIGTRAP, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGTRAP\n");

	if (signal(SIGABRT, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGABRT\n");

	if (signal(SIGBUS, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGBUS\n");

	if (signal(SIGFPE, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGFPE\n");


	if (signal(SIGKILL, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGKILL\n");

	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGUSR1\n");

	if (signal(SIGSEGV, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGSEGV\n");

	if (signal(SIGUSR2, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGUSR2\n");


	if (signal(SIGPIPE, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGPIPE\n");

	if (signal(SIGALRM, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGALRM\n");

	if (signal(SIGTERM, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGTERM\n");


	if (signal(SIGCHLD, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGCHLD\n");

	if (signal(SIGCONT, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGCONT\n");

	if (signal(SIGSTOP, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGSTOP\n");

	if (signal(SIGTSTP, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGTSTP\n");


	if (signal(SIGTTIN, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGTTIN\n");

	if (signal(SIGTTOU, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGTTOU\n");

	if (signal(SIGURG, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGURG\n");

	if (signal(SIGXCPU, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGXCPU\n");


	if (signal(SIGXFSZ, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGXFSZ\n");

	if (signal(SIGVTALRM, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGVTALRM\n");

	if (signal(SIGPROF, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGPROF\n");

	if (signal(SIGWINCH, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGWINCH\n");


	if (signal(SIGSYS, sig_handler) == SIG_ERR)
		printf("\nNie można złapać SIGSYS\n");

	while(1)
		sleep(1);

	return 0;
}
