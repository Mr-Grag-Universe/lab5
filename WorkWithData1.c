#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MatrixStruct.h"
#include "KGetLine.h"
#include "String.h"

void printMatrix(Matrix* m) {
    printf("SIZE: %ldx%ld\n", m->height, m->width);
    for (size_t ii = 0; ii < m->height; ++ii) {
        for (size_t k = 0; k < m->width; ++k)
            printf("%6.2lf", m->ptr[ii * m->width + k]);
        printf("\n");
    }
}

Matrix * insert_row(Matrix* MATRIX, double* m,int i) {
	size_t w = MATRIX->width, h = MATRIX->height;
    Matrix * M = malloc(sizeof(Matrix));
    M->ptr = malloc(sizeof(double)*(h+1)*w);
    M->width = w;
    M->height = h+1;
    h++;

    double * donor = MATRIX->ptr;
    double * recipient = M->ptr;
    if (i != 0)
    	memcpy(recipient, donor, w*i*sizeof(double));
    donor = m;
    recipient = M->ptr + w*i;
    memcpy(recipient, donor, w*sizeof(double));
    donor = MATRIX->ptr + w*i;
    recipient = M->ptr + w*(i+1);
    memcpy(recipient, donor, ((h-1)*w - w*i)*sizeof(double));
    printMatrix(M);
    return M;
}

Matrix * insert_column(Matrix* MATRIX, double* m,int i) {
	size_t w = MATRIX->width, h = MATRIX->height;
    Matrix * M = malloc(sizeof(Matrix));
    M->ptr = malloc(sizeof(double)*(h+1)*w);
    M->width = w+1;
    M->height = h;
    w++;

    double * donor;
    double * recipient;
	for (size_t i = h; i > 0; --i) {
		donor = MATRIX->ptr + (w-1)*h + i-(w-1);
		recipient = M->ptr + w*h - w*(h-i) - (w-1-i);
		// перед места вставки
		memmove(recipient, donor, sizeof(double)*(w-i-1));
		// вставим элемент
		memcpy(recipient-1, m+i-1, sizeof(double));
		// подтаскиваем оставшееся
		memmove(recipient-i-1, donor-i, sizeof(double)*i);
        donor = donor - (w-1);
	}

    printMatrix(M);
    return M;
}

void insert(Matrix ** MATRIX, size_t * nom_) {
	size_t nom = *nom_;
	getchar();
	char * answer = NULL;
	printf("What would you like to insert?\n");
	printf("1 - column || 2 - row\n->");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("-> ");
		answer = get_line();
	}
	int n = atoi(answer);
	free(answer);

	if (n < 1 || n > 2) {
		printf("Your number is out of range!\n");
		sleep(2);
		return;
	}
	
	printf("Which Matrix would you like to change?\nEnter index of it: ");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("-> ");
		answer = get_line();
	}
	size_t ind = atol(answer);
	free(answer);

	if (ind < 0 || ind > nom-1) {
		printf("Your index is out of range!\n");
		sleep(2);
		return;
	}

	printf("Where do you wanna insert your this?\nEnter index of it: ");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("-> ");
		answer = get_line();
	}
	size_t ind_n = atol(answer);
	free(answer);

	size_t width = (*MATRIX)[ind].width, height = (*MATRIX)[ind].height;
	printf("This Matrix's size: %ld x %ld.\n", height, width);

	if (ind_n < 0 || (ind_n > width && n == 1) || (ind_n > height && n == 2)) {
		printf("Your index is out of range!\n");
		sleep(2);
		return;
	}


	if (n == 2) {
		double * m = (double*) malloc(sizeof(double) * width);
		// ввод новой строки
		printf("Enter your row here: ");
		char * line = get_line();
		while (line == NULL) {
			free(line);
			printf("-> ");
			line = get_line();
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

		if (now != width) {
			printf("Enter ERROR!\n");
			sleep(3);
			free(words);
			free(line);
			free(m);
			return;
		}

		//преобразуем строки в числа
		for (size_t k = 0; k < width; ++k)
			m[k] = atof(words[k]);
		free(words);
		free(line);
		
		Matrix* M = insert_row((*MATRIX)+ind, m, ind_n);
		free((*MATRIX)[ind].ptr);
		(*MATRIX)[ind] = *M;
		free(M);
		//getchar();
		free(m);
        //*nom_ += width;
	}
	else {
		double * m = (double*) malloc(sizeof(double) * height);
		// ввод новой строки
		printf("Enter your column here:\n");

		for (size_t i = 0; i < height; ++i) {
			printf("-> ");
			answer = get_line();
			while (is_float(answer) == 0) {
				free(answer);
				printf("retry -> ");
				answer = get_line();
			}
			m[i] = atof(answer);
			free(answer);
		}

		Matrix* M = insert_column((*MATRIX)+ind, m, ind_n);
		free((*MATRIX)[ind].ptr);
		(*MATRIX)[ind] = *M;
		free(M);
		free(m);
        //*nom_ += height;
	}
}

