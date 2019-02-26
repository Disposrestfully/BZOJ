#include<bits/stdc++.h>
#define read() Read<int>()
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
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,k;
ll ans,w[N];
int a[N],vis[N];
int l[N],r[N];
struct cmp{
    inline bool operator ()(const int a,const int b){ 
    	return w[a]>w[b];
    } ;
};
priority_queue<int,vector<int>,cmp>q;
int main(){
	freopen("1150.in","r",stdin);
	freopen("1150.out","w",stdout);
	n=read();k=read();
	for (int i=1;i<=n;++i) a[i]=read();
	for (int i=2;i<=n;++i){
		w[i]=a[i]-a[i-1];
		l[i]=i-1,r[i]=i+1;
		q.push(i);	
	}
	l[1]=1,r[n+1]=n+1;
	w[1]=w[n+1]=(ll)1e18;
	for (int cas=1;cas<=k;++cas){
		while (vis[q.top()]) q.pop();
		int x=q.top();q.pop();
		ans+=w[x];
		w[x]=w[l[x]]+w[r[x]]-w[x];
		q.push(x);
		vis[l[x]]=vis[r[x]]=1;
		l[x]=l[l[x]],r[x]=r[r[x]];
		l[r[x]]=r[l[x]]=x;	
	}
	printf("%lld\n",ans);
	return 0;
}
