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
const int Mod=1e4+7;
int a[50010],dp[50010][2];
int s[50010]={0};
int n,m,l=-1e9,r=0; 
int check(int x){
	int sum=0,cnt=0;
	for (int i=1;i<=n;++i){
		if (sum+a[i]>x){
			sum=0;
			cnt++;
		}
		if (cnt>m) return 0;
		sum+=a[i];
	}
	return 1; 
}
int main(){
	//freopen("stick.in","r",stdin);
	n=read();m=read();
	a[0]=0;
	for (int i=1;i<=n;++i){
		a[i]=read();
		l=l>a[i]?l:a[i];
		s[i]=s[i-1]+a[i];
	}
	r=s[n];
	while (l<r){
		int mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d ",r);
	int now=0,sum,ans=0,last;
	for (int i=1;i<=n;++i){
		if (s[i]<=r) dp[i][0]=1;
		else break;	
	} 
	for (int j=1;j<=m;++j){
		last=now;now^=1;
		sum=dp[0][last];l=1;
		for (int i=1;i<=n;++i){
			while (s[i]-s[l]>r && l<i){
				sum-=dp[l][last];
				if (sum<0) sum+=Mod;
				++l;	
			} 
			dp[i][now]=sum;
			sum+=dp[i][last];
			if (sum>Mod) sum-=Mod;
		}
		ans+=dp[n][now];
		if (ans>Mod) ans-=Mod;
	}
	printf("%d\n",ans);
	return 0;
}

