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
const int N=2005;
int n,m,tot,flag;
int a[N],col[N];
int cnt[N][2],dp[N]={1};
void dfs(int x,int now){
	++cnt[tot][col[x]=now];
	for (int i=1;i<=n;++i){
		if (i==x || ((i<x)==(a[i]<a[x]) && a[i]!=a[x])) continue;
		if (col[i]==col[x]){
			flag=1;
			return;
		}
		if (!(~col[i])) dfs(i,now^1);
	}
}
int main(){
	freopen("1489.in","r",stdin);
	freopen("1489.out","w",stdout);
	int T=read();
	while (T--){
		n=read(),tot=flag=0,m=n>>1;
		for (int i=1;i<=n;++i)
			a[i]=read(),col[i]=-1,dp[i]=0;
		for (int i=1;i<=n;++i)
			if (!(~col[i])){
				++tot;
				cnt[tot][0]=cnt[tot][1]=0;
				dfs(i,0);
				if (flag) break;	
			}		
		if (flag){
			puts("No!");
			continue;
		}
		for (int i=1;i<=tot;++i){
			for (int j=m;~j;--j)
				if (dp[j]) dp[j+cnt[i][0]]=dp[j+cnt[i][1]]=1;
		}
		if (dp[m]) puts("Yes!");
		else puts("No!");
	}
	return 0;
}
