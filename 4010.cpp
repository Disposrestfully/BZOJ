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
int n,m,tot;
int ans[N],d[N];
struct edge{
	int next,to;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
priority_queue<int>q;
inline void solve(){
	q=priority_queue<int>();
	for (int i=1;i<=n;++i)
		if (!d[i]) q.push(i);
	while (!q.empty()){
		int x=q.top();
		ans[++tot]=q.top();
		q.pop();
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if ((--d[y])==0) q.push(y);
		}	
	} 
}
int main(){
	freopen("4010.in","r",stdin);
	freopen("4010.out","w",stdout);
	int T=read();
	while (T--){
		n=read(),m=read();
		memset(d,0,sizeof(d));	
		memset(head,0,sizeof(head));
		tot=0;
		for (int i=1;i<=m;++i){
			int u=read(),v=read();
			add(v,u),++d[u];
		}
		solve();
		if (tot<n) printf("Impossible!\n");
		else{
			for (int i=n;i;--i)
				Print(ans[i],i==1?'\n':' ');
			io::flush();
		}
	}
	return 0;
}
