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
int n,m,p,q;
int f[N],col[N];
int find(int x){
	if (f[x]==x) return x;
	return f[x]=find(f[x]);
}
int main(){
	freopen("2054.in","r",stdin);
	freopen("2054.out","w",stdout);
	n=read(),m=read();
	p=read(),q=read();
	for (int i=1;i<=n+1;++i) f[i]=i;
	for (int i=m;i;--i){
		int l=(i*p+q)%n+1,r=(i*q+p)%n+1;
		if (l>r) swap(l,r);
		for (int j=find(l);j<=r;j=find(j)) col[j]=i,f[j]=j+1;
	}	
	for (int i=1;i<=n;++i){
		Print(col[i]);
		if (i==n || i%100000==0) io::flush();
	}
	return 0;
}
