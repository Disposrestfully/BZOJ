#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
using namespace std;
typedef double ll;
const int N=305;
const ll inf=(ll)1e20;
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
int n;
ll x[N],y[N];
ll ans=inf;
inline ll calc(int i,ll dx){
	ll len=y[i]+(y[i+1]-y[i])/(x[i+1]-x[i])*(dx-x[i]);
	ll res=0;
	for (int j=1;j<=n;++j){
		if (j==i || j==i+1) continue;
		int p=(j<=i)?(j+1):(j-1);
		ll h=y[j]+(y[p]-y[j])/(x[p]-x[j])*(dx-x[j]);
		res=max(res,h-len);
	}
	return res;
}
int main(){
//	freopen("1.in","r",stdin);
	n=read();
	for (int i=1;i<=n;++i) x[i]=read();
	for (int i=1;i<=n;++i) y[i]=read();
	for (int i=1;i<n;++i){
		ll l=x[i],r=x[i+1];
		while (fabs(r-l)>1e-9){
			ll len=(r-l)/3;
			ll lm=l+len,rm=r-len;
			if (calc(i,lm)>calc(i,rm)) l=lm;
			else r=rm;
			//printf("%.3lf %.3lf\n",l,r);
		}
		ans=min(ans,calc(i,l));
	}
	if (n==1) ans=0;
	printf("%.3lf\n",ans);
	return 0;
}
