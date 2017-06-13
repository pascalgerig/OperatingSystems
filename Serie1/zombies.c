/* gcc -Wall -std=gnu99 zombies.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void panic (const char *serror)
{
	printf("%s", serror);
	exit(1);
}

void create_zombie() {
	/* TODO: Implement child process and kill it */
	int pid = fork();
	if(pid < 0)
	{
		panic("fork failed");
	}

	else if(pid > 0)
	{
		/*Parent Process Does nothing*/
	}

	else
	{
		/*kill child Process*/
		exit(0);
	}	

	return;
}

int main(void)
{
	int wait = 15;
	/* TODO: implement */
	create_zombie();
	sleep(wait);
	/*There is no need to ask for the Status of the child to remove it since
	it gets removed automatically when the parent gets removed*/
	return 0;
}
