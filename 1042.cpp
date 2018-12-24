#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define read Read<int>
using namespace std;
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
long long f[100010],ans;
int c[5],d[5],s; 
void solve(int x){
	int cnt=0,sum=0;
	for (int i=0;i<4;++i){
		if (x&(1<<i)){
			sum+=c[i]*(d[i]+1);
			cnt++;	
		}
	}
	if (sum>s) return;
	if (cnt%2==1) ans-=f[s-sum];
	else ans+=f[s-sum];
}
int main(){
	//freopen("coin.in","r",stdin);
	for (int i=0;i<4;++i)
		c[i]=read();
	f[0]=1;
	for (int i=0;i<4;++i)
		for (int j=1;j<=100000;++j)
			if (j>=c[i]) f[j]+=f[j-c[i]];
	int T=read();
	while (T--){
		ans=0;
		for (int i=0;i<4;++i) 
			d[i]=read();
		s=read();
		for (int i=0;i<16;++i)
			solve(i);
		printf("%lld\n",ans);	
	}
	return 0;
}

