#include <stdio.h>
#include "MatrixStruct.h"
#include <stdlib.h>
#include "String.h"
#include "KGetLine.h"

void print_data(Matrix * MATRIX, size_t nom, char mode) {
	switch (mode) {
		case -1: {
			getchar();
			for (size_t i = 0; i < nom; ++i) {
				printf("The %ld matrix:\n", i+1);
				printf("SIZE: %ldx%ld\n", MATRIX[i].height, MATRIX[i].width);
				for (size_t j = 0; j < MATRIX[i].height; ++j) {
					for (size_t k = 0; k < MATRIX[i].width; ++k)
						printf("%5.lf", MATRIX[i].ptr[j*MATRIX[i].width+k]);
					printf("\n");
				}
			}
			char * answer = get_line();
			free(answer);
			}
			break;
		case 0: {
			getchar();
			printf("Enter index here:\n-> ");
			char * answer = get_line();
			while (is_digit(answer) == 0) {
				free(answer);
				printf("-> ");
				answer = get_line();
			}
			size_t i = atoi(answer);
			free(answer);

			if (i < 0 || i > nom-1)
				break;

			printf("The %ld matrix:\n", i+1);
			printf("SIZE: %ldx%ld\n", MATRIX[i].height, MATRIX[i].width);
			for (size_t j = 0; j < MATRIX[i].height; ++j) {
				for (size_t k = 0; k < MATRIX[i].width; ++k)
					printf("%6.lf", MATRIX[i].ptr[j*MATRIX[i].width+k]);
				printf("\n");
			}
			answer = get_line();
			free(answer);
			}
			break;
		default:
			break;
	}
}