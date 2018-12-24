#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=2e5+5;
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
int n,ans,p,m;
int s[N],a[N];
namespace seg{
	#define ls (x<<1)
	#define rs (ls|1)
	#define mid (l+r>>1)
	int t[N<<2],mx[N<<2];
	int solve(int x,int l,int r,int w){
		if (l==r) return l+max(mx[x],w);
		if (mx[rs]>=w) return min(t[x],solve(rs,mid+1,r,w));
		return min(solve(ls,l,mid,w),mid+1+w);
	}
	inline void pushup(int x,int l,int r){
		t[x]=solve(ls,l,mid,mx[rs]);
		mx[x]=max(mx[ls],mx[rs]);
	}
	void build(int x,int l,int r){
		if (l==r){
			t[x]=s[l],mx[x]=a[l];
			return;
		}	
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(x,l,r);
	}
	void update(int x,int l,int r,int pos){
		if (l==r){
			t[x]=s[pos],mx[x]=a[pos];
			return;
		}
		if (pos<=mid) update(ls,l,mid,pos);
		else update(rs,mid+1,r,pos);
		pushup(x,l,r);
	}
}
using namespace seg;
int main(){
	freopen("5286.in","r",stdin);
	freopen("5286.out","w",stdout);
	n=read(),m=read(),p=read();
	for (int i=1;i<=n;++i){
		s[i]=s[i+n]=read();
		a[i]=s[i]-i,a[i+n]=s[i+n]-i-n;
	}
	build(1,1,(n<<1));
	printf("%d\n",ans=t[1]+n-1);
	while (m--){
		int x=read(),y=read();
		x^=ans*p,y^=ans*p;
		s[x]=s[x+n]=y;
		a[x]=s[x]-x,a[x+n]=s[x+n]-x-n;
		update(1,1,(n<<1),x);
		update(1,1,(n<<1),x+n);
		printf("%d\n",ans=t[1]+n-1);
	}
	return 0;
}
