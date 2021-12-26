#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MatrixStruct.h"
#include "KGetLine.h"
#include "String.h"

void ReadFromFile(Matrix ** MATRIX, size_t * nom) {
	getchar();
	printf("Enter the path to file where you wanna read data.\n-> ");
	char * path = get_line();
	char * answer = NULL;
	printf("How would you like to read from this file.\n");
	printf("1 - delete old matrixes || 2 - append new matrixes to old\n->");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("-> ");
		answer = get_line();
	}
	int mode = atoi(answer);
	free(answer);

	if (mode < 1 || mode > 2) {
		printf("Your number out of range!\n");
		sleep(2);
		free(path);
		return;
	}

	FILE * file;
	file = fopen(path, "rb");
	free(path);
	
	if (file == NULL) {
		printf("We cant open that file.\nCheck your path and try again.\n");
		sleep(3);
		return;
	}

	if (mode == 1) {
		*nom = 0;
		for (size_t i = 0; i < *nom; ++i) {
			free((*MATRIX)[i].ptr);
		}
		free(*MATRIX);
		(*MATRIX) = (Matrix*) malloc(0);
	}

	//fseek(file, 0, SEEK_SET);
	size_t flag = 1;
	while (flag) {
		if (*MATRIX)
			(*MATRIX) = (Matrix*) realloc((*MATRIX), sizeof(Matrix)*(*nom+1));
		else
			(*MATRIX) = (Matrix*) malloc(sizeof(Matrix));
		size_t n = fread(&(*MATRIX)[*nom].height, sizeof(size_t), 1, file);
		if (!n) {
			if (*nom)
				(*MATRIX) = (Matrix*) realloc((*MATRIX), sizeof(Matrix)*(*nom));
			else {
				free(*MATRIX);
				(*MATRIX) = NULL;
			}
			break;
		}
		n = fread(&(*MATRIX)[*nom].width, sizeof(size_t), 1, file);
		printf("%ld x %ld\n", (*MATRIX)[*nom].height, (*MATRIX)[*nom].width);
		getchar();

		size_t h = (*MATRIX)[*nom].height;
		size_t w = (*MATRIX)[*nom].width;

		(*MATRIX)[*nom].ptr = (double*) malloc(h*w*sizeof(double));
		flag = fread((*MATRIX)[*nom].ptr, sizeof(double), h*w, file);
		for (size_t i = 0; i < h*w; ++i)
			printf("%lf ", (*MATRIX)[*nom].ptr[i]);
		printf("n: %ld\n", flag);
		(*nom)++;
		getchar();
		//break;
	}
	fclose(file);
}