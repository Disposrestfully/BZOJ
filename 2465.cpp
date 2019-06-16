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
const int N=205;
int n,m,ans1,ans2;
int w[N];
struct node{
	int c,q;
	inline bool operator < (const node &u)const{
		return q>u.q;
	}
}a[N];
int main(){
	freopen("2465.in","r",stdin);
	freopen("2465.out","w",stdout);
	while (1){
		n=read(),m=read();
		ans1=ans2=0;
		if (!n && !m) break;
		for (int i=1;i<=n;++i) w[i]=read();
		sort(w+1,w+n+1);
		reverse(w+1,w+n+1);
		for (int i=1;i<=m;++i)
			a[i].c=read(),a[i].q=read();
		sort(a+1,a+m+1);
		for (int i=1;i<=n;++i){
			for (int j=1;j<=m && a[j].q>=w[i];++j)
				if (a[j].c){
					--a[j].c,++ans1,ans2+=w[i];
					break;
				}
		}
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
