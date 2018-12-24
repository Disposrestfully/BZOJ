#include<bits/stdc++.h>
#include<sys/mman.h>
#define lowbit(i) i&(-i)
#define read Read<int>
using namespace std;
typedef long long ll;
const int N=1005;
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
int dp[2][N][N],all;
int w[10]={0,100,50,20,10,5,1};
int a[10][10],sum[10],t[10],cnt[10];
inline int min(int x,int y){
	if (x==-1) return y;
	return x<y?x:y;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x1=read(),x2=read(),x3=read();
	t[1]-=x1-x3;t[2]-=x2-x1;t[3]-=x3-x2;
	for (int i=1;i<=3;++i){
		for (int j=1;j<=6;++j){
			a[i][j]=read();
			sum[i]+=a[i][j]*w[j];
			cnt[j]+=a[i][j];
		}
		all+=sum[i];
		t[i]+=sum[i];
	}
	memset(dp,-1,sizeof(dp));
	dp[0][sum[1]][sum[2]]=0;
	if (t[1]<0 || t[2]<0 || t[3]<0 || t[1]+t[2]+t[3]!=all){
		 printf("impossible\n");
		 return 0;
	}
	int now=0;
	for (int i=1;i<=6;++i){
		now^=1;
		for (int s1=0;s1<=all;++s1){
			for (int s2=0;s1+s2<=all;++s2){
				if (dp[now^1][s1][s2]==-1) continue;
				//printf("%d %d %d %d\n",i-1,s1,s2,dp[i-1][s1][s2]);
				dp[now][s1][s2]=min(dp[now][s1][s2],dp[now^1][s1][s2]);
				for (int c1=0;c1<=cnt[i];++c1){
					for (int c2=0;c1+c2<=cnt[i];++c2){
						int c3=cnt[i]-c1-c2,d=abs(c1-a[1][i])+abs(c2-a[2][i])+abs(c3-a[3][i]);
					//	printf("%d %d %d %d %d %d %d %d\n",i,c1,c2,c3,d,a[1][i],a[2][i],a[3][i]);
						int s3=s1+(c1-a[1][i])*w[i],s4=s2+(c2-a[2][i])*w[i];
						dp[now][s3][s4]=min(dp[now][s3][s4],dp[now^1][s1][s2]+(d>>1));
					}
				}
			}	
		}
	}	
	if (dp[now][t[1]][t[2]]==-1) printf("impossible\n");
	else printf("%d\n",dp[now][t[1]][t[2]]);
	return 0;
}
