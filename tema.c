#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "functions.h"

int main(void)
{
	char **nume = (char **) calloc(100, sizeof(char *));

	for (int i = 0; i < 100; i++)
		nume[i] = (char *) calloc(100, sizeof(char));
	char *info, *token;

	Directory *root;

	Directory *position;

	flist *filelist;

	dlist *dirlist;

	int ok = 1, count = 0, increment, max_depth, min_size, max_size;

	while (ok) {
		scanf("%[^\n]%*c", nume[count]);
		if (strcmp(nume[count], "create fs") == 0) {
			createfs(&root);
			position = root;
			createdirlist(&position, &dirlist);
			createfilelist(&position, &filelist);
			continue;
		}
		if (strcmp(nume[count], "delete fs") == 0) {
			deletefs(&root);
			ok = 0;
			continue;
		}
		if (strstr(nume[count], "touch ") != NULL) {
			token = strtok(nume[count], " ");
			token = strtok(NULL, " ");
			info = strtok(NULL, " ");
			touch(position, token, info);
			count++;
			continue;
		}
		if (strstr(nume[count], "mkdir ") != NULL) {
			token = strtok(nume[count], " ");
			token = strtok(NULL, " ");
			mkdir(position, token);
			count++;
			continue;
		}
		if (strcmp(nume[count], "ls") == 0)
			ls(&position);
		if (strcmp(nume[count], "pwd") == 0) {
			pwd(position, 1);
			printf("\n");
			continue;
		}
		if (strstr(nume[count], "cd ")) {
			token = strtok(nume[count], " ");
			token = strtok(NULL, " ");
			if (strcmp(token, "..") != 0)
				cd(&position, token);
			else
				cdreverse(&position);
		}
		if (strcmp(nume[count], "tree") == 0) {
			increment = 4;
			printf("%s\n", position->name);
			tree(position, increment);
		}
		if (strstr(nume[count], "rm ")) {
			token = strtok(nume[count], " ");
			token = strtok(NULL, " ");
			if (position->crrntfile->len != 0)
				rm(position, token);
			else {
				printf("Cannot remove '%s': ", token);
				printf("No such file!\n");
			}
			continue;
		}
		if (strstr(nume[count], "rmdir ")) {
			token = strtok(nume[count], " ");
			token = strtok(NULL, " ");
			if (position->crrntdir->len != 0)
				rmdir(position, token);
			else {
				printf("Cannot remove '%s': ", token);
				printf("No such directory!\n");
			}
			continue;
		}
		if (strstr(nume[count], "find")) {
			token = strtok(nume[count], " ");
			max_depth = atoi(strtok(NULL, " "));
			min_size = atoi(strtok(NULL, " "));
			max_size = atoi(strtok(NULL, " "));
			token = strtok(NULL, " ");
			find(position, max_depth, min_size, max_size, token);
			printf("\n");
		}
	}
	for (int i = 0; i < 100; i++)
		free(nume[i]);
	free(nume);
}
