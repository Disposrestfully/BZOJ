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
const int N=1e4+5;
const int M=105;
int n,m,ans,mn;
int a[N],s[N][M];
namespace bit{
	#define lowbit(x) (x&(-x))
	int sss[N];
	inline void add(int x,int k){
		for (int i=x;i<=m;i+=lowbit(i))
			sss[i]+=k;
	}
	inline int sum(int x){
		int res=0;
		for (int i=x;i;i-=lowbit(i))
			res+=sss[i];
		return res;
	}
	inline int query(int l,int r){
		if (l>r) return 0;
		return sum(r)-sum(l-1);	
	}
}
using namespace bit;
int main(){
	freopen("1786.in","r",stdin);
	freopen("1786.out","w",stdout);
	n=read(),m=mn=read();
	for (int i=1;i<=n;++i) a[i]=read();
	for (int i=n;i;--i){
		for (int j=1;j<=m;++j)
			s[i][j]=s[i+1][j];
		if (a[i]==-1) continue;
		for (int j=a[i]+1;j<=m;++j)
			++s[i][j];
	}
	for (int i=1;i<=n;++i){
		if (a[i]==-1){
			mn=1e9;
			for (int j=1;j<=m;++j)
				mn=min(mn,query(j+1,m)+s[i][j]);
			for (int j=1;j<=m;++j)
				if (mn==query(j+1,m)+s[i][j]){
					a[i]=j;
					break;
				}
		}
		ans+=query(a[i]+1,m);
		add(a[i],1);
	}
	printf("%d\n",ans);
	return 0;
}
