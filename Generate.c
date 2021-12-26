#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MatrixStruct.h"
#include "string.h"
#include "KGetLine.h"

double * generate(size_t height, size_t width) {
	double * m = (double*) malloc(sizeof(double)*height*width);
	srand(time(NULL));
	for (size_t i = 0; i < height; ++i)
		for (size_t j = 0; j < width; ++j)
			m[i*width+j] = ((double) (rand()%10000))/100-50;

	return m;
}

void random_generation(Matrix ** MATRIX, size_t * nom_) {
	getchar();
	printf("Enter a height of new matrixes.\n");
	printf("HEIGHT: ");
	char * answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("ERROR!\n->");
		answer = get_line();
	}
	int height = atoi(answer);
	free(answer);

	printf("Enter a width of new matrixes.\n");
	printf("WIDTH: ");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("ERROR!\n->");
		answer = get_line();
	}
	int width = atoi(answer);
	free(answer);

	printf("Enter, how many matrixes with this sizes would you like to generate.\n");
	printf("NUMBER: ");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("ERROR!\n->");
		answer = get_line();
	}
	size_t number = (size_t) atoi(answer);
	printf("%ld\n", number);
	free(answer);

	size_t nom = *nom_;
	*nom_ += number;
	//Matrix * M = (*MATRIX);
	for (size_t i = 0; i < number; ++i) {
		double * m = generate(height, width);
		(*MATRIX) = (Matrix*) realloc((*MATRIX), sizeof(Matrix)*(nom+1));
		printf("hi\n");
		(*MATRIX)[nom].ptr = m; printf("ptr\n");
		(*MATRIX)[nom].height = height;
		(*MATRIX)[nom].width = width;
		nom++;
	}
}