Matrix *delete_row(Matrix * MATRIX, size_t ind_n) {
    size_t w = MATRIX->width, h = MATRIX->height;
    Matrix * M = malloc(sizeof(Matrix));
    M->ptr = malloc(sizeof(double)*(h-1)*w);
    M->width = w;
    M->height = h-1;
    h--;

    double * donor = MATRIX->ptr;
    double * recipient = M->ptr;
    memmove(recipient, donor, w*ind_n*sizeof(double));
    donor = MATRIX->ptr + w*(ind_n+1);
    recipient = M->ptr + w*ind_n;
    memmove(recipient, donor, ((1+h)*w - w*(1+ind_n))*sizeof(double));
    printMatrix(M);
    return M;
}

Matrix * delete_column(Matrix * MATRIX, size_t ind_n) {
    double * donor = MATRIX->ptr + 1+ind_n;
    size_t w = MATRIX->width, h = MATRIX->height;
    Matrix * M = (Matrix*) malloc(sizeof(Matrix));
    M->ptr = (double*) malloc(sizeof(double)*h*(w-1));
    M->width = w-1;
    w--;
    M->height = h;
    for (size_t i = 0; i < h; ++i) {
        donor = MATRIX->ptr + (w+1)*i;
        double * recipient = M->ptr + w*i;
        //printf("%lf, %lf\n", *donor, *recipient);
        if (ind_n != 0)
            memcpy(recipient, donor, ind_n*sizeof(double));
        donor = MATRIX->ptr + (w+1)*i+ind_n+1;
        recipient = M->ptr + w*i + ind_n;
        //printf("%lf, %lf\n", MATRIX->ptr[(w+1)*i+ind_n+1], M->ptr[w*i + ind_n]);
        memcpy(recipient, donor, (w-ind_n)*sizeof(double));
    }

    printMatrix(M);
    return  M;
}

void delete(Matrix ** MATRIX, size_t * nom_) {
    size_t nom = *nom_;
    getchar();
    char * answer = NULL;
    printf("What would you like to insert?\n");
    printf("1 - column || 2 - row\n->");
    answer = get_line();
    while (is_digit(answer) == 0) {
        free(answer);
        printf("-> ");
        answer = get_line();
    }
    int n = atoi(answer);
    free(answer);

    if (n < 1 || n > 2) {
        printf("Your number is out of range!\n");
        sleep(2);
        return;
    }

    printf("Which Matrix would you like to change?\n-> ");
    answer = get_line();
    while (is_digit(answer) == 0) {
        free(answer);
        printf("-> ");
        answer = get_line();
    }
    size_t ind = atol(answer);
    free(answer);

    if (ind < 0 || ind > nom-1) {
        printf("Your index is out of range!\n");
        sleep(2);
        return;
    }

    size_t width = (*MATRIX)[ind].width, height = (*MATRIX)[ind].height;
    printf("This Matrix's size: %ld x %ld.\n", height, width);
    printMatrix(MATRIX[ind]);

    if (n == 1) {
        if (width == 1) {

        }
        printf("Which column would you like to delete?\n-> ");
        answer = get_line();
        while (is_digit(answer) == 0) {
            free(answer);
            printf("-> ");
            answer = get_line();
        }
        long int ind_n = atol(answer);
        free(answer);

        if (ind_n < 0 || (ind_n > width - 1 && n == 1) || (ind_n > height - 1 && n == 2)) {
            printf("Your index is out of range!\n");
            sleep(2);
            return;
        }

        Matrix * M = delete_column(((*MATRIX)+ind), ind_n);
        free((*MATRIX)[ind].ptr);
        (*MATRIX)[ind] = *M;
        free(M);
    }
    else if (n == 2) {
        printf("Which row would you like to delete? (enter index)\n-> ");
        answer = get_line();
        while (is_digit(answer) == 0) {
            free(answer);
            printf("-> ");
            answer = get_line();
        }
        size_t ind_n = atol(answer);
        free(answer);

        if (ind_n < 0 || (ind_n > width - 1 && n == 1) || (ind_n > height - 1 && n == 2)) {
            printf("Your index is out of range!\n");
            sleep(2);
            return;
        }

        Matrix * M = delete_row((*MATRIX)+ind, ind_n);
        free((*MATRIX)[ind].ptr);
        (*MATRIX)[ind].ptr = M->ptr;
        (*MATRIX)[ind].height--;
        free(M);
    }
    answer = get_line();
    free(answer);
}

