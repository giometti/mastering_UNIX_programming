#include <stdio.h>
#include <string.h>

char lut[] = "TUucEkVGoCxyzmFLdQYSWswanihqgAOvrXKJHZNBfpPjeIDlRtbM";

void mod_crypt(char *text, size_t n)
{
        int i;

	for (i = 0; i < n; i++) {
                if ((text[i] >= 'a') && (text[i] <= 'z'))
                        text[i] = lut[text[i] - 'a' + 26];
                else if ((text[i] >= 'A') && (text[i] <= 'Z'))
                        text[i] = lut[text[i] - 'A'];
                else
                        continue;
        }
}

void mod_decrypt(char *text, size_t n)
{
        int i;
	char *ptr;
	int base;

        for (i = 0; i < n; i++) {
		ptr = strchr(lut, text[i]);
		if (!ptr)
			continue;

        	base = ptr - lut;
		if (base < 26)
			text[i] = base + 'A';
		else if (base >= 26)
			text[i] = base - 26 + 'a';
        }
}
