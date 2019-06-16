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
ll n,las=1,m=10;
int f[2][5];
int ans,Mod,p;
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
}
struct mat{
	int a[5][5];
	inline void init(int opt=0){
		memset(a,0,sizeof(a));
		if (opt){
			for (int i=1;i<=3;++i)
				a[i][i]=1;
		}
	}
	inline mat operator * (const mat &u){
		mat res;
		res.init();
		for (int i=1;i<=3;++i)
			for (int k=1;k<=3;++k)
				for (int j=1;j<=3;++j)
					ad(res.a[i][j],1ll*a[i][k]*u.a[k][j]%Mod);
		return res;
	}	
}now,tmp;
inline mat Pow(mat x,ll y){
	mat res;
	res.init(1);
	while (y){
		if (y&1ll) res=res*x;
		x=x*x;
		y>>=1ll;
	}
	return res;
}
int main(){
	freopen("2326.in","r",stdin);
	freopen("2326.out","w",stdout);
	n=read(),Mod=read();
	now.init(1),tmp.init();
	tmp.a[1][1]=m,tmp.a[3][3]=1;
	tmp.a[2][1]=tmp.a[3][1]=1;
	tmp.a[2][2]=tmp.a[3][2]=1;	
	f[p=0][3]=1;
	while (1){
		if (las==m/10) now=Pow(tmp,m-las);
		else{
			now=Pow(tmp,m-las+1);
			p^=1;
			memset(f[p],0,sizeof(f[p]));
			for (int i=1;i<=3;++i)
				for (int j=1;j<=3;++j)
					ad(f[p][j],1ll*f[p^1][i]*now.a[i][j]%Mod);
			break;	
		}
		las=m;
		tmp.a[1][1]=((m%Mod)*10)%Mod;
		if (m<=n/10) m*=10;
		else m=n;
		p^=1;
		memset(f[p],0,sizeof(f[p]));
		for (int i=1;i<=3;++i)
			for (int j=1;j<=3;++j)
				ad(f[p][j],1ll*f[p^1][i]*now.a[i][j]%Mod);
	}
	printf("%d\n",f[p][1]);	
	return 0;
}
