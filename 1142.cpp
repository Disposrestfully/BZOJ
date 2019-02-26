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
const int N=1005;
int n,m;
int rk[N],w[N];
inline bool cmp(int x,int y){
	return w[x]<w[y];
}
struct mat{
	int a[N][N];
	inline void print(){
		for (int i=1;i<=n;++i){
			for (int j=1;j<=m;++j)
				printf("%d ",a[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	inline void input(){
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)
				a[i][j]=read();
	}
	inline bool operator == (const mat &u)const{
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)
				if (a[i][j]!=u.a[i][j])
					return 0;
		return 1;
	}
	inline void trans(int opt){
		int b[N][N];
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)
				b[i][j]=a[i][j];
		if (opt){
			for (int i=1;i<=n;++i)
				for (int j=1;j<=m;++j)
					a[i][j]=b[rk[i]][j];
		}else{
			for (int i=1;i<=m;++i)
				for (int j=1;j<=n;++j)
					a[j][i]=b[j][rk[i]];
		}
	}
	inline void solve(){
		int x=0,y=0;
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)
				if (!x || a[i][j]<a[x][y])
					x=i,y=j;
		for (int i=1;i<=m;++i)
			swap(a[1][i],a[x][i]);
		for (int i=1;i<=n;++i)
			swap(a[i][1],a[i][y]);
		for (int i=1;i<=n;++i)
			w[i]=a[i][1],rk[i]=i;
		sort(rk+1,rk+n+1,cmp),trans(1);
		for (int i=1;i<=m;++i)
			w[i]=a[1][i],rk[i]=i;
		sort(rk+1,rk+m+1,cmp),trans(0);
	}
}s1,s2;
int main(){
	freopen("1142.in","r",stdin);
	freopen("1142.out","w",stdout);
	int T=read();
	while (T--){
		n=read(),m=read();
		s1.input(),s1.solve();
		s2.input(),s2.solve();
		if (s1==s2) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}
