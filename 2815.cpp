#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
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
const int N=66000;
int dep[N],a[N][17],d[N];
int q[N],l[N],sz[N];;
int n,top,cnt,head[N];
vector <vector <int> >s; 
vector <vector <int> >s2; 
struct node{
	int next,to;
}e[N];
void init(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;	
}
void work(int x){
	for (int i=1;i<=16;++i)
		a[x][i]=a[a[x][i-1]][i-1];
}
void solve(int &u,int &v){
	if (dep[u]==dep[v]) return;
	for (int i=16;i>=0;--i)
		if (dep[a[u][i]]>dep[v])
			u=a[u][i];
	u=a[u][0];
}
int lca(int u,int v){
	if (dep[v]>dep[u]) solve(v,u);
	else solve(u,v);
	if (u==v) return u;
	for (int i=16;i>=0;--i)
		if (a[u][i]!=a[v][i]){
			u=a[u][i];
			v=a[v][i];
		}
	return a[u][0];
}
void Sort(){
	int cnt=0;
	while (top!=0){
		l[++cnt]=q[top];
		int x=q[top];
		top--;
		for (int i=0;i<s2[x].size();++i){
			int y=s2[x][i];
			if (--d[y]==0) q[++top]=y;	
		}
	}
}
void insert(int x){
	if (s[x].size()==0) return;
	int father=s[x][0];
	if (s[x].size()>=2){
		for (int i=1;i<s[x].size();++i)
			father=lca(father,s[x][i]);
	}
	a[x][0]=father;
	dep[x]=dep[father]+1;
	//printf("%d %d\n",x,father);
	init(father,x);
	work(x);
}
void dfs(int x){
	sz[x]=1;
	for (int i=head[x];i;i=e[i].next){
		//printf("%d %d\n",x,e[i].to);
		dfs(e[i].to);	
		sz[x]+=sz[e[i].to];
	}
}
int main(){
	//freopen("catas.in","r",stdin);
	//freopen("catas.out","w",stdout);
	n=read();
	s.resize(n+1);
	s2.resize(n+1);
	for (int i=0;i<n;++i){
		s[i].resize(0);
		s2[i].resize(0);		
	}
	for (int i=1;i<=n;++i)
		while (1){
			int k=read();
			if (k==0) break;
			++d[i];
			s[i].push_back(k);
			s2[k].push_back(i);	
		}
	for (int i=1;i<=n;++i){
		if (!d[i]){
			q[++top]=i;
			dep[i]=1;
			a[i][0]=0;
			init(0,i);	
		}
	}
	Sort();
	dep[0]=0;
	for (int i=1;i<=n;++i)
		insert(l[i]);
	dfs(0);
	for (int i=1;i<=n;++i)
		printf("%d\n",sz[i]-1);
	return 0;
}

