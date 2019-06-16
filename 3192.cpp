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
int n1,n2,n,pos;
int a[N],p[N];
ll ans;
namespace bit{
	#define lowbit(x) (x&(-x))
	int sss[N];
	inline void add(int x,int k){
		for (int i=x;i<=n;i+=lowbit(i))
			sss[i]+=k;
	}
	inline int sum(int x){
		int res=0;
		for (int i=x;i;i-=lowbit(i))
			res+=sss[i];
		return res;
	}
}
using namespace bit;
inline bool cmp(int u,int v){
	return a[u]>a[v];
}
int main(){
	freopen("3192.in","r",stdin);
	freopen("3192.out","w",stdout);
	n1=read(),n2=read(),n=n1+n2;
	for (int i=n1;i;--i) a[i]=read();
	for (int i=n1+1;i<=n1+n2;++i) a[i]=read();
	for (int i=1;i<=n;++i) p[i]=i;
	sort(p+1,p+n+1,cmp);
	for (int i=1;i<=n;++i) add(i,1);
	pos=n1;
	/*for (int i=1;i<=n;++i)
		printf("%d ",a[i]);
	puts("");*/
	for (int i=1;i<=n;++i){
		if (p[i]>pos) ans+=sum(p[i]-1)-sum(pos);
		else ans+=sum(pos)-sum(p[i]);
		//printf("%d %d %d\n",pos,p[i],query(pos,p[i])-1);
		pos=p[i],add(p[i],-1);
	}
	printf("%lld\n",ans);
	return 0;
}
