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
#define Get_Char() getchar()
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int Mod=1e9+7;
struct Readint{
	char buffer[1<<15],*S,*T; 
	/*inline char Get_Char(){  
    	if(S==T){  
     	   T=(S=buffer)+fread(buffer,1,1<<15,stdin);
      	  if(S==T) return EOF;  
    	}  
    	return *S++;  
	}*/
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
struct node{
	int cnt[6],l;
	bool operator <(const node &u)const{
		if (l!=u.l) return l<u.l;
		for (int i=1;i<=5;++i)
			if (u.cnt[i]!=cnt[i]) return cnt[i]<u.cnt[i];
		return 0;
	}
};
map<node,int>mp;
map<node,bool>vis;
int solve(node x){
	/*for (int i=1;i<=5;++i)
		printf("%d ",x.cnt[i]);
	printf("%d %d\n",x.l,vis[x]);*/
	if (vis[x]) return mp[x];
	int flg=0;
	for (int i=1;i<=5;++i)
		if (x.cnt[i]){
			flg=1;
			break;
		}
	vis[x]=1;
	if (!flg) return mp[x]=1;
	node y=x;
	int res=0;
	for (int i=1;i<=5;++i){
		if (x.cnt[i]){
			if (i!=x.l-1){
				y.l=i;
				--y.cnt[i];
				++y.cnt[i-1];
				res=(res+((ll)solve(y)*x.cnt[i])%Mod)%Mod;
				++y.cnt[i];
				--y.cnt[i-1];
			}else{
				y.l=i;
				--y.cnt[i];
				++y.cnt[i-1];
				res=(res+((ll)solve(y)*(x.cnt[i]-1))%Mod)%Mod;
				++y.cnt[i];
				--y.cnt[i-1];
			}
		}
	}
	mp[x]=res;
	return res;
}
int main(){
	node x;
	x.l=0;
	int n=read();
	for (int i=1;i<=5;++i)
		x.cnt[i]=0;
	for (int i=1;i<=n;++i){
		int k=read();
		++x.cnt[k];
	}
	printf("%d\n",solve(x));
	return 0;
}