double getMatrixIJ(Matrix* m, size_t i, size_t j) {
	return m->ptr[m->width*i+j];
}

void setMatrixIJ(Matrix* m, size_t i, size_t j, double val) {
	m->ptr[m->width*i+j] = val;
}

Matrix *getMinorMatrix(Matrix* m, int i, int j) {
    if (m->width != m->height)
        return NULL;
    if (i < 0 || i >= m->width)
        return NULL;
    if (j < 0 || j >= m->width)
        return NULL;

	Matrix* res = malloc(sizeof(Matrix));
	res->height = m->height - 1;
	res->width = m->width - 1;
	res->ptr = malloc(sizeof(double)*res->height*res->width);

	for (int n = 0; n < res->width; n++) {
		double* from = m->ptr + (n >= i ? n + 1 : n)*m->width;
		double* to = res->ptr + n*res->width;
		if (j != 0) {
			memcpy(to, from, j*sizeof(double));
		}
		if (j != m->height - 1) {
			memcpy(to + j, from + j + 1, sizeof(double)*(res->width - j));
		}
	}
	return res;
}

void removeMatrix(Matrix* m) {
	free(m->ptr);
	free(m);
}

double determinant(Matrix* m) {
	if (m->width == 1)
		return m->ptr[0];

	double res = 0;
    int sign = 1;
	for (int i = 0; i < m->width; i++) {
		Matrix* minor = getMinorMatrix(m, 0, i);
		res += (sign * determinant(minor) * getMatrixIJ(m, 0, i));
		removeMatrix(minor);
		sign *= -1;
	}
	return res;
}

void getAllMinors(Matrix* m) {
	for (int i = 0; i < m->width; i++) {
		for (int j = 0; j < m->width; j++) {
			Matrix* minor = getMinorMatrix(m, i, j);
			printMatrix(minor);
			printf("det: %lf\n\n", determinant(minor));
			removeMatrix(minor);
		}
	}
}

