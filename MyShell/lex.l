%{
# define YY_DECL char **yylex()
int _numargs = 100;
char *_args[100];
int _argcount = 0;
%}

WORD [a-zA-Z0-9\/\.-]+
SPECIAL [()><|&;*]

%%


 _args[0] = NULL; _argcount = 0;
{WORD}|{SPECIAL} {
 if(_argcount < _numargs) {
 _args[_argcount++] = (char *)strdup(yytext);
 _args[_argcount] = NULL;
 }
}
\n return _args;
[ \t]+
.
%%
char **Ggetline() { return yylex(); }
