//
// Created by Stephan on 22.11.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>

char * f_get_line(FILE * file) {
    char * res = (char*) calloc(1, sizeof(char));
    char n = 0;
    int old_len = 0;
    char buf[101] = {0};
	//printf("%p\n", file);

    do {
        n = fscanf(file, "%100[^\n]", buf);
        int chunck_len = strlen(buf);
        //int old_len = strlen(res);
	   //printf("buf: %s\n", buf);
        if (n == 1) {
            res = (char *) realloc(res, sizeof(char) * (old_len + chunck_len + 1));
            memcpy(res + old_len, buf, chunck_len);
            old_len += chunck_len;
        } else if (!n) fscanf(file, "%*c");

        else if (!old_len) {
		if (res) free(res);
		return NULL;
	}

    } while (n > 0);
    //fscanf(file, "%*c");

    if (old_len > 0) {
        res[old_len] = '\0'; //смотри утечку из-за обрезания
        res = (char*) realloc(res, sizeof(char)*(strlen(res)+1));
    }
    else {
        if (res) free(res);
        res = (char *) calloc(1, sizeof(char));
    }
    return res;
}

char * f_get_lines(char * path) {
    setlocale(LC_ALL, "Rus");
    int m_len = 0;
    char * res = (char*) calloc(1, sizeof(char));

    FILE * file;
    file = fopen(path, "r");//"C:\\Users\\Stephan\\CLionProjects\\lab4\\test1.txt", "r");
    if (file == NULL) {
        printf("Something came wrong. Check you pass and try again, please.\n");
        sleep(1);
	free(res);
        //fclose(file);
        return NULL;
    }

    char * line = NULL;
    int len = 0;
    do {
        line = f_get_line(file);
        if (line) {
            if (line[0] != '\r' && line[0] != '\0') {
                len = strlen(line);
		//printf("%d, %s\n", len, line);
                //m_len += len;
                res = (char*) realloc(res, sizeof(char)*(m_len+len+2));
                memcpy(res+m_len, line, len);
                m_len += len+1;
                res[m_len] = '\0';
                res[m_len-1] = '\n';
		//printf("%d, %s\n", m_len, res);
            }
	    free(line);
	}
	else
		break;
    } while(line);

    //if (line) free(line);

    if (m_len > 0) {
        m_len--;
        res = (char*) realloc(res, (m_len+1)*sizeof(char));
        res[m_len] = '\0';
    }
    else {
        if (res)
            free(res);
        res = (char *) calloc(1, sizeof(char));
    }

    fclose(file);
    return res;
}
