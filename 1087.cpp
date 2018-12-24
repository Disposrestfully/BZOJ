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
int n,m;
long long dp[15][105][1030];
int cnt[1030];
void solve(int x){
	cnt[x]=0;
	int k=x;
	while (x){
		cnt[k]+=x&1;
		x>>=1;
	}
}
int main(){
	n=read();m=read();
	for (int i=0;i<1<<n;++i){
		solve(i);
		dp[1][cnt[i]][i]++;	
	}
	for (int i=1;i<n;++i)
		for (int j=0;j<=m;++j)
			for (int k=0;k<1<<n;++k){
				if (k&(k>>1) || cnt[k]>j) continue;
			//	printf("%d %d %d %d\n",i,j,k,dp[i][j][k]);
				for (int t=0;t<1<<n;++t){
					if (t&(t>>1) || j+cnt[t]>m) continue;
					int k1=k<<1,k2=k>>1;
					if (!(t&k1) && !(t&k2) && !(t&k))
						dp[i+1][j+cnt[t]][t]+=dp[i][j][k];
				}
			}
	long long ans=0;
	for (int i=0;i<1<<n;++i)
		if (cnt[i]<=m)
			ans+=dp[n][m][i];
	printf("%lld\n",ans);
	return 0;
}

