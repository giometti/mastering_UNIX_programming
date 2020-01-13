#include <stdio.h>

#include "scdu.h"

void mod_crypt(char *text, size_t n)
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
                c = (c + 13) % 26;
                text[i] = c + base;
        }
}

void mod_decrypt(char *text, size_t n)
{
	mod_crypt(text, n);
}
