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
const int N=1e6+5;
int n,m;
int a[N],ans[N],las[N];
vector<int>id[N],g[N];
namespace bit{
	#define lowbit(x) (x&(-x))
	int sss[N];
	inline void add(int x,int k){
		for (int i=x;i<=n;i+=lowbit(i))
			sss[i]+=k;
	}
	inline int sum(int x){
		int res=0;
		for (int i=x;i;i-=lowbit(i))
			res+=sss[i];
		return res;
	}
	inline int query(int l,int r){
		return sum(r)-sum(l-1);	
	}
}
using namespace bit;
int main(){
	freopen("1878.in","r",stdin);
	freopen("1878.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i){
		int x=read();
		a[i]=las[x],las[x]=i;
	}
	m=read();
	for (int i=1;i<=m;++i){
		int l=read(),r=read();
		g[r].push_back(l);
		id[r].push_back(i);
	}	
	for (int i=1;i<=n;++i){
		if (a[i]) add(a[i],-1);
		add(i,1);
		for (int j=0,sz=g[i].size();j<sz;++j)
			ans[id[i][j]]=query(g[i][j],i);
	}
	for (int i=1;i<=m;++i){
		Print(ans[i]);
		if (i%100000==0 || i==m) io::flush();
	}
	return 0;
}
