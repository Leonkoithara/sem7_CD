#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <string.h>

typedef struct
{
    int input;
    int next_state;
}transition;

int n, syms;

int compare (const void *a, const void *b)
{ return ( *(int*)a - *(int*)b ); }

void eclosure(transition **tr, int *v, int *e, int *i, int *k);
void closure(transition **tr1, transition **tr2, int *v, int *v2, int **e, int *ke, int i, int j);
int dfa(transition **tr2, transition **tr3, int *v2,  int **states, int *v3, int sym, int curr_state, int *no_states, int *new_state);

int main()
{
    int t;

    printf("Enter number of alphabets: ");
    scanf("%d", &syms);
    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of transitions: ");
    scanf("%d", &t);

    int *v = (int*)malloc(n*sizeof(int));
    int *v2 = (int*)malloc(n*sizeof(int));
    int **e = (int**)malloc(n*sizeof(int*));
    int *ke = (int*)malloc(n*sizeof(int));
    bzero(v, n);
    bzero(v2, n);
    transition **tr1 = (transition**)malloc(n*sizeof(transition*));
    transition **tr2 = (transition**)malloc(n*sizeof(transition*));
    for(int i=0;i<n;i++)
    {
	tr1[i] = (transition*)malloc(t*sizeof(transition));
	tr2[i] = (transition*)malloc(t*sizeof(transition));
	e[i] = (int*)malloc(n*sizeof(int));
    }

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
	int k=1;
	e[i][0] = i;
	eclosure(tr1, v, e[i], &i, &k);
	ke[i] = k;
    }

    for(int i=0;i<n;i++)
    {
	for(int j=0;j<syms;j++)
	{
	    closure(tr1, tr2, v, v2, e, ke, i, j);
	}
    }

    int max_size = pow(2, n);
    int no_states=1, q0;
    int **states = (int**)malloc(max_size*sizeof(int*));
    transition **tr3 = (transition**)malloc(max_size*sizeof(transition*));
    int *v3 = (int*)malloc(max_size*sizeof(int));
    for (int i=0; i<max_size; ++i)
    {
	tr3[i] = (transition*)malloc(syms*sizeof(transition));
	states[i] = (int*)malloc(n*sizeof(int));
    }


    printf("Enter start state: ");
    scanf("%d", &q0);

    states[0][0]=q0;
    v3[0]=1;
    
    for(int i=0;i<no_states;i++)
    {
	for(int j=0;j<syms;j++)
	{
	    int flag = dfa(tr2, tr3, v2, states, v3,  j, i, &no_states, states[no_states]);

	    if(!flag)
	    {
		tr3[i][j].input = j;
		tr3[i][j].next_state = -1;
	    }
	}
    }

    for (int i=0; i<no_states; ++i)
    {
	for (int j=0; j<syms; j++)
	{
	    printf("%d %d %d\n", i, j, tr3[i][j].next_state);
	}

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

void closure(transition **tr1, transition **tr2, int *v, int *v2, int **e, int *ke, int i, int j)
{
    for(int l=0;l<ke[i];l++)
    {
	for(int m=0;m<v[e[i][l]];m++)
	{
	    if(tr1[e[i][l]][m].input == j)
	    {
		int flag=0;
		for(int x=0;x<v2[i];x++)
		{
		    if(tr2[i][x].next_state == tr1[e[i][l]][m].next_state && tr2[i][x].input == j)
			flag = 1;
		}

		if(!flag)
		{
		    tr2[i][v2[i]].input = j;
		    tr2[i][v2[i]].next_state = tr1[e[i][l]][m].next_state;
		    v2[i]++;


		    for(int x=0;x<ke[tr1[e[i][l]][m].next_state];x++)
		    {
			int flag=0;
			for(int y=0;y<v2[i];y++)
			{
			    if(tr2[i][y].input == j && tr2[i][y].next_state == e[tr1[e[i][l]][m].next_state][x])
				flag = 1;
			}

			if(!flag)
			{
			    tr2[i][v2[i]].input = j;
			    tr2[i][v2[i]].next_state = e[tr1[e[i][l]][m].next_state][x];
			    v2[i]++;
			}
		    }
		}
	    }
	}
    }
}

int dfa(transition **tr2, transition **tr3, int *v2,  int **states, int *v3, int sym, int curr_state, int *no_states, int *new_state)
{
    int k=0;

    for(int i=0;i<v3[curr_state];i++)
    {
	for(int j=0;j<v2[states[curr_state][i]];j++)
	{
	    if(tr2[states[curr_state][i]][j].input == sym)
	    {
		int flag=0;
		for(int x=0;x<k;x++)
		{
		    if(new_state[x] == tr2[states[curr_state][i]][j].next_state)
			flag=1;
		}
		if(!flag)
		{
		    new_state[k] = tr2[states[curr_state][i]][j].next_state;
		    k++;
		}
	    }
	}
    }

    if(k == 0)
    {
	tr3[curr_state][sym].input = sym;
	tr3[curr_state][sym].next_state = -1;
	return 0;
    }

    qsort(new_state, k, sizeof(int), compare);

    int flag=1, t;
    for(int x=0;x<*no_states;x++)
    {
	flag=1;
	if(v3[x] != k)
	    flag=0;
	
	for(int y=0;y<v3[x];y++)
	{
	    if(states[x][y] != new_state[y])
		flag=0;
	}

	if(flag)
	{
	    t = x;
	    break;
	}
    }
    if(!flag)
    {
	(*no_states)++;
	t = *no_states-1;
	v3[t] = k;
    }

    tr3[curr_state][sym].input = sym;
    tr3[curr_state][sym].next_state = t;

    return k;
}
