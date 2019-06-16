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
const int N=2e6+5;
int n,m,ans;
int c[N];
vector<int>g[N];
inline bool cmp(int x,int y){
	return c[x]<c[y];
}
void dfs(int x){
	c[x]+=g[x].size();
	for (int i=0,sz=g[x].size();i<sz;++i)
		dfs(g[x][i]);
	sort(g[x].begin(),g[x].end(),cmp);
	for (int i=0,sz=g[x].size();i<sz;++i){
		if (c[x]+c[g[x][i]]-1<=m){
			c[x]+=c[g[x][i]]-1;
			++ans;
		}else break;
	}
}
int main(){
	freopen("4027.in","r",stdin);
	freopen("4027.out","w",stdout);
	n=read(),m=read();
	for (int i=0;i<n;++i) c[i]=read();
	for (int i=0;i<n;++i){
		int tot=read();
		for (int j=1;j<=tot;++j)
			g[i].push_back(read());
	}
	dfs(0);
	printf("%d\n",ans);
	return 0;
}
