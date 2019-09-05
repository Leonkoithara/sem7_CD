#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_token(char *);

void main()
{
	char str[50];
	FILE *input = fopen("input.c", "r");

	while((fscanf(input, "%s", str)) != EOF)
	{
		print_token(str);
	}
}

char symtab[50][50];
int k=0;

void print_token(char *s)
{
	char keywords[32][10] = {"auto", "return", "int", "void"};
	char seperators[10] = {'{', '}', '[', ']', ';', '(', ')'};
	char operators[10] = {'+', '-', '='};

	if(s[0] == '\0')
		return;

	int i;

	for(i=0;i<4;i++)
	{
		if(!strcmp(s, keywords[i]))
		{
			printf("%s:=keyword\n", s);
			return;
		}
	}

	for(i=0;i<7;i++)
	{
		if(s[0] == seperators[i])
		{
			printf("%s:=seperator\n", s);
			return;
		}
	}

	if(isdigit(s[0]))
	{
		for(int i=0;i<strlen(s);i++)
		{
			if(!isdigit(s[i]))
			{
				printf("Invalid token\n");
				return;
			}
		}

		printf("%s:=literal\n", s);
		return;
	}
	else
	{
		char *p, temp[50];
		int flag=1, t5=0;

		p=s;
		temp[0]='\0';
		int i=0;
		int t2=0;

		while(isalnum(s[i+t2]))
			t2++;

		if(!t2)
		{
			while(!isalnum(s[i+t2]))
			{
				t2++;
				printf("%c: %d", s[i+t2], t2);
				scanf("%d", &t5);
			}
		}

		i=i+t2;
		strncpy(temp, p, t2);
		temp[t2]='\0';
		scanf("%d", &t5);
		
		for(int j=0;j<k;j++)
		{
			if(!strcmp(symtab[j], temp))
			{
				flag=0;
			}
		}
		if(flag)
		{
			printf("%s:=identifier\n", temp);
		}
		p=s+i;
		print_token(p);
		
	}
}
