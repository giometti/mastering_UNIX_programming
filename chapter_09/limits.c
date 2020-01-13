#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/resource.h>

int rlimit_v[] = {
	RLIMIT_CORE,	RLIMIT_CPU,	RLIMIT_DATA,	RLIMIT_FSIZE,
	RLIMIT_NOFILE,	RLIMIT_STACK,	RLIMIT_AS
};
char *rlimit_n[] = {
	"RLIMIT_CORE",	"RLIMIT_CPU",	"RLIMIT_DATA",	"RLIMIT_FSIZE",
	"RLIMIT_NOFILE","RLIMIT_STACK", "RLIMIT_AS"
};

int res_n2v(char *n)
{
	int i;
	for (i = 0; i < 7; i++)
		if (strcmp(rlimit_n[i], n) == 0)
			break;
	if (i >= 7)
		return -1;
	return rlimit_v[i];
}

int main(int argc, char *argv[])
{
	int resource;
	struct rlimit rlim;
	bool do_set = false;
	int ret;

	/* Check the command line */
	if (!(argc == 2 || argc == 4)) {
		fprintf(stderr,
			"usage: %s <resource> "
				"[<soft-limit> <hard-limit>]\n",
			argv[0]);
		fprintf(stderr,
			"where <resource> can be: ");
		for (resource = 0; resource < 7; resource++)
			fprintf(stderr, "%s ", rlimit_n[resource]);
		fprintf(stderr, "\n");
		return -1;
	}
	resource = res_n2v(argv[1]);
	if (resource < 0) {
		fprintf(stderr, "invallid resource %s", argv[1]);
		return -1;

	}
	if (argc == 4) {
		rlim.rlim_cur = atoi(argv[2]);
		rlim.rlim_max = atoi(argv[3]);
		do_set = true;
	}

	if (do_set) {
		/* Try to set the new resource's values */
		ret = setrlimit(resource, &rlim);
		if (ret) {
			perror("setrlimit");
			return -1;
		}
	}

	/* Read the resource's values in order to print them */	
	ret = getrlimit(resource, &rlim);
	if (ret) {
		perror("getrlimit");
		return -1;
	}
	printf("limits for %s are soft=%lld; hard=%lld\n", argv[1],
		(long long) rlim.rlim_cur, (long long) rlim.rlim_max);

	return 0;
}
