#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char var;
    char prod[20];
}CharStrMap;

void ComputeFirst(CharStrMap *prod, CharStrMap **first, int var_index, int *no_firsts)

int main()
{
    int sym_n, prod_n, var_n;

    printf("Enter number of productions: ");
    scanf("%d", &prod_n);
    printf("Enter number of symbols: ");
    scanf("%d", &sym_n);
    printf("Enter number of variables: ");
    scanf("%d", &var_n);

    CharStrMap *prods = (CharStrMap*)malloc(var_n*sizeof(CharStrMap));
    CharStrMap *first = (CharStrMap*)malloc(var_n*sizeof(CharStrMap));

    for (int i=0; i<prod_n; ++i)
    {
	char ivar;
	char prod[20];

	scanf("%c", &ivar);
	scanf("%s", &prod);

	prods[ivar%var_n].var = ivar;
	strcpy(prod, prods[i].prod);
    }

    for (int i=0; i<var_n; ++i)
    {
	ComputeFirst(prod, first, i, no_firsts);
    }

    return 0;
}

void ComputeFirst(CharStrMap *prod, CharStrMap **first, int var_index, int *no_firsts)
{
    for (int i=0; i<prod_n; ++i)
    {
	if(prod[i].var == var_index+65)
	{
	    if (prod[i].prod[0] > 90)
	    {
		int flag=0;
		for (int x=0; x<no_firsts; x++)
		{
		    if(first[var_index][x] == prod[i].prod[0])
			flag=1;
		}

		if(!flag)
		{
		    first[var_index][no_firsts[var_index]] = prod[i].prod[0];
		    no_firsts[var_index]++;
		}
	    }
	    else
		ComputeFirst(prod, first, 
	}
    }

}
