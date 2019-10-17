#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct
{
    int input;
    int next_state;
}transition;

void eclosure(transition **, int *, int *, int*, int*);

int main()
{
    int syms, n, t;

    printf("Enter number of alphabets: ");
    scanf("%d", &syms);
    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of transitions: ");
    scanf("%d", &t);

    int *v = (int*)malloc(n*sizeof(int));
    int *e = (int*)malloc(n*sizeof(int));
    bzero(v, n);
    transition **tr = (transition**)malloc(n*sizeof(transition*));
    for(int i=0;i<n;i++)
	tr[i] = (transition*)malloc(t*sizeof(transition));

    for(int i=0;i<t;i++)
    {
	int t1, t2, in;

	scanf("%d", &t1);
	scanf("%d", &in);
	scanf("%d", &t2);

	tr[t1][v[t1]].input = in;
	tr[t1][v[t1]].next_state = t2;
	v[t1]++;
    }

    for(int i=0;i<n;i++)
    {
	int k=1;
	e[0] = i;
	eclosure(tr, v, e, &i, &k);

	printf("\nE-closures of %d state: { ", i);

	for(int j=0;j<k;j++)
	    printf("%d ", e[j]);

	printf("}\n");
    }

    return 0;
}

void eclosure(transition **tr, int *v, int *e, int *i, int *k)
{
    for(int j=0;j<v[*i];j++)
    {
	if(tr[*i][j].input == -1)
	{
		int flag=0;
		for(int l=0;l<(*k);l++)
		{
			if(e[l] == tr[*i][j].next_state)
				flag = 1;
		}

		if(!flag)
		{
	    e[*k] = tr[*i][j].next_state;
	    (*k)++;
	    eclosure(tr, v, e, &tr[*i][j].next_state, k);
		}
	}
    }
}
