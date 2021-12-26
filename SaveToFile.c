#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MatrixStruct.h"
#include "KGetLine.h"
#include "String.h"

void save_data_to_binary_file(Matrix * MATRIX, size_t nom) {
	getchar();
	printf("Enter the path to file where you wanna save data.");
	char * path = get_line();
	char * answer = NULL;
	printf("How would you like to open this file.\n");
	printf("1 - rewrite || 2 - append\n->");
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
	if (mode == 1)
		file = fopen(path, "wb");
	else if (mode == 2)
		file = fopen(path, "ab");
	else {
		free(path);
		return;
	}
	free(path);
	
	if (file == NULL) {
		printf("We cant open that file.\nCheck your path and try again.\n");
		sleep(3);
		return;
	}

	
	for (size_t i = 0; i < nom; ++i) {
		size_t h = MATRIX[i].height, w = MATRIX[i].width;
		fwrite(&MATRIX[i].height, sizeof(size_t), 1, file);
		fwrite(&MATRIX[i].width, sizeof(size_t), 1, file);
		fwrite(MATRIX[i].ptr, sizeof(double), h*w, file);
	}

	fclose(file);
}