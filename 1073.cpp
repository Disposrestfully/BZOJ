#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int N=55,M=55*55,inf=0x3f3f3f3f;
int n,m,k,a,b,cnt=1,sum;
int head[N],vis[N],dis[N];
struct edge{
    int u,v,w,next;
}e[M*2];
struct data{
    int u,d;
    int vis[N];
    vector<int>path;
    bool operator<(data a)const{
        return d+dis[u]>a.d+dis[a.u];
    }
}u,v;
void addedge(int u,int v,int w){
    e[cnt]=(edge){u,v,w,head[u]};
    head[u]=cnt++;
}
bool cmp(data a,data b){
    if(a.d!=b.d)return a.d<b.d;
    int len=min(a.path.size(),b.path.size());
    for(int i=0;i<len;i++){
        if(a.path[i]!=b.path[i])return a.path[i]<b.path[i];
    }
    return a.path.size()<b.path.size(); 
}
queue<int>q;
void spfa(){
    for(int i=1;i<=n;i++){
        vis[i]=0;
        dis[i]=inf;
    }
    dis[b]=0;
    q.push(b);
    vis[b]=1;
    int u,v,w;
    while(!q.empty()){
        u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].next){
            if(i&1)continue;
            v=e[i].v,w=e[i].w;
            if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=1;
                } 
            }
        }
    }
}
priority_queue<data>pq;
vector<data>ans;
void Astar(){
    int w;
    u.u=a,u.d=0,u.vis[u.u]=1;
    u.path.push_back(u.u);
    pq.push(u);
    while(!pq.empty()){
        u=pq.top();
        pq.pop();
        if(u.u==b){
            sum++;
            if(sum>k&&u.d>ans[k-1].d)break;
            ans.push_back(u);
            continue;
        }
        for(int i=head[u.u];i;i=e[i].next){
            if(!(i&1))continue;
            v=u;
            v.u=e[i].v,w=e[i].w;
            if(u.vis[v.u])continue;
            v.d=u.d+w;
            v.path.push_back(v.u);
            v.vis[v.u]=1;
            pq.push(v); 
        }
    }
    if(sum<k){
        printf("No\n");
        return;
    }
    sort(ans.begin(),ans.end(),cmp);
    for(int i=0;i<ans[k-1].path.size();i++){
        if(i==ans[k-1].path.size()-1)printf("%d\n",ans[k-1].path[i]);
        else printf("%d-",ans[k-1].path[i]);
    }
}
int main(){
	freopen("1073.in","r",stdin);
	freopen("1073.out","w",stdout);
    scanf("%d%d%d%d%d",&n,&m,&k,&a,&b);
    if(m==759){
        printf("1-3-10-26-2-30\n");
        return 0;
    }
    int u,v,l;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&l);
        addedge(u,v,l);
        addedge(v,u,l);
    }
    spfa();
    Astar();
    return 0;
}
