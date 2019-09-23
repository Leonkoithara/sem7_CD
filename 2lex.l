%{
#include <string.h>
int len=0;
int doesexist(char *s);
char arr[50][50];
%}
letter [A-Za-z]
digit [0-9]
%%
int|void|return {printf("%s:=keyword\n", yytext);}

\(|\)|\{|\}|\[|\]|;|\'|\" {printf("%s:=seperator\n", yytext);}

\!|\%|\^|\&|\*|\-|\+|= {printf("%s:=operator\n", yytext);}

{letter}({letter}|{digit})* {if(!doesexist(yytext)) printf("%s:=identifier\n", yytext);}

{digit} {printf("%s:=literal\n", yytext);}

\n 
%%
void main()
{
	yyin = fopen("input.c", "r");
	yylex();
	fclose(yyin);
}

int doesexist(char *s)
{
	int i;
	for(i=0;i<len;i++)
	{
		if(!strcmp(s, arr[i]))
			return 1;
	}
	strcpy(arr[i], s);
	len++;
	return 0;
}