double all_minors_values(Matrix * MATRIX, size_t nom) {
    //size_t HEIGHT = MATRIX[0].height, WIDTH = MATRIX[0].width;
    size_t rang = MATRIX[0].height;
    Matrix * M = (Matrix*) malloc(sizeof(Matrix)*rang);
    size_t number_of_minors = 1;

    //M = (Matrix *) realloc(M, sizeof(Matrix) * rang * rang);

    for (size_t i = 0; i < rang*rang; ++i) {
       	size_t size = MATRIX->width * MATRIX->height;
    	//getchar();

        M[i].ptr = (double*) malloc(sizeof(double) * size);
        memcpy(M[i].ptr, MATRIX->ptr, size * sizeof(double));
        //getchar();
        M[i].width = MATRIX->width;
        M[i].height = MATRIX->height;
    }

    
    size_t iter = 0;
    //getchar();

    // i-ая строка и j-ый столбец для вычёркивания
    for (size_t i = 0; i < rang; ++i) {
        for (size_t j = 0; j < 1; ++j) {
            size_t w = M[iter].width, h = M[iter].height;
            w--;
            M[iter].width--;

            double* m = M[iter].ptr;
            //printf("size: %ld\n", M[iter].height*M[iter].width);
            for (size_t ii = 0; ii < h; ++ii) {
                double* donor = m + (w + 1) * ii + 1 + i;
                double* recipient = m + w * ii + i;
                //printf("don, rec: %ld, %ld\n", (w + 1) * ii + 1 + i, w * ii + i);
                /*for (size_t k = w * ii + i; k < w * ii + i + w; ++k) {
                    m[k] = m[ii + 1 + k];
                }*/
                memmove(recipient, donor, w*sizeof(double));
            }

            {
                h--;
                M[iter].height--;
                double *donor = m + w*(j + 1);
                double *recipient = m + w*j;
                size_t move_size = (1 + h)*w - w * (1 + j);
                memcpy(recipient, donor, sizeof(double) * move_size);
                M[iter].ptr = m;
            }

            M[iter].ptr = (double*) realloc(M[iter].ptr, sizeof(double) * h*w);
            iter++;
        }
    }

    //printf("+++++++++++++");
    //getchar();

    // обрабатываем результат на наличие совпадений
    size_t len = M->width * M->height;
    size_t N = number_of_minors*rang*rang;
    //getchar();
    /*
    for (size_t i = 0; i < number_of_minors*rang*rang-1; ++i) {
        double * m1 = M[i].ptr;
        double * m2 = M[i+1].ptr;
        char flag = 0;

        for (size_t j = 0; j < len; ++j) {
            if (m1[j] != m2[j]) {
                flag = 1;
                break;
            }
        }

        if (flag)
            continue;

        memmove(M+i+1, M+i+2, N-i-2);
        N--;
    }*/

    for (size_t i = 0; i < N; ++i) {
        printf("SIZE: %ldx%ld\niter: %ld\n", M[i].height, M[i].width, i);
        for (size_t ii = 0; ii < M[i].height; ++ii) {
            for (size_t k = 0; k < M[i].width; ++k)
                printf("%5.lf", M[i].ptr[ii * M[i].width + k]);
            printf("\n");
        }
        //printf("Det: %lf\n", all_minors_values(M+i, 0));
    }

    //M = (Matrix*) realloc(M, N*sizeof(Matrix));
    number_of_minors *= rang*rang;
    if (M->width == 1) {
    	printf("%lf, %lf, %lf, %lf\n", M[0].ptr[0], MATRIX->ptr[0], M[1].ptr[0], MATRIX->ptr[1]);
    	getchar();
    	double a1 = M[0].ptr[0], a2 = MATRIX->ptr[0], a3 = M[1].ptr[0], a4 = MATRIX->ptr[1];
    	free(M[0].ptr);
    	free(M[1].ptr);
    	free(M);
    	return a1*a2 - a3*a4;
    	//return M[0].ptr[0]*M[3].ptr[0] - M[1].ptr[0]*M[2].ptr[0];
        //return M->ptr[0]*M->ptr[3] - M->ptr[1]*M->ptr[2];
    }
    else {
    	//printf("else\n");
    	//getchar();
        double sum = 0;
        for (size_t i = 0; i < number_of_minors; ++i) {
        	double minor = all_minors_values(M + i, 0);
        	printf("minor: %lf\n", minor);
            if (i % 2)
                sum += -1*minor*MATRIX->ptr[i];
            else
                sum += minor*MATRIX->ptr[i];
            //printf("SUM: %lf\n", sum);
        }
        for (size_t i = 0; i < number_of_minors; ++i)
    		free(M[i].ptr);
    	free(M);
        return sum;
    }
}

