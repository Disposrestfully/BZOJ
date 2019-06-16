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
const int N=1e5+5;
int n,h,ans;
int f[N];
struct node{
	int x,y;
	inline bool operator < (const node &u)const{
		return x+y<u.x+u.y;
	}
}a[N];
int main(){
	freopen("3174.in","r",stdin);
	freopen("3174.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read(),f[0]+=a[i].x;
	sort(a+1,a+n+1);
	h=read();
	for (int i=1;i<=n;++i){
		for (int j=ans;~j;--j)
			if (f[j]+a[i].y>=h){
				f[j+1]=max(f[j+1],f[j]-a[i].x);
				if (j==ans) ++ans;
			}
	}
	printf("%d\n",ans);
	return 0;
}
