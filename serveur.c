#include "minitalk.h"

void handler(int sig)
{
    static int i = 0;
    static char c = 0;

    if (sig == SIGUSR1)
        c += 1 << i;
    i++;
    if (i == 8)
    {
        if (c == '\0')
        {
            printf("\n");
            exit(0);
        }
        printf("%c", c);
        i = 0;
        c = 0;
    }
}

int main (int arc, char **arv)
{
    pid_t pid;
    int i;

    (void)arv;
    if (arc != 1)
    {
        printf("Error: Invalid number of arguments");
        return (0);
    }
    pid = getpid();
    printf("pid: %d\n", pid);
	printf("message: \n");
    signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (0);
}