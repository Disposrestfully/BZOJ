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
#define int ll
const int N=1e5+5;
int n=44,T;
int f[N];
signed main(){
	freopen("3713.in","r",stdin);
	freopen("3713.out","w",stdout);
	f[1]=f[2]=1;
	for (int i=3;i<=n;++i)
		f[i]=f[i-1]+f[i-2];
	T=read();
	while (T--){
		int x=read(),flag=0;
		for (int i=1;i<=n;++i)
			for (int j=i;j<=n;++j)
				if (1ll*f[i]*f[j]==1ll*x)
					flag=1;
		if (!x) flag=1;
		puts(flag?"TAK":"NIE");
	}
	return 0;
}
