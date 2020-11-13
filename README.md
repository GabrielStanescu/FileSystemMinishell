# FileSystemMinishell
A project which replicates commands from Linux shell

Am folosit liste simplu inlantuie

structurile File si Directory au cate o lista fiecare (dlist si flist), iar
listele acestea au structuri de noduri(dnode si fnode)

am folosit un while(true) pentru a citi comenzi de la tastatura pana cand se 
citeste "delete fs", moment in care se apeleaza "break" si programul se inchide

pentru a trimite parametri functiilor (nume de fisiere, directoare, adancime 
minima, maxima, etc) am folosit functia "strtok" pentru a extrage cuvinte din 
comanda (delimitate de " ")

Explicatii functii:

createfs() - creeaza directorul root si atribuie listelor de fisiere si 
directoare ale rootului NULL

deletefs() - sterge radacina(root) si elibereaza memoria

createdirlist() - aloca dinamic lista de directoare din directorul respectiv

createfilelist() - aloca dinamic lista de fisiere din directorul respectiv

touch() - creeaza fisiere. primeste ca parametri directorul curent, numele si 
informatia fisierului. pentru adaugare am procedat ca adaugarea nodurilor in 
liste inlantuite. singura diferenta a fost ca fnode pointeaza catre structura 
de tip "File" si ca a trebuit sa adaug lexicografic

mkdir() - creeaza directoare. la fel ca la touch(), primeste ca parametri 
directorul curent si numele directorului adaugat. pentru adaugare se procedeaza 
similar ca la touch()

ls() - am parcurs prima data lista de fisiere din directorul curent si am 
afisat fiecare fisier, apoi am facut acelasi lucru cu lista de directoare

pwd() - am parcurs recursiv lista de parent directories ale directorului 
curent. la final am afisat numele directorului

cd() - am parcurs lista de directoare din directorul curent si am cautat 
cu "strstr" directorul cautat, dupa care am schimbat pozitia directorului curent in cel dorit

cdreverse() - este accesata exclusiv de comanda "cd ..". se schimba directorul 
curent in parent directory-ul directorului curent

tree() - am afisat fiecare fisier din directorul curent, dupa care am apelat 
recursiv functia tree() folosind ca parametru fiecare director din lista de directoare

rm() - am parcurs lista de fisiere si am cautat fisierul pe care am vrut sa il 
sterg. dupa ce l-am gasit, am eliberat memoria.

rmdir() - am cautat directorul pe care am vrut sa il sterg in lista de 
directoare.am apelat functia rmdirrec() si am eliberat memoria directorului cautat.

rmdirrec() - sterge si elibereaza recursiv fisierele si directoarele din 
directorul primit ca parametru

find() - bonus - se apeleaza recursiv. la fiecare apel se scade adancimea maxima 
cu 1. conditia principala a functiei este ca adancimea sa fie diferita de -1. se 
verifica ca fiecare fisier din lista de fisiere ale directorului primit ca 
parametru daca indeplineste conditiile necesare si se afiseaza
