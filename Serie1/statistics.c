/* gcc -Wall -pthread statistics.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int max;
int min;
float avg;
int len;

/*Used for communication between process and threads*/
struct Communicator
{
	int* firstelement;
	int* minimum;
	int* maximum;
	float* average;
};

void *average(void *val) {
	/* TODO */
	struct Communicator* comm = (struct Communicator*) val;
	float sum = 0;
	int i;
	for (i = 0; i < len; i++)
	{
		sum += comm->firstelement[i];	
	}
	*(comm->average) = sum/len;
	
	return NULL;
}

void *minimum(void *val) {
	/* TODO */
	struct Communicator* comm = (struct Communicator*) val;
	
	*(comm->minimum) = comm->firstelement[0];
	int i;
	for(i = 1; i < len; i++)
	{
		if(comm->firstelement[i] < *(comm->minimum))
		{
			*(comm->minimum) = comm->firstelement[i];
		}
	}
	return NULL;
}

void *maximum(void *val) {
	/* TODO */
	struct Communicator* comm = (struct Communicator*) val;
	
	*(comm->maximum) = comm->firstelement[0];
	int i;
	for(i = 1; i < len; i++)
	{
		if(comm->firstelement[i] > *(comm->maximum))
		{
			*(comm->maximum) = comm->firstelement[i];
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t thread0;
	pthread_t thread1;
	pthread_t thread2;

	if (argc < 3) {
		printf("You have to supply at least 2 integers as arguments!\n");
		return 0;
	}
	len = argc - 1;
	int i;
	int array[len];

	/*stors command line parameters as integers*/
	char character;
	for (i = 1; i<argc; i++)
	{
		if(sscanf(argv[i], "%d%c", &array[i-1],&character) != 1)
		{
			printf("wrong usage\n");
			return 0;
		}
	}
	
	struct Communicator comm;
	comm.minimum = &min;
	comm.maximum = &max;
	comm.average = &avg;
	comm.firstelement = &array[0];

	pthread_create(&thread0, NULL, minimum, &comm);
	pthread_create(&thread1, NULL, maximum, &comm);
	pthread_create(&thread2, NULL, average, &comm);
	
	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Average: %f\n" , avg);
	printf("Maximum: %i\n" , max);
	printf("Minimum: %i\n" , min);

	return 0;
}
