#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=2e6+5;
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
int n,Mod,cnt[N];
int isprime[N],prime[N],ptot;
inline void get_prime(int prange){
	isprime[1]=1;
	for (int i=2;i<=prange;++i){
		if (!isprime[i]) prime[++ptot]=i;
		for (int j=1;j<=ptot && prime[j]*i<=prange;++j){
			isprime[i*prime[j]]=1;
			if (!(i%prime[j])) break;	
		}
	}
}
inline int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=1ll*res*x%Mod;
		x=1ll*x*x%Mod;
		y>>=1;
	}
	return res;
}
int main(){
	freopen("1485.in","r",stdin);
	freopen("1485.out","w",stdout);
	n=read(),Mod=read();
	get_prime(n<<1);
	for (int i=2;i<=(n<<1);++i){
		int x=i;
		for (int j=1;prime[j]*prime[j]<=x && j<=ptot;++j)
			while (!(x%prime[j])){
				++cnt[prime[j]],x/=prime[j];
				if (i<=n+1) --cnt[prime[j]];
				if (i<=n) --cnt[prime[j]];
			}
		if (x!=1){
			++cnt[x];
			if (i<=n+1) --cnt[x];
			if (i<=n) --cnt[x];
		}
	}
	int ans=1;
	for (int i=1;i<=ptot;++i)
		ans=1ll*Pow(prime[i],cnt[prime[i]])*ans%Mod;
	printf("%d\n",ans);
	return 0;
}
