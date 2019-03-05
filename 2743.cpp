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
typedef pair<int,int> pr;
#define mp make_pair
const int N=2e6+5;
int n,m,c;
int las[N],pre[N],ans[N];
vector<pr>g[N];
namespace bit{
	#define lowbit(x) (x&(-x))
	int s[N];
	inline void add(int x,int k){
		for (int i=x;i<=n;i+=lowbit(i))
			s[i]+=k;
	}
	inline int sum(int x){
		int res=0;
		for (int i=x;i;i-=lowbit(i))
			res+=s[i];
		return res;
	}
	inline int query(int l,int r){
		return sum(r)-sum(l-1);
	}
}
using namespace bit;
int main(){
	freopen("2743.in","r",stdin);
	freopen("2743.out","w",stdout);
	n=read(),c=read(),m=read();
	for (int i=1;i<=n;++i){
		int x=read();
		pre[i]=las[x],las[x]=i;
	}
	for (int i=1;i<=m;++i){
		int l=read(),r=read();
		g[r].push_back(mp(l,i));
	}
	for (int i=1;i<=n;++i){
		if (pre[pre[i]]) add(pre[pre[i]],-1);
		if (pre[i]) add(pre[i],1);
		for (int j=0,sz=g[i].size();j<sz;++j){
			ans[g[i][j].second]=query(g[i][j].first,i);
		}
	}
	for (int i=1;i<=m;++i){
		Print(ans[i]);
		if (i==m || i%100000==0) io::flush();
	}
	return 0;
}
