#include "MatrixStruct.h"

#ifndef INPUT
#define INPUT
void read_from_terminal(Matrix ** MATRIX, size_t * nom_);
double * generate(size_t height, size_t width);
void random_generation(Matrix ** MATRIX, size_t * nom_);
void ReadFromFile(Matrix ** MATRIX, size_t * nom);
#endif