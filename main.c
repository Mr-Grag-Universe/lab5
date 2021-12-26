#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include "MenuCreation.h"
#include "KGetLine.h"
#include "InputFunctions.h"
#include "MatrixStruct.h"
#include "OutputFunctions.h"
#include "WorkWithData.h"

char functions_execution(char * name, Matrix ** MATRIX, size_t * nom) {
    printf("%s\n", name);
    if (!strcmp(name, "EXIT")) return 1;
    else if (!strcmp(name, "Read data from the terminal window.")) read_from_terminal(MATRIX, nom);
    else if (!strcmp(name, "Read data from a binary file.")) ReadFromFile(MATRIX, nom);
    else if (!strcmp(name, "Generate random data.")) random_generation(MATRIX, nom);
    else if (!strcmp(name, "Print the last matrix to terminal.")) print_data(*MATRIX, *nom, 0);
    else if (!strcmp(name, "Print all data to terminal.")) print_data(*MATRIX, *nom, -1);
    else if (!strcmp(name, "Save data to file.")) save_data_to_binary_file(*MATRIX, *nom);
    else if (!strcmp(name, "Insert column or row.")) insert(MATRIX, nom);
    else if (!strcmp(name, "Delete column or row.")) delete(MATRIX, nom);
    else if (!strcmp(name, "Find all minors in matrix.")) all_minors(*MATRIX, *nom);
    return 0;
}

char start_session() {
	setlocale(LC_ALL, "Rus");
	
	printf("\nHello, Dear User.\nDo you wanna activate this app? [Y/n]: ");
	
	char * answer = NULL;// = get_line();
	char * yes = "y";
	char * no = "n";
	char * ryes = "д";
	char * rno = "н";

	do {
		if (answer) {
			printf("Are you stupid?! It's definitely not [Y/n]. Please check your answer and retry.\n-->");
			free(answer);
		}
		answer = get_line();
		for (int i = 0, l = strlen(answer); i < l; ++i) answer[i] = tolower(answer[i]);
	} while (strcmp(answer, yes) && strcmp(answer, no) && strcmp(answer, ryes) && strcmp(answer, rno));
	
	if (!(strcmp(answer, yes) && strcmp(answer, ryes))) {
		printf("Wait for a second, please.\n");
		free(answer);
		return 1;
	}

	printf("Okey, goodbye!\n");
	free(answer);
	return 0;
}

void clrscr(){
    system("@cls||clear");
}

void end_session(){
	printf("Goodbye!\n");
	printf("Enter something to finish your work.\n");
	sleep(1);
	clrscr();
	//free(buf);
}

struct Menu create_menu() {
	struct Menu menu = init_menu();
	char enter_data[] = "Entering of Data.";
	char get_out_data[] = "Getting out of Data.";
	char work_with_data[] = "Work with Data.";
	char root[] = "root";

	char read_from_terminal[] = "Read data from the terminal window.";
	char read_from_file[] = "Read data from a binary file.";
	char random_generation[] = "Generate random data.";
	char last_out[] = "Print the last matrix to terminal.";
	char print_all[] = "Print all data to terminal.";
	char save_data_to_file[] = "Save data to file.";
	char insert[] = "Insert column or row.";
    char delete[] = "Delete column or row.";
    char minors[] = "Find all minors in matrix.";
    
	add_folder(enter_data, root, &menu);
	add_folder(get_out_data, root, &menu);
	add_folder(work_with_data, root, &menu);
	
	add_function(read_from_terminal, enter_data, menu);
	add_function(read_from_file, enter_data, menu);
	add_function(random_generation, enter_data,  menu);
	
	add_function(last_out, get_out_data, menu);
	add_function(print_all, get_out_data, menu);
	add_function(save_data_to_file, get_out_data, menu);

	add_function(insert, work_with_data, menu);
    add_function(delete, work_with_data, menu);
    add_function(minors, work_with_data, menu);

	return menu;
}
void main_circle(){
	clrscr();
    char finish_session = 0;

	printf("Hello. It is the start menu of my app.\nWhat would you like to do the first?\n");
	//sleep(3);
	//getchar();

	struct Menu menu = create_menu();
	struct Folder * folder = menu.root;
	Matrix * MATRIX = NULL;
	size_t nom = 0;

	while (!finish_session) {
    	clrscr();
    	//printf("%s\n", folder->name);
    	print_menu(folder);
    
		int n = 0;
		//int b = 0;
		if (scanf("%d", &n) <= 0) { 
			scanf("%*c");
			continue;
		}
		//while (scanf("%d", &n) <= 0) { getchar(); printf("Error!\n->"); }
		
		int nof = number_of_folders(*folder);
		int l = nof+ number_of_functions(*folder);
		if (n > l || n < 0) {
    		printf("Your command was out of range. Try again.\n");
    		sleep(1);
    		continue;
		}

		if (n == 0) {
			if (folder->previous)
				folder = folder->previous;
			else
				printf("This is the root!\n");
			continue;
		}

		
		if (n <= nof) {
			folder = folder->folders[n-1];
			continue;
		}

		
		finish_session = functions_execution(folder->functions[n-nof-1], &MATRIX, &nom);
	}


	clrscr();

    delete_all_folders(&menu);
    //printf("s;fkdjkjdf");
    //printf("SLEEEP\n");
	//sleep(10);
	clear_root(&menu);
	for (int i = 0; i < nom; ++i)
		free(MATRIX[i].ptr);
	free(MATRIX);
}

int main() {
	printf("Hello, World!");
	
	char we_are_begining = start_session();
	if (!we_are_begining) return 0;
	
	main_circle();
	
	end_session();
	return 0;
}