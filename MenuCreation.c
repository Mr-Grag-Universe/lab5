#include <stdio.h>
#include <stdlib.h>
#include "MenuCreation.h"
#include <string.h>
#include <unistd.h>

struct Menu init_menu() {
	struct Menu menu;
	menu.root = (struct Folder*) malloc(sizeof(struct Folder));
	
	menu.root->folders = (struct Folder**) malloc(sizeof(struct Folder*));
	menu.root->folders[0] = NULL;
	
	menu.root->previous = NULL;
	//menu.name->name = (char*) malloc(sizeof(char)*5);
	
	menu.root->name = (char*) malloc(sizeof(char) * strlen("root")+1);
	memcpy(menu.root->name, "root", strlen("root")+1);//"root";
	
	menu.root->functions = (char**) malloc(sizeof(char*)*2);
	//menu.root->functions[0] = (char*) malloc(sizeof(char)*5);
	menu.root->functions[0] = "EXIT";
    menu.root->functions[1] = NULL;
	
	menu.all_folders = (struct Folder**) malloc(sizeof(struct Folder*));
	menu.all_folders[0] = NULL;
	
	menu.nof = 0;

	return menu;
}

int number_of_folders(struct Folder folder) {
	//if (menu.root->folders == NULL) return 0;
	
	int i = 0;
	while (folder.folders[i]) i++;
	return i;
}

int number_of_functions(struct Folder folder) {
        //if (menu.root->folders == NULL) return 0;

        int i = 0;
        while (folder.functions[i]) i++;
        return i;
}

void add_folder(char * name, char * host_name, struct Menu * menu) {
	struct Folder * f = menu->root;
	if (menu->nof == 0){//} || (strcmp("root", host_name) == 0) {
		//f->folders = (struct Folder**) malloc(sizeof(struct Folder*));
		f->folders[0] = (struct Folder*) malloc(sizeof(struct Folder));

		f->folders[0]->previous = f;

        f = f->folders[0];

       	f->name = (char*) malloc(sizeof(char) * strlen(name)+1);
       	memcpy(f->name, name, strlen(name)+1);

       	f->folders = (struct Folder**) malloc(sizeof(struct Folder*));
	    f->folders[0] = NULL;
		
	    f->functions = (char**) malloc(sizeof(char*));
        f->functions[0] = NULL;

		int nof = menu->nof;
		menu->all_folders = (struct Folder **) realloc(menu->all_folders, sizeof(struct Folder*) * (nof + 2));
		menu->all_folders[nof] = f;
		menu->all_folders[nof+1] = NULL;
		menu->nof++;
	}
	else {
		int nof = menu->nof;
		for (int i = 0; i < nof; ++i) {
			if (!strcmp(menu->all_folders[i]->name, host_name)) {
				f = menu->all_folders[i];
				int nof1 = number_of_folders(*f);
				
				f->folders = (struct Folder**) realloc(f->folders, (nof1+2) * sizeof(struct Folder*));

				f->folders[nof1+1] = NULL;
                f->folders[nof1] = (struct Folder*) malloc(sizeof(struct Folder));
				f->folders[nof1]->previous = f;
                		
				f = f->folders[nof1];

        		f->name = (char*) malloc(sizeof(char) * strlen(name)+1);
        		memcpy(f->name, name, strlen(name)+1);

        		f->folders = (struct Folder**) malloc(sizeof(struct Folder*));
        		f->folders[0] = NULL;

        		f->functions = (char**) malloc(sizeof(char*));
    			f->functions[0] = NULL;
				
        		menu->all_folders = (struct Folder **) realloc(menu->all_folders, sizeof(struct Folder*) * (nof + 2));
        		menu->all_folders[nof] = f;
        		menu->all_folders[nof+1] = NULL;
				menu->nof++;
				break;
			}
		}
        if (!strcmp(host_name, menu->root->name)) {
            f = menu->root;

            f->folders = (struct Folder**) realloc(f->folders, (nof+2) * sizeof(struct Folder*));

            f->folders[nof+1] = NULL;
            f->folders[nof] = (struct Folder*) malloc(sizeof(struct Folder));
            f->folders[nof]->previous = f;

            f = f->folders[nof];

            f->name = (char*) malloc(sizeof(char) * strlen(name)+1);
            memcpy(f->name, name, strlen(name)+1);

            f->folders = (struct Folder**) malloc(sizeof(struct Folder*));
            f->folders[0] = NULL;

	        f->functions = (char**) malloc(sizeof(char*));
            f->functions[0] = NULL;

            //int nof = number_of_folders(menu);
            menu->all_folders = (struct Folder **) realloc(menu->all_folders, sizeof(struct Folder*) * (nof + 2));
            menu->all_folders[nof] = f;
            menu->all_folders[nof+1] = NULL;
            menu->nof++;
        }
	}
}

