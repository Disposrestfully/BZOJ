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
const int Mod=1e9+7;
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
}
int n,ans;
int a[N],w[N],p[N];
int las[N],dp[N];
namespace bit{	
	#define lowbit(x) (x&(-x))
	int s[N];
	inline void add(int x,int k){
		for (int i=x;i<=n;i+=lowbit(i))
			ad(s[i],k);
	}	
	inline int query(int x){
		int res=0;
		for (int i=x;i;i-=lowbit(i))
			ad(res,s[i]);
		return res;
	}
}
using namespace bit;
int main(){
	freopen("5157.in","r",stdin);
	freopen("5157.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i)
		a[i]=w[i]=read();
	sort(w+1,w+n+1);
	for (int i=1;i<=n;++i)
		a[i]=lower_bound(w+1,w+n+1,a[i])-w;
	for (int i=1;i<=n;++i){
		dp[i]=query(a[i]-1);
		ad(dp[i],1);
		ad(dp[i],Mod-las[a[i]]);
		if (!p[a[i]]) p[a[i]]=1,ad(ans,-1);
		add(a[i],dp[i]);
		ad(las[a[i]],dp[i]);
		ad(ans,dp[i]);
	}	
	printf("%d\n",ans);
	return 0;
}
