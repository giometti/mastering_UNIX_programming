#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	char *str; 
	int ret; 

	/* Print a prompt */
	printf("type a string> ");

	/* Read input data accepting strings holding
	 * character between a to z only
	 */
	errno = 0; 
	ret = scanf("%m[a-z]", &str); 
	if (ret != 1) { 
		if (errno != 0) { 
			perror("scanf"); 
			return -1;
		} else { 
			fprintf(stderr,
				"no matching characters\n"); 
			return 0;
		}
	} 

	/* Print read data */
	printf("read: %s\n", str); 
	free(str); 

	return 0;
}
