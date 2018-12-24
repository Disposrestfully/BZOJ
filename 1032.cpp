#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#define y1 Y1
#define read() Re.Read()
#define lowbit(i) i&(-i)
//#define Get_Char() getchar()
using namespace std;
typedef long long ll;
const int N=505;
struct Readint{
	char buffer[1<<15],*S,*T; 
	inline char Get_Char(){  
    	if(S==T){  
     	   T=(S=buffer)+fread(buffer,1,1<<15,stdin);
      	  if(S==T) return EOF;  
    	}  
    	return *S++;  
	}
	int Read(){
	    char c;  
	    int re=0,w=1;  
	    for (c=Get_Char();c<'0'||c>'9';c=Get_Char()){
    		if (c==EOF) return -1;
    		if (c=='-') w=-1;
    	}	
 	   	while(c>='0'&&c<='9')
           	re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();  
    	return re*w;  
	}
}Re;
int dp[N][N],n,m;
int sz[N],s[N],a[N];
int main(){
	//freopen("2.in","r",stdin);
	n=read();
	for (int i=1;i<=n;++i) a[i]=read();
	m=0;s[0]=19260817;
	for (int i=1;i<=n;++i){
		if (a[i]!=s[m])
			s[++m]=a[i];
		++sz[m];
	}
	for (int i=1;i<=m;++i)
		for (int j=1;j<=m;++j)
			dp[i][j]=1e9;
	for (int i=1;i<=m;++i){
		if (sz[i]==1) dp[i][i]=2;
		else dp[i][i]=1;
	}
	for (int j=2;j<=m;++j){
		for (int i=1;i+j-1<=m;++i){
			int y=i+j-1;
			if (s[i]==s[y]) dp[i][y]=dp[i+1][y-1]+((sz[i]+sz[y]==2)?1:0);
			for (int k=i;k<y;++k)
				dp[i][y]=min(dp[i][y],dp[i][k]+dp[k+1][y]);
			//printf("%d %d %d\n",i,y,dp[i][y]);
		}
	}
	printf("%d\n",dp[1][m]);
	return 0;
}
