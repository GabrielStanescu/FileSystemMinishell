build: tema.c
	gcc tema.c functions.c functions.h file.h -std=c99 -Wall -o fsminishell
run: fsminishell
	./fsminishell
clean: fsminishell
	rm fsminishell
