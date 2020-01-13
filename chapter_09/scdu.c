#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "scdu.h"

void crypt_std(char *text, size_t n)
{
	int i, c;
	char base;

	for (i = 0; i < n; i++) {
		if ((text[i] >= 'a') && (text[i] <= 'z'))
			base = 'a';
		else if ((text[i] >= 'A') && (text[i] <= 'Z'))
			base = 'A';
		else
			continue;
		
		c = text[i] - base;
		c = (c + 1) % 26;
		text[i] = c + base;
	}
}

void decrypt_std(char *text, size_t n)
{
	int i, c;
	char base;

	for (i = 0; i < n; i++) {
		if ((text[i] >= 'a') && (text[i] <= 'z'))
			base = 'a';
		else if ((text[i] >= 'A') && (text[i] <= 'Z'))
			base = 'A';
		else
			continue;

		c = text[i] - base;
		c = (c - 1) % 26;
		text[i] = c + base;
	}
}

void load_funcs(char *module, func_t *crypt, func_t *decrypt)
{
	void *handler;

	if (module == NULL) {
		/* Use standard functions */
		*crypt = crypt_std;
		*decrypt = decrypt_std;

		return;
	}

	/* Try to load external functions */
	handler = dlopen(module, RTLD_NOW | RTLD_GLOBAL);
	if (!handler) {
		fprintf(stderr,
			"cannot load module %s\n", module);
		exit(EXIT_FAILURE);
	}

	*crypt = (func_t) dlsym(handler, "mod_crypt");
	if (!*crypt) {
		fprintf(stderr,
			"cannot find crypt() function: %s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	*decrypt = (func_t) dlsym(handler, "mod_decrypt");
	if (!*crypt) {
		fprintf(stderr,
			"cannot find decrypt() function: %s\n", dlerror());
		exit(EXIT_FAILURE);
	}
}

void usage(char *name, int status)
{
	fprintf(stderr,
		"usage: %s, [-h] [-d] [-f <module>] <text>\n", name);
	exit(status);
}

int main(int argc, char *argv[ ])
{
	bool do_decrypt = false;
	int errflg = 0;
	char *module = NULL, *text;
	func_t crypt, decrypt;
	int c, n;

	/* Parse the command line */
	while ((c = getopt(argc, argv, ":hdf:")) != -1) {
		switch(c) {
		case 'h':
			usage(argv[0], EXIT_SUCCESS);

		case 'd':
			do_decrypt = true;
			break;

		case 'f':
			module = optarg;
			break;

		case ':':       /* missing operand? */
			fprintf(stderr,
				"option -%c requires an operand\n",
				optopt);
			errflg++;
			break;

		case '?':	/* invalid option? */
			fprintf(stderr,
				"unrecognized option: '-%c'\n",

				optopt);
			errflg++;
		}
	}
	if (errflg)
		usage(argv[0], EXIT_FAILURE);
	if (optind == argc) {
		fprintf(stderr, "no input text\n");
		exit(EXIT_FAILURE);
	}
	text = argv[optind];

	/* Load standard or external function within a module */
	load_funcs(module, &crypt, &decrypt);

	/* Do the job */
	n = strlen(text);
	if (do_decrypt)
		decrypt(text, n);
	else
		crypt(text, n);

	/* Print the result */
	printf("%*s\n", n, text);

	return 0;
}
