#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "file.h"

void createfs(Directory **root)
{
	*root = malloc(sizeof(struct Directory));
	(*root)->name = "/";
	(*root)->crrntfile = NULL;
	(*root)->crrntdir = NULL;
	(*root)->parentDir = NULL;
}

void deletefs(Directory **root)
{
	free((*root)->crrntfile);
	free((*root)->crrntdir);
	free(*root);
}

void createdirlist(Directory **position, dlist **dirlist)
{
	*dirlist = malloc(sizeof(struct dlist));
	(*dirlist)->head = NULL;
	(*dirlist)->len = 0;
	(*position)->crrntdir = *dirlist;
}

void createfilelist(Directory **position, flist **filelist)
{
	*filelist = malloc(sizeof(struct flist));
	(*filelist)->head = NULL;
	(*filelist)->len = 0;
	(*position)->crrntfile = *filelist;
}

void touch(Directory *position, char *nume, char *info)
{
	int l, thisisfine = 0;

	char *name1, *name2;

	File *file;

	file = malloc(sizeof(struct File));
	file->name = nume;
	file->data = info;
	file->size = strlen(info);
	file->dir = position;
	flist *filelist;

	filelist = position->crrntfile;
	fnode *filenode;

	filenode = malloc(sizeof(struct fnode));

	filenode->fisier = file;
	filenode->next = NULL;
	if (filelist->len == 0) {
		filelist->head = filenode;
	} else {
		fnode *tmp;

		tmp = filelist->head;
		if (strcmp(filenode->fisier->name, tmp->fisier->name) < 0) {
			filenode->next = tmp;
			filelist->head = filenode;
		} else {
			if (tmp->next != NULL) {
				name1 = filenode->fisier->name;
				name2 = tmp->next->fisier->name;
				l = strcmp(name1, name2);
				thisisfine = 1;
			}
			while (tmp->next != NULL && l > 0 && thisisfine == 1) {
				tmp = tmp->next;
				if (tmp->next == NULL)
					break;
				name2 = tmp->next->fisier->name;
				l = strcmp(name1, name2);
			}
			if (tmp->next != NULL)
				filenode->next = tmp->next;
			tmp->next = filenode;
		}
	}
	filelist->len++;
}

void mkdir(Directory *position, char *nume)
{
	int ll, thisisfine = 0;

	char *name1, *name2;

	Directory *dir;

	dir = malloc(sizeof(struct Directory));
	dir->name = nume;
	dir->parentDir = position;
	dlist *dirlist;
	flist *filelist;

	dirlist = malloc(sizeof(struct dlist));
	filelist = malloc(sizeof(struct flist));
	dirlist->head = NULL;
	dirlist->len = 0;
	filelist->head = NULL;
	filelist->len = 0;
	dir->crrntdir = dirlist;
	dir->crrntfile = filelist;
	dlist *posdirlist;

	posdirlist = position->crrntdir;
	dnode *dirnode;

	dirnode = malloc(sizeof(struct dnode));
	dirnode->next = NULL;
	dirnode->directory = dir;
	if (posdirlist->len == 0) {
		posdirlist->head = dirnode;
	} else {
		dnode *tmp;

		tmp = posdirlist->head;
		int l = strcmp(dirnode->directory->name, tmp->directory->name);

		if (l < 0) {
			dirnode->next = tmp;
			posdirlist->head = dirnode;
		} else {
			if (tmp->next != NULL) {
				name1 = dirnode->directory->name;
				name2 = tmp->next->directory->name;
				ll = strcmp(name1, name2);
				thisisfine = 1;
			}
			while (tmp->next != NULL && ll > 0 && thisisfine) {
				tmp = tmp->next;
				if (tmp->next == NULL)
					break;
				name2 = tmp->next->directory->name;
				ll = strcmp(name1, name2);
			}
			if (tmp->next != NULL)
				dirnode->next = tmp->next;
			tmp->next = dirnode;
		}
	}
	posdirlist->len++;
}

void ls(Directory **position)
{
	flist *filelist;

	filelist = (*position)->crrntfile;
	fnode *filenode;

	filenode = filelist->head;

	dlist *dirlist;

	dirlist = (*position)->crrntdir;
	dnode *dirnode;

	dirnode = dirlist->head;

	for (int i = 0; i < filelist->len; i++) {
		printf("%s ", filenode->fisier->name);
		filenode = filenode->next;
	}
	for (int i = 0; i < dirlist->len; i++) {
		printf("%s ", dirnode->directory->name);
		dirnode = dirnode->next;
	}
	printf("\n");
}

void pwd(Directory *position, int first)
{
	if (position->parentDir != NULL)
		pwd(position->parentDir, 0);
	if (position->parentDir == NULL || first == 1)
		printf("%s", position->name);
	else
		printf("%s/", position->name);
}