void add_function(char * name, char * host_name, struct Menu menu) {
	int nof = menu.nof;
	for (int i = 0; i < nof; ++i) {

        	if (!strcmp(menu.all_folders[i]->name, host_name)) {
			struct Folder * f = menu.all_folders[i];
                	int nof1 = number_of_functions(*f);
					f->functions = (char**) realloc(f->functions, sizeof(char*) * (nof1+2));
            		f->functions[nof1+1] = NULL;

            		f->functions[nof1] = (char*) malloc(sizeof(char) * (strlen(name) + 1));
            		memcpy(f->functions[nof1], name, strlen(name));
            		f->functions[nof1][strlen(name)] = '\0';

			break;
		}
	}
}

void delete_all_folders(struct Menu * menu) {
    for (int i = 0; i < menu->nof; ++i) {
	    struct Folder * f = menu->all_folders[i];
        free(f->folders);
        free(f->name);
        
    	for (int j = 0, l =  number_of_functions(*f); j < l; ++j) {
    		free(f->functions[j]);
    	}
		free(f->functions);
    	free(f);
	}
}

void clear_root(struct Menu * menu) {
    free(menu->root->name);
    free(menu->root->folders);
    //я делал указатель на статическую память
    //free(*(menu->root->functions));
    free(menu->root->functions);
    free(menu->root);
    free(menu->all_folders);
}
/*
struct Menu create_menu() {
	struct Menu menu = init_menu();
	char enter_data[] = "Entering of Data.";
	char get_out_data[] = "Getting out of Data.";
	char work_with_data[] = "Work with Data.";
	char data_time[] = "Timing.";
	char root[] = "root";
    char sort[] = "Sort all cars.";

	char read_from_terminal[] = "Read data from the terminal window.";
	char read_from_file[] = "Read data from a file.";
	char random_generation[] = "Generate random data.";
	char output_to_terminal[] = "Print cars to terminal.";
	char save_data_to_file[] = "Save data to file.";
    char insert[] = "Insert a new car.";
    char insert_in_sorted_array[] = "Insert a new car in the sorted array.";
    char erase[] = "Delete several elements.";
    char timing[] = "Timing.";
    char gnome_sort[] = "Gnome Sort.";
    char insert_binary_sort[] = "Insert Sort.";
    char radix_sort[] = "Radix Sort.";
    
	add_folder(enter_data, root, &menu);
	add_folder(get_out_data, root, &menu);
	add_folder(work_with_data, root, &menu);
	add_folder(data_time, root, &menu);
    add_folder(sort, root, &menu);
	
	add_function(read_from_terminal, enter_data, menu);
	add_function(read_from_file, enter_data, menu);
	add_function(random_generation, enter_data,  menu);
	
	add_function(output_to_terminal, get_out_data, menu);
	add_function(save_data_to_file, get_out_data, menu);

    add_function(insert, work_with_data, menu);
    add_function(insert_in_sorted_array, work_with_data, menu);
    add_function(erase, work_with_data, menu);

    add_function(gnome_sort, sort, menu);
    add_function(insert_binary_sort, sort, menu);
    add_function(radix_sort, sort, menu);

    add_function(timing, data_time, menu);

    return menu;
}*/

void print_menu(struct Folder * f) {
    for (size_t i = 0; i < strlen(f->name)+10; ++i)
	    printf("=");
    printf("\n");
    printf("||   %s   ||\n", f->name);
    for (size_t i = 0; i < strlen(f->name)+10; ++i)
	    printf("=");
    printf("\n");

    printf("0-> [< go back >]\n");

    int i = 0;
    while (f->folders[i++])
        printf("%d-> [%s]\n", i, f->folders[i-1]->name);

    int j = 0;
    while (f->functions[j++])
        printf("%d-> [< %s >]\n", i+j-1 , f->functions[j-1]);
}
