#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
int read()
{
    int x=0,f=1; char ch=getchar();
    while (ch<'0' || ch>'9') {if (ch=='-') f=-1; ch=getchar();}
    while (ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
#define maxn 20010
#define maxm 400010
int N,M,K,C,dis[maxn],d[30][maxn],ans; bool visit[maxn];
struct EdgeNode{int next,to,len,from;}edge[maxm];
int head[maxn],cnt;
void add(int u,int v,int w)
{
    cnt++;
    edge[cnt].to=v;edge[cnt].from=u;edge[cnt].len=w;edge[cnt].next=head[u];head[u]=cnt;
}
void insert(int u,int v,int w) {add(u,v,w); add(v,u,w);}

#define inf 0x7fffffff
void SPFA(int S)
{
    queue<int>q; memset(visit,0,sizeof(visit));
    for (int i=1; i<=N; i++) dis[i]=inf;
    q.push(S); visit[S]=1; dis[S]=0;
    while (!q.empty())
        {
            int now=q.front(); q.pop(); visit[now]=0;
            for (int i=head[now]; i; i=edge[i].next)
                if (dis[edge[i].to]>dis[now]+edge[i].len)
                    {
                        dis[edge[i].to]=dis[now]+edge[i].len;
                        if (!visit[edge[i].to])
                            q.push(edge[i].to),visit[edge[i].to]=1;
                    }
        }
    for (int i=1; i<=N; i++) d[S][i]=dis[i];
}
int Min(int a,int b)
{
    if (a==-1) return b;
    if (a>b) return b; else return a;
}
int dp[1<<21][30],zt[maxn];
void DP()
{
    for (int i=0; i<=(1<<K)-1; i++)
        for (int j=1; j<=K+1; j++)
            if (dp[i][j]!=-1)
                for (int k=2; k<=K+1; k++)
                    if ((i&zt[k])==zt[k])
                        dp[i|(1<<(k-2))][k]=Min(dp[i|(1<<(k-2))][k],dp[i][j]+d[j][k]);
}
int main()
{
    N=read(),M=read(),K=read();
    for (int u,v,w,i=1; i<=M; i++)
        u=read(),v=read(),w=read(),insert(u,v,w);
    for (int i=1; i<=K+1; i++) SPFA(i);
    C=read();
    for (int x,y,i=1; i<=C; i++)
        x=read(),y=read(),zt[y]|=(1<<(x-2));
    memset(dp,-1,sizeof(dp)); dp[0][1]=0;
    DP(); ans=0x7fffffff;
    for (int i=1; i<=K+1; i++)
        if (dp[(1<<K)-1][i]!=-1) ans=Min(dp[(1<<K)-1][i]+d[i][N],ans);
    printf("%d",ans);
    return 0;
}
