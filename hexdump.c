#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "hexdump.h"

void
hexdump(FILE *fp, unsigned char *buf, size_t len)
{
	size_t i, j;

	for (i=0; i<len; i+=16) {
		fprintf(fp, "%08x  ", (unsigned int)i);

		for (j=0; j<16 && (i+j)<len; j++) {
			if (j == 8) fprintf(fp, " ");
			fprintf(fp, "%02x ", buf[i+j]);
		}

		for (; j<16; j++) {
			if (j == 8) fprintf(fp, " ");
			fprintf(fp, "   ");
		}

		fprintf(fp, "  ");

		for (j=0; j<16 && (i+j)<len; j++) {
			unsigned char ch = buf[i+j];
			if (!isprint(ch)) ch = '.';
			fprintf(fp, "%c", ch);
		}

		fprintf(fp, "\n");
	}
}
