#include<bits/stdc++.h>
#define read() Read<ll>()
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
ll T,n;
namespace sub1{
	ll tot,now,ans;
	ll dp[2][2][2],s[105];
	inline void trans(ll x){
		tot=0;
		while (x){
			s[++tot]=x&1;
			x>>=1;
		}
		reverse(s+1,s+tot+1);
	}
	inline void solve(){
		trans(n),ans=0;
		memset(dp,0,sizeof(dp));
		now=0,dp[0][0][0]=1;
		for (int i=1;i<=tot;++i){
			now^=1;
			memset(dp[now],0,sizeof(dp[now]));
			for (int j=0;j<=1;++j){
				if (j==s[i]){
					dp[now][j][0]+=dp[now^1][0][0];
					if (!j) dp[now][j][0]+=dp[now^1][1][0];
					dp[now][j][1]+=dp[now^1][0][1];
					if (!j) dp[now][j][1]+=dp[now^1][1][1];
				}else if (j<s[i]){
					dp[now][j][1]+=dp[now^1][0][0];
					if (!j) dp[now][j][1]+=dp[now^1][1][0];
					dp[now][j][1]+=dp[now^1][0][1];
					if (!j) dp[now][j][1]+=dp[now^1][1][1];
				}else{
					dp[now][j][1]+=dp[now^1][0][1];
					if (!j) dp[now][j][1]+=dp[now^1][1][1];
				}
			}	
		}
		for (int i=0;i<=1;++i)
			for (int j=0;j<=1;++j)
				ans+=dp[now][i][j];
		printf("%lld\n",ans-1);
	}
}
namespace sub2{
	struct mat{
		int a[2][2];
		inline void init(int opt=0){
			memset(a,0,sizeof(a));
			if (opt) a[0][0]=a[1][1]=1;
		}
		inline mat operator * (const mat &u){
			mat res;
			res.init();
			for (int i=0;i<=1;++i)
				for (int k=0;k<=1;++k)
					for (int j=0;j<=1;++j)
						ad(res.a[i][j],1ll*a[i][k]*u.a[k][j]%Mod);
			return res;
		}
	}bas;
	inline mat Pow(mat x,ll y){
		mat res;
		res.init(1);
		while (y){
			if (y&1) res=res*x;
			x=x*x;
			y>>=1;
		}
		return res;
	}
	inline void solve(){
		bas.a[0][1]=bas.a[0][0]=1;
		bas.a[1][0]=1,bas.a[1][1]=0;
		bas=Pow(bas,n);
		ad(bas.a[0][0],bas.a[0][1]);
		printf("%d\n",bas.a[0][0]);
	}
}
int main(){
	freopen("3329.in","r",stdin);
	freopen("3329.out","w",stdout);
	T=read();
	while (T--){
		n=read();
		sub1::solve();
		sub2::solve();
	}
	return 0;
}
