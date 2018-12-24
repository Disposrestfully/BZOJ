#pragma GCC optimize (2)
#pragma G++ optimize (2)
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cctype>
#include<queue>
#define read Read<int>
using namespace std;
namespace pb_ds{   
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0; 
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100]; 
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
const int N=1e5+5;
const int M=4e6+5;
vector<int>a[N];
queue<int>q;
int ans[N],sz;
int n,m,cnt,vis[N];
struct list_node{
	int next,pre;
};
struct list{
	list_node s[N];
	int head,tail;
	void init(){
		for (int i=1;i<=n;++i){
			s[i].pre=i-1;
			s[i].next=i+1;	
		}
		s[1].pre=s[n].next=0;
		head=1;tail=n;
	}
	void del(int x){
		if (x==head) head=s[x].next;
		if (x==tail) tail=s[x].pre;
		s[s[x].pre].next=s[x].next;
		s[s[x].next].pre=s[x].pre;
	}
}ls;
void bfs(int s){
	q.push(s);
	vis[s]=1;
	ls.del(s);
	while (!q.empty()){
		int x=q.front();
		q.pop();
		int now=0;
		for (int i=ls.head;i;i=ls.s[i].next){
			while (now<a[x].size()-1 && a[x][now]<i) ++now;
			if (a[x][now]!=i){
				q.push(i);
				ls.del(i);
				vis[i]=1;
				++sz;
			}
		}
	}
}
int main(){
    n=read();m=read();
    for (int i=1;i<=m;++i){
        int u=read(),v=read();
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for (int i=1;i<=n;++i){
        a[i].push_back(n+1);
        a[i].push_back(0);
        sort(a[i].begin(),a[i].end());
    }
    ls.init();
    for (int i=1;i<=n;++i)
        if (!vis[i]){
            sz=1;
            bfs(i);
            ans[++cnt]=sz;
        }
    sort(ans+1,ans+cnt+1);
    printf("%d\n",cnt);
    for (int i=1;i<cnt;++i)
        printf("%d ",ans[i]);
    printf("%d\n",ans[cnt]);
    return 0;
}
