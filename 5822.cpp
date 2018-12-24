#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=1e6+5;
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
struct edge{
	int next,to;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	//printf("%d %d\n",u,v);
}
int l[N],r[N],p[N],d[N],pos[N];
int n,m,q,tot=1,id[N],rk[N];
queue<int>qu;
inline void tp(){
	for (int i=1;i<=tot;++i)
		if (!d[i]) qu.push(i),rk[i]=0;
	while (!qu.empty()){
		int x=qu.front();
		qu.pop();
		int flag=1;
		while (flag){
			flag=0;
			if (l[x]>1 && pos[id[l[x]-1]]>=l[x] && pos[id[l[x]-1]]<=r[x]) l[x]=l[id[l[x]-1]],flag=1;
			if (r[x]<n && pos[id[r[x]]]>=l[x] && pos[id[r[x]]]<=r[x]) r[x]=r[id[r[x]+1]],flag=1;
		}
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if ((--d[y])==0) qu.push(y),rk[y]=rk[x]+1;
		}
	}
}
int main(){
	freopen("5822.in","r",stdin);
	freopen("5822.out","w",stdout);
	n=read(),m=read(),q=read();
	for (int i=1;i<=m;++i){
		int x=read();
		p[x]=read();	
	}
	for (int i=1;i<=n;++i){
		id[i]=tot;
		r[tot]=i;
		if (!l[tot]) l[tot]=i;
		if (p[i]) pos[tot]=p[i],++tot;
	}
	for (int i=1;i<=n;++i)
		if (p[i]){
			if (p[i]<=i) add(id[i+1],id[i]),++d[id[i]];
			else add(id[i],id[i+1]),++d[id[i+1]];
		}
	tp();
	for (int i=1;i<=q;++i){
		int s=read(),t=read();
		if (l[id[s]]<=t && r[id[s]]>=t) printf("YES\n");
		else printf("NO\n"); 
	}		
	return 0;
}
