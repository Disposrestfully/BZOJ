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
int n,now,top;
struct point{
	ll x,y;
	inline point operator - (const point &u){
		return (point){x-u.x,y-u.y};
	}
	inline ll operator * (const point &u){
		return x*u.y-y*u.x;
	}
}p[N],sta[N];
inline void insert(point p){
	while (top && (p-sta[top])*(sta[top]-sta[top-1])<=0) --top;
	sta[++top]=p;
}
int main(){
	freopen("5483.in","r",stdin);
	freopen("5483.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i){
		p[i].x=i;
		p[i].y=100000ll*read();
		insert(p[i]);
	}
	insert((point){n+1,0});
	for (int i=1;i<=n;++i){
		while (now<top && sta[now].x<i) ++now;
		if (sta[now].x==i) printf("%lld\n",p[i].y);
		else printf("%lld\n",((sta[now].x-i)*sta[now-1].y+(i-sta[now-1].x)*sta[now].y)/(sta[now].x-sta[now-1].x));
	}
	return 0;
}