void cd(Directory **position, char *nume)
{
	dlist *dirlist;

	dirlist = (*position)->crrntdir;
	dnode *dirnode;

	dirnode = dirlist->head;
	while (dirnode != NULL) {
		if (strcmp(dirnode->directory->name, nume) == 0) {
			*position = dirnode->directory;
			break;
		}
		dirnode = dirnode->next;
	}
	if (dirnode == NULL)
		printf("Cannot move to '%s': No such directory!\n", nume);
}

void cdreverse(Directory **position)
{
	if ((*position)->parentDir != NULL)
		*position = (*position)->parentDir;
	else
		printf("Cannot move to '..': No such directory!\n");
}

void tree(Directory *position, int increment)
{
	if (position != NULL) {
		flist *filelist = position->crrntfile;

		fnode *filenode = filelist->head;

		while (filenode != NULL) {
			for (int i = 0; i < increment; i++)
				printf(" ");
			printf("%s\n", filenode->fisier->name);
			filenode = filenode->next;
		}
		dlist *dirlist = position->crrntdir;

		dnode *dirnode = dirlist->head;

		while (dirnode != NULL) {
			for (int i = 0; i < increment; i++)
				printf(" ");
			printf("%s\n", dirnode->directory->name);
			tree(dirnode->directory, increment + 4);
			dirnode = dirnode->next;
		}
	}
}

void rm(Directory *position, char *token)
{
	flist *filelist = position->crrntfile;

	fnode *filenode = filelist->head;

	int ok = 1;

	File  *file;

	if (strcmp(filenode->fisier->name, token) == 0) {
		fnode *rem = filenode;

		filelist->head = filenode->next;
		filelist->len--;
		file = filenode->fisier;
		free(file);
		free(rem);
		ok = 0;
		return;
	}
	while (filenode->next != NULL && ok != 0) {
		if (strcmp(filenode->next->fisier->name, token) == 0) {
			fnode *rmv;

			rmv = filenode->next;
			file = rmv->fisier;
			filenode->next = filenode->next->next;
			filelist->len--;
			free(file);
			free(rmv);
			ok = 2;
			break;
		}
		filenode = filenode->next;
	}
	if (filenode->next == NULL)
		printf("Cannot remove '%s': No such file!\n", token);
}

void rmdirrec(Directory *position)
{
	if (position != NULL) {
		flist *filelist = position->crrntfile;

		fnode *filenode = filelist->head;

		while (filenode != NULL && position != NULL) {
			fnode *frmv = filenode;

			filenode = filenode->next;
			free(frmv->fisier);
			free(frmv);
		}
		dlist *dirlist = position->crrntdir;

		dnode *dirnode = dirlist->head;

		while (dirnode != NULL) {
			rmdirrec(dirnode->directory);
			dnode *rmv = dirnode;

			dirnode = dirnode->next;
			free(rmv->directory->crrntdir);
			free(rmv->directory->crrntfile);
			free(rmv->directory);
			free(rmv);
		}
	}
}

void rmdir(Directory *position, char *token)
{
	dlist *dirlist = position->crrntdir;

	dnode *dirnode = dirlist->head;

	int ok = 1;

	if (strcmp(dirnode->directory->name, token) == 0) {
		rmdirrec(dirnode->directory);
		dirlist->head = dirnode->next;
		dirlist->len--;
		free(dirnode->directory->crrntdir);
		free(dirnode->directory->crrntfile);
		free(dirnode->directory);

		free(dirnode);
		ok = 0;
		return;
	}

	while (dirnode->next != NULL && ok) {
		if (strcmp(dirnode->next->directory->name, token) == 0) {
			dnode *rmv;

			rmv = dirnode->next;
			dirnode->next = dirnode->next->next;
			dirlist->len--;
			free(rmv->directory->crrntdir);
			free(rmv->directory->crrntfile);
			rmdirrec(dirnode->directory);
			free(rmv->directory);
			free(rmv);
			ok = 2;
			break;
		}
		dirnode = dirnode->next;
	}
	if (dirnode->next == NULL && ok == 1)
		printf("Cannot remove '%s': No such directory!\n", token);
}

void find(Directory *position, int depth, int min, int max, char *name)
{
	if (position != NULL && depth != -1) {
		File *file;

		flist *filelist = position->crrntfile;

		fnode *filenode = filelist->head;

		while (filenode != NULL) {
			file = filenode->fisier;
			if (strstr(file->data, name) != NULL)
				if (min <= file->size && max >= file->size)
					printf("%s ", file->name);
			filenode = filenode->next;
		}
		dlist *dirlist = position->crrntdir;

		dnode *dirnode = dirlist->head;

		while (dirnode != NULL) {
			find(dirnode->directory, depth - 1, min, max, name);
			dirnode = dirnode->next;
		}
	}
}
