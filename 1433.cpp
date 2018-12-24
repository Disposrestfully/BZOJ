#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
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
int n,T; 
int p[100],q[100];
int f[100],vis[100];
struct node{
	int next,to;
}a[100010];
int head[100],cnt,tot;
void init(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
int dfs(int x){
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (!vis[y]){
			vis[y]=1;
			if (!f[y] || dfs(f[y])){
				f[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	//freopen("hol.in","r",stdin);
	T=read();
	while (T--){
		n=read();
		tot=0;
		cnt=0;
		memset(head,0,sizeof(head));
		memset(f,0,sizeof(f));
		for (int i=1;i<=n;++i)
			p[i]=read();
		for (int i=1;i<=n;++i){
			int k=read();
			if (p[i]){
				q[i]=k;
				if (!q[i]) init(i,i);	
			}
		}
		for (int i=1;i<=n;++i)
			if (!p[i] || (p[i] && !q[i]))
				tot++;
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j){
				int k=read();
				if (k && p[j])
					init(i,j);
			}		
		for (int i=1;i<=n;++i){
			memset(vis,0,sizeof(vis));
			if (!p[i] || (p[i] && !q[i]))
				dfs(i);	
		}
		int ans=0;
		for (int i=1;i<=n;++i)
			if (f[i]) ans++;
		if (ans>=tot) printf("%c%c%c\n",94,95,94);
		else printf("%c%c%c\n",84,95,84); 
	}
	return 0;
}

