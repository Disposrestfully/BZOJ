#include<bits/stdc++.h>
#define read() Read<int>()
typedef long long ll;
#define int ll
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
const int N=1e5+5;
const int inf=1e18;
inline void ad(int &x,int y){
	if (x>inf-y) x=inf+1;
	else x+=y;
}
struct node{
	int len,cnt;
}dp[N];
int n,k,mx;
int a[N],p[N];
inline bool cmp(int x,int y){
	return a[x]>a[y];
}
inline void merge(node &v,node u){
	if (u.len<v.len) return;
	if (u.len>v.len) v.len=u.len,v.cnt=u.cnt;
	else if (u.len==v.len) ad(v.cnt,u.cnt);
}
namespace bit{
	#define lowbit(x) (x&(-x))
	node s[N];
	inline void chkmax(int x,node k){
		for (int i=x;i<=n;i+=lowbit(i))
			merge(s[i],k);
	}
	inline node query(int x){
		node res=(node){0,1};
		for (int i=x;i;i-=lowbit(i))
			merge(res,s[i]);
		return res;
	}
}
using namespace bit;
vector<int>g[N];
void solve(int x,int rk,int las){
	if (!x) return;
	int now=0;
	for (int i=0,sz=g[x].size();i<sz;++i){
		int y=g[x][i];
		if (y<las || a[y]<a[las]) continue;
		if (now>=rk-dp[y].cnt){
			p[a[y]]=1;
			solve(x-1,rk-now,y);
			return;
		}
		ad(now,dp[y].cnt);
	}
}
signed main(){
	freopen("5484.in","r",stdin);
	freopen("5484.out","w",stdout);
	n=read(),k=read();
	for (int i=1;i<=n;++i) a[i]=read();
	for (int i=1;i<=n;++i) s[i].cnt=s[i].len=0;
	for (int i=n;i;--i){
		dp[i]=query(n-a[i]+1),++dp[i].len;
		mx=max(mx,dp[i].len);
		g[dp[i].len].push_back(i);
		chkmax(n-a[i]+1,dp[i]);
	}
	for (int i=1;i<=mx;++i)
		sort(g[i].begin(),g[i].end(),cmp);
	solve(mx,k,0);
	printf("%lld\n",n-mx);
	for (int i=1;i<=n;++i)
		if (!p[i]) printf("%lld\n",i);
	return 0;
}
