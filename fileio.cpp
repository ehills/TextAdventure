#include "fileio.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
/*
 * This method is implemented from help given from:
 * http://www.gamedev.net/topic/399558-how-to-copy-a-file-in-c/
 *
 */
void copy_file(char* filename, char* new_filename) {
	int c;
	FILE *in,*out;
	in = fopen(filename, "r" );
	out = fopen( new_filename, "w" );
	if(in==NULL || !in) {
		return;
	} else if(out==NULL || !out) {
		return;
	}
	while((c=getc(in))!=EOF)
		putc(c,out);
	fclose(in);
	fclose(out);
}