void all_minors(Matrix * MATRIX, size_t nom) {
    size_t ind = 0;
    //getchar();
    printf("Which Matrix would you like to change?\n-> ");
    char * answer = get_line();
    while (is_digit(answer) == 0) {
        free(answer);
        printf("-> ");
        answer = get_line();
    }
    ind = atol(answer);
    free(answer);
    //getchar();

    size_t width = MATRIX[ind].width, height = MATRIX[ind].height;
    //getchar();
    printf("The %ld matrix:\n", ind+1);
    printf("SIZE: %ldx%ld\n", height, width);
    for (size_t j = 0; j < height; ++j) {
        for (size_t k = 0; k < width; ++k)
            printf("%5.lf", MATRIX[ind].ptr[j*MATRIX[ind].width+k]);
        printf("\n");
    }

	getAllMinors(MATRIX + ind);
	getchar();
	//return;
    /*
    // начало работы
    size_t HEIGHT = MATRIX[ind].height, WIDTH = MATRIX[ind].width;
    size_t rang = HEIGHT;
    if ((size_t) rand > WIDTH)
        rang = WIDTH;
    if (HEIGHT != WIDTH)
        return;

    Matrix * M = (Matrix*) malloc(sizeof(Matrix)*rang*rang);
    size_t number_of_minors = 1;

    for (size_t i = 0; i < rang*rang; ++i) {
        M[i].ptr = (double *) malloc(sizeof(double)*HEIGHT*WIDTH);
        memcpy(M[i].ptr, MATRIX[ind].ptr, HEIGHT*WIDTH*sizeof(double));
        M[i].width = MATRIX[ind].width;
        M[i].height = MATRIX[ind].height;
        break;
    }

    // главный цикл

    for (size_t I = rang; I > 2; --I) {
        M = (Matrix *) realloc(M, sizeof(Matrix) * rang * rang * number_of_minors);

        for (size_t i = 1; i < I * I; ++i) {
            for (size_t t = 0; t < number_of_minors; ++t) {
                M[i * number_of_minors + t].width = M[t].width;
                M[i * number_of_minors + t].height = M[t].height;


                M[i * number_of_minors + t].ptr = (double *) malloc(sizeof(double) * M[t].width * M[t].height);
                memcpy(M[i * number_of_minors + t].ptr, M[t].ptr, M[t].height * M[t].width * sizeof(double));
            }
        }

        size_t iter = 0;

        // i-ая строка и j-ый столбец для вычёркивания
        for (size_t f = 0; f < number_of_minors; ++f) {
            for (size_t i = 0; i < I; ++i) {
                for (size_t j = 0; j < I; ++j) {
                    size_t w = M[iter].width, h = M[iter].height;
                    //getchar();
                    w--;
                    M[iter].width--;

                    double *m;
                    m = M[iter].ptr;
                    for (size_t ii = 0; ii < h; ++ii) {
                        double *donor = m + (w + 1) * ii + 1 + i;
                        double *recipient = m + w * ii + i;
                        //for (size_t k = w * ii + i; k < w * ii + i + w; ++k) {
                        //    m[k] = m[ii + 1 + k];
                        //}
                        //getchar();
                        memcpy(recipient, donor, w * sizeof(double));
                    }

                    {
                        h--;
                        M[iter].height--;
                        double *donor = m + w * (j + 1);
                        double *recipient = m + w * j;
                        size_t move_size = (1 + h) * w - w * (1 + j);
                        getchar();
                        memcpy(recipient, donor, sizeof(double) * move_size);
                        //M[iter].ptr = m;
                    }

                    M[iter].ptr = (double *) realloc(M[iter].ptr, sizeof(double) * h * w);
                    iter++;
                }
            }
        }
        printf("hard\n");
        getchar();

        // обрабатываем результат на наличие совпадений
        size_t len = M[0].width*M[0].height;
        size_t N = number_of_minors*I*I;
        for (size_t i = 0; i < number_of_minors*I*I-1; ++i) {
            double * m1 = M[i].ptr;
            double * m2 = M[i+1].ptr;
            char flag = 0;

            for (size_t j = 0; j < len; ++j) {
                if (m1[j] != m2[j]) {
                    flag = 1;
                    break;
                }
            }

            if (flag)
                continue;

            memmove(M+i+1, M+i+2, N-i-2);
            N--;
        }
        M = (Matrix*) realloc(M, N*sizeof(Matrix));

        for (size_t i = 0; i < N; ++i) {
            printf("SIZE: %ldx%ld\niter: %ld\n", M[i].height, M[i].width, i);
            for (size_t ii = 0; ii < M[i].height; ++ii) {
                for (size_t k = 0; k < M[i].width; ++k)
                    printf("%6.2lf", M[i].ptr[ii * M[i].width + k]);
                printf("\n");
            }
            printf("Det: %lf\n\n", determinant(M+i));
            getchar();
        }
        number_of_minors *= I*I;
        break;
    }

    for (size_t i = 0; i < number_of_minors; ++i)
    	free(M[i].ptr);
    free(M);

    getchar();
    //exit(1);
    */
}