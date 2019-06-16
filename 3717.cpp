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
const int N=155;
const int S=(1<<24)+5;
int n,m,all;
int w[N],val[N];
struct node{
	int f,g;
	inline bool operator < (const node &u)const{
		if (f!=u.f) return f<u.f;	
		return g>u.g;
	}		
}dp[S];
int main(){
	freopen("3717.in","r",stdin);
	freopen("3717.out","w",stdout);
	n=read(),m=read(),all=(1<<n)-1;
	for (int i=1;i<=n;++i) w[i]=read();
	for (int i=1;i<=m;++i) val[i]=read();
	sort(val+1,val+m+1),reverse(val+1,val+m+1);
	dp[0]=(node){0,0};
	for (int i=1;i<=all;++i){
		dp[i]=(node){m+1,0};
		for (int j=1;j<=n;++j)
			if (i&(1<<(j-1))){
				int pre=i^(1<<(j-1));
				node now=dp[pre];
				if (now.g>=w[j]) now.g-=w[j];
				else{
					if (val[now.f+1]>=w[j]){
						now.g=val[now.f+1]-w[j];
						++now.f;
					}else now=(node){m+1,0};
				}
				if (now<dp[i]) dp[i]=now;
			}
		//printf("%d %d\n",dp[i].f,dp[i].g);
	}
	if (dp[all].f==m+1) puts("NIE");
	else printf("%d\n",dp[all].f);
	return 0;
}
