#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct
{
    int input;
    int next_state;
}transition;

int n;

void eclosure(transition **tr, int *v, int *e, int *i, int *k);
void closure(transition **tr1, transition **tr2, int *v, int *v2, int **e, int *ke, int i, int j);

int main()
{
    int syms, n3, t;

    printf("Enter number of alphabets: ");
    scanf("%d", &syms);
    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of transitions: ");
    scanf("%d", &t);

    int *v = (int*)malloc(n*sizeof(int));
    int *v2 = (int*)malloc(n*sizeof(int));
    int *v3 = (int*)malloc(n*sizeof(int));
    int **e = (int**)malloc(n*sizeof(int*));
    int *ke = (int*)malloc(n*sizeof(int));
    bzero(v, n);
    bzero(v2, n);
    bzero(v3, n);
    transition **tr1 = (transition**)malloc(n*sizeof(transition*));
    transition **tr2 = (transition**)malloc(n*sizeof(transition*));
    transition **tr3 = (transition**)malloc(n*sizeof(transition*));
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

    int n2=1, q0;
	int **states = (int**)malloc(1*sizeof(int*));
    printf("Enter start state: ");
    scanf("%d", q0);
	int *states[0] = (int*)malloc(1*sizeof(int));
	states[0][0]=q0;
	v3[0]=1;
    
	for(int i=0;i<syms;i++)
	{
    	dfa(tr2, tr3, v2, v3, states, i, 0, &n2);
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
		    if(tr2[i][x].next_state == tr1[e[i][l]][m].next_state)
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

void dfa(transition **tr2, transition **tr3, int *v2, int *v3, int **states, int sym, int curr_state, int *no_states)
{
	int *new_state = (int*)malloc(n*sizeof(int));
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
}
