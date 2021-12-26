#pragma once

#ifndef MENU
#define MENU
struct Folder{
	char * name;
	struct Folder ** folders;
	struct Folder * previous;
	char ** functions;
};

struct Menu{
	struct Folder * root;
	struct Folder ** all_folders;
	int nof;
};
struct Menu init_menu();
int number_of_folders(struct Folder folder);
int number_of_functions(struct Folder folder);
void add_folder(char * name, char * host_name, struct Menu * menu);
struct Menu create_menu();
void add_function(char * name, char * host_name, struct Menu menu);
void delete_all_folders(struct Menu * menu);
void clear_root(struct Menu * menu);
void print_menu(struct Folder * f);
#endif
