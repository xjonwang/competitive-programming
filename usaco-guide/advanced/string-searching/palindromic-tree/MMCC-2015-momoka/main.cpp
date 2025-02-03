#include "momoka.h"
#include <stdio.h>
#include <stdlib.h>

#define ensured(x, y) ensure(x, y)

static inline void ensure(int cond, const char *msg)
{
    if(!cond)
    {
        printf("REJECTED %s\n", msg);
        exit(0);
    }
}

#define MAXN 1000000

static int TEST, N;
static int Q[MAXN][2];
static long long ans[MAXN];
static int NANS;

static void read_input()
{
    ensured(scanf("%d", &N)==1, "cannot read N");
    ensured(0<=N && N<=MAXN, "number of queries out of bounds");
    int i;
    char ch;
    for(i=0; i<N; i++)
    {
        ensured(scanf("%d", Q[i])==1, "cannot read query");
        if(Q[i][0]==1)
        {
            ensured(scanf(" %c", &ch)==1, "cannot read typed character");
            ensured('a'<=ch && ch<='z', "invalid character");
            Q[i][1]=ch;
            NANS++;
        }
        else
            ensured(Q[i][0]==2, "unexpected query type");
    }
    for(i=0; i<NANS; i++)
        ensured(scanf("%lld", ans+i)==1, "cannot read answer");
    scanf(" ");
    ensured(feof(stdin), "extra input at end of file");
}

int main()
{
    scanf("%d", &TEST);
    read_input();
    Init();
    int CANS=0;
    int accepted=1;
    int i;
    for(i=0; i<N; i++)
    {
        switch(Q[i][0])
        {
        case 1:
            accepted&=ans[CANS++]==Type((char)Q[i][1]);
            break;
        case 2:
            Backspace();
            break;
        }
    }
    ensure(accepted, "wrong answer");
    printf("ACCEPTED %d numbers ok\n", NANS);
    return 0;
}
