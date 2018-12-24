#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
#define read Read<int>
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
int n,x[N],p[N],c[N],q[N];
ll f[N],s[N],sp[N];
int F,L;
inline ll Y(int x,int y){
	return ((f[x]-f[y])+(s[x]-s[y]))/(sp[x]-sp[y]);
}
int main(){
	n=read();
	for (int i=1;i<=n;++i){
		x[i]=read();
		p[i]=read();
		c[i]=read();
		s[i]=s[i-1]+1ll*x[i]*p[i];
		sp[i]=sp[i-1]+p[i];	
	}
	q[F=L=1]=0;
	for (int i=1;i<=n;++i){
		while (F<L && Y(q[F+1],q[F])<x[i]) ++F;
		int now=q[F];
		f[i]=f[now]+x[i]*(sp[i]-sp[now])-(s[i]-s[now])+c[i];
		while (F<L && Y(q[L],q[L-1])>Y(i,q[L])) --L;
		q[++L]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}

