#ifndef FILEIO_H_
#define FILEIO_H_
#include <fstream>
#include <iostream>
#include "constants.h"
using namespace std;

extern void copy_file(char* filename, char* new_filename);
extern void move_file(char* old_filename, char* new_filename);

#endif
