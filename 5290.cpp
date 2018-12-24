#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=4e4+5;
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
int n,a[N],b[N],c[N];
int ch[N][2];
ll mp[N][41][41];
ll dfs(int x,int k1,int k2){
	if (x>=n) return 1ll*c[x-n+1]*(a[x-n+1]+k1)*(b[x-n+1]+k2);
	if (mp[x][k1][k2]) return mp[x][k1][k2];
	ll ans0,ans1;
	ans0=dfs(ch[x][0],k1+1,k2)+dfs(ch[x][1],k1,k2);
	ans1=dfs(ch[x][0],k1,k2)+dfs(ch[x][1],k1,k2+1);
	//printf("%d %d %d %lld %lld\n",x,k1,k2,ans1,ans0);
	return mp[x][k1][k2]=min(ans1,ans0);
}
int main(){
	freopen("5290.in","r",stdin);
	freopen("5290.out","w",stdout);
	n=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read();
		if (u<0) u=n-u-1;
		if (v<0) v=n-v-1;
		ch[i][0]=u;
		ch[i][1]=v;
	}
	for (int i=1;i<=n;++i)
		a[i]=read(),b[i]=read(),c[i]=read();
	printf("%lld\n",dfs(1,0,0));
	return 0;
}
