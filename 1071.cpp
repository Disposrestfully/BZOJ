#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<ll>()
#define lowbit(i) i&(-i)
using namespace std;
typedef long long ll;
const int N=5005;
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
struct node{
	int v,h;
	ll s;
}a[2][N];
int n,ans;
inline bool cmp1(node u,node v){
	return u.s<v.s;
}
inline bool cmp2(node u,node v){
	return u.h<v.h;
}
ll A,B,C;
inline int solve(int x){
	int l=1,r=1,res=0,sum=0;
	ll val;
	for (int i=1;i<=n;++i){
		int y=a[1][i].h;
		val=A*y+B*x+C;
		while (r<=n && a[0][r].s<=val){	
			sum+=(a[0][r].h>=a[1][l].h && a[0][r].v>=x);
			++r;
		}
		while (l<=n && a[1][l].h<y){
			sum-=(a[1][l].v>=x && a[1][l].s<=val);
			++l;
		}
		res=max(res,sum);
	}	
	return res;
}
int main(){
	//freopen("1.in","r",stdin);
	n=read();A=read();
	B=read();C=read();
	for (int i=1;i<=n;++i){
		a[0][i].h=a[1][i].h=read();
		a[0][i].v=a[1][i].v=read();
		a[0][i].s=a[1][i].s=A*a[0][i].h+B*a[0][i].v;
	}
	sort(a[0]+1,a[0]+n+1,cmp1);
	sort(a[1]+1,a[1]+n+1,cmp2);
	for (int i=1;i<=n;++i)
		ans=max(ans,solve(a[0][i].v));
	printf("%d\n",ans);
	return 0;
}
