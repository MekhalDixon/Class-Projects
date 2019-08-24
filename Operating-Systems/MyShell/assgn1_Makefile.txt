myshell: myshell.o lex.yy.o
	cc -g -o myshell myshell.o lex.yy.o -lfl
lex.yy.o: lex.yy.c
	cc -g -c lex.yy.c -I.
lex.yy.c: lex.l
	flex lex.l
myshell.o: myshell.c
	cc -g -c myshell.c -I.
clean:
	rm -f myshell lex.yy.c lex.yy.o myshell.o

