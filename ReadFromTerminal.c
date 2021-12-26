#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "KGetLine.h"
#include "String.h"
#include "MatrixStruct.h"

void read_from_terminal(Matrix ** MATRIX, size_t * nom_) {
	getchar();
	size_t nom = *nom_;
	char * answer = NULL;

	printf("How many matrixes would you like to enter?\n");
	do {
		printf("-> ");
		//printf("hi");
		//sleep(2);
		answer = get_line();
		//getchar();
	} while (is_digit(answer) == 0);
	size_t n = atoi(answer);
	free(answer);

	for (size_t i = 0; i < n; ++i) {
		double * m = NULL;
		system("@cls||clear");
		printf("%ld new matrix.\n", i+1);
		printf("HEIGHT: ");
		printf("-> ");
		answer = get_line();
		while (is_digit(answer) == 0) {
			free(answer);
			printf("-> ");
			answer = get_line();
		}
		size_t height = atoi(answer);
		free(answer);

		printf("WIDTH: ");
		answer = get_line();
		while (is_digit(answer) == 0) {
			free(answer);
			printf("-> ");
			answer = get_line();
		}
		size_t width = atoi(answer);
		free(answer);

		m = (double*) malloc(sizeof(double) * width*height);
		for (size_t j = 0; j < height; ++j) {
			printf("%ld: ", j);
			char * line = get_line();
			while (line == NULL) {
				free(line);
				line = get_line();
				//getchar();
			}

			char ** words = NULL;
			size_t now = 0;
			words = (char**) malloc(sizeof(char*));
			words[0] = strtok(line, " ");
			now++;
			while(words[now-1]) {
				words = (char**) realloc(words, sizeof(char*)*(now+1));
				words[now] = strtok(NULL, " ");
				now++;
			}

			now--;
			words = (char**) realloc(words, sizeof(char*)*(now));
			//for (size_t k = 0; k < now; ++k)
				//printf("%s\n", words[k]);

			//now--;
			if (now != width) {
				printf("Enter ERROR!\n");
				sleep(3);
				//size_t k = 0;
				//while (k < now)
					//free(words[k++]);
				free(words);
				free(line);
				free(m);
				free(answer);
				return;
			}

			//преобразуем строки в числа
			for (size_t k = 0; k < width; ++k)
				m[j*width+k] = atof(words[k]);

			//size_t k = 0;
			//while (k < now)
				//free(words[k++]);
			free(words);
			free(line);
		}
		(*MATRIX) = (Matrix *) realloc((*MATRIX), sizeof(Matrix)*(*nom_+1));
		(*MATRIX)[*nom_].ptr = m;
		(*MATRIX)[*nom_].height = height;
		(*MATRIX)[*nom_].width = width;
		(*nom_)++;
		//free(m);
	}

	free(answer);
}