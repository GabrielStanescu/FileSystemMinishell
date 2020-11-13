#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "file.h"
void createfs(Directory **root);
void deletefs(Directory **root);
void createdirlist(Directory **position, dlist **dirlist);
void createfilelist(Directory **position, flist **filelist);
void touch(Directory *position, char *nume, char *info);
void mkdir(Directory *position, char *nume);
void ls(Directory **position);
void pwd(Directory *position, int first);
void cd(Directory **position, char *nume);
void cdreverse(Directory **position);
void tree(Directory *position, int increment);
void rm(Directory *position, char *token);
void rmdirrec(Directory *position);
void rmdir(Directory *position, char *token);
void find(Directory *position, int depth, int min, int max, char *name);

#endif
