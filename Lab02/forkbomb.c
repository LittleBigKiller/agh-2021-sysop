#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
	while (1)
		fork();

	return 0;
}
