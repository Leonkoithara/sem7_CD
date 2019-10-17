#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct
{
    int input;
    int next_state;
}transition;

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
    transition **tr1 = (transition**)malloc(n*sizeof(transition*));
    transition **tr2 = (transition**)malloc(n*sizeof(transition*));
    for(int i=0;i<n;i++)
	tr1[i] = (transition*)malloc(t*sizeof(transition));

    for(int i=0;i<t;i++)
    {
	int t1, t2, in;

	scanf("%d", &t1);
	scanf("%d", &in);
	scanf("%d", &t2);

	tr1[t1][v[t1]].input = in;
	tr1[t1][v[t1]].next_state = t2;
	v[t1]++;
    }

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<syms;j++)
		{
		}
	}

    return 0;
}

void closure(transition **tr1, transition **tr2, int *v, int *i, int *k)
{
	
}
