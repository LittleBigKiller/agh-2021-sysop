#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo) {
	printf("CAPTURE");
}

// Nie da się: SIGKILL (9), SIGSTOP (19)
// Nie zaimplementowane: SIGWAITING (32), SUGLWP (33)

int main(void) {
	for (int i = 1; i <= 64; i++) {
		if (signal(i, sig_handler) == SIG_ERR)
			printf("sig %d nie da się złapać\n", i);
	}

	return 0;
}
