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
const int N=1e5+5;
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
	    int re=0;  
	    for (c=Get_Char();c<'0'||c>'9';c=Get_Char()){
    		if (c==EOF) return -1;
    	}	
 	   	while(c>='0'&&c<='9')  
           	re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();  
    	return re;  
	}
}Re;
ll f[5][50],g[5][50],n;
bool vis[5];
char s[3];
int main(){
	scanf("%lld",&n);
	for (int i=1;i<=6;++i){
		scanf("%s",s);
		int l=s[0]-'A'+1,r=s[1]-'A'+1;
		if (vis[l]) continue;
		vis[l]=1;
		f[l][1]=1;
		g[l][1]=r;
	}
	for (int i=2;i<=n;++i){
		for (int j=1;j<=3;++j){
			int y=g[j][i-1];
			int k=6-j-y;
			f[j][i]=f[j][i-1]+1;
			if (k==g[y][i-1]){
				f[j][i]+=f[y][i-1];
				g[j][i]=k;
			}else{
				f[j][i]+=f[y][i-1]+1+f[j][i-1];
				g[j][i]=y;
			}
		}	
	}
	printf("%lld\n",f[1][n]);
	return 0;
}
