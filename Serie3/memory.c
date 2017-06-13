/* gcc -Wall ./memory.c -o memory */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* TODO: Insert System Type here
 * System used: Linux Ubuntu 64bit x86
 */

const int pageSize = 4096;

int calculate_page (uint32_t address) {
	return (int)address/pageSize;
}

int calculate_offset (uint32_t address , int page) {
	double afterComa = (double)address/pageSize- (double)page;
	return (int)(afterComa * pageSize);
}

int main(int argc, char *argv[])
{
	long long_input;
	uint32_t address;
	int offset , page;

	if (argc != 2) {
		printf("You must provide a parameter as input!\n");
		return -1;
	} else {
		long_input = atol(argv[1]);
		long supremum = pow(2 , 8*sizeof(uint32_t));
		if (long_input < 0 || long_input >= supremum) {
			printf("You must enter a valid 32bit address as parameter!\n");
			return -1;
		} else {
			printf("%ld\n", long_input);
			/*For some reason this only works for numbers <= 2147483647, after address is a negativ number although
			* it's declared as unsigned int*/
			address = (uint32_t) long_input;
		}
	}
	
	/* TODO: calculate values and generate correct output */
	page = calculate_page(address);
	offset = calculate_offset(address, page);
	printf("The address %u contains:\n", address);
	printf("page number = %i\n", page);
	printf("offset = %i\n", offset);
	
	return 0;
}
