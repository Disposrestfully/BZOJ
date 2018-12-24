#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#define maxn 1000010
#define inf (~0U>>1)
 
using namespace std;
 
int n,m,ans;
int a[maxn],b[maxn];
char c[20];
map<int,int>ms;
set<int>bt;
 
void update(int x){
    if (bt.count(x)) {
        ans=0; return;
    }
    set<int>::iterator p=bt.upper_bound(x);
    if (p!=bt.end()) ans=min(ans,abs(*p-x));//,printf("%d->%d ",x,*p);
    --p;
    if (*p!=-inf) ans=min(ans,abs(*p-x));//,printf("%d<-%d",x,*p); printf("\n");
    bt.insert(x);
}
 
void insert(int x){
    map<int,int>::iterator p=ms.find(x);
    if (p!=ms.end()) p->second++; else ms.insert(pair<int,int>(x,1));
}
 
void erase(int x){
    map<int,int>::iterator p=ms.find(x);
    if (p->second==1) ms.erase(p); else p->second--;
}
 
void printbt(){
    for (set<int>::iterator p=bt.begin();p!=bt.end();p++) printf("%d ",*p); printf("\n");
}
 
void printms(){
    for (map<int,int>::iterator p=ms.begin();p!=ms.end();p++) printf("|%d %d\n",p->first,p->second);
}
 
int main(){
    ans=inf; bt.insert(-inf);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=1;i<n;i++) insert(abs(a[i]-a[i+1]));
    for (int i=1;i<=n;i++) { 
        if (bt.count(a[i])) {
            ans=0; break;
        }
        update(a[i]);
    }
    //printms(); printbt();
    while (m--){
        scanf("%s",&c);
        if (c[0]=='I'){
            int x,y;
            scanf("%d%d",&x,&y);
            if (x==n){
                if (b[x]) insert(abs(b[x]-y)); else insert(abs(a[x]-y));
            } else {
                if (b[x]){
                    erase(abs(b[x]-a[x+1]));
                    insert(abs(b[x]-y)); insert(abs(a[x+1]-y));
                } else {
                    erase(abs(a[x]-a[x+1]));
                    insert(abs(a[x]-y)); insert(abs(a[x+1]-y));
                }
            }
            b[x]=y;
            if (ans) update(y);
        } else
        if (c[4]=='G') {
            printf("%d\n",ms.begin()->first);
        } else printf("%d\n",ans);
    }
    return 0;
}
