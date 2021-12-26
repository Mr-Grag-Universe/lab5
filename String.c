#include <stdlib.h>

unsigned char is_digit(char * s) {
	size_t i = 0;
	while (s[i]) {
		if ((s[i] > '9' || s[i] < '1') && s[i] != '0')
			return 0;
		++i;
	}
	return 1;
}

unsigned char is_float(char * s) {
	size_t i = 0;
	char flag = 0;
	while (s[i]) {
		if ((s[i] > '9' || s[i] < '1') && s[i] != '0') {
			if (s[i] == '.') {
				if (flag)
					return 0;
				flag++;
			}
			else
				return 0;
		}
		++i;
	}
	return 1;
}