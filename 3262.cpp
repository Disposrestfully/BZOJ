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
const int N=2e5+5;
int n,m,tt;
int f[N],p[N];
struct node{
	int x,y,z,id;
	inline bool operator < (const node &u)const{
		if (x==u.x) return (y==u.y)?(z<u.z):(y<u.y);
		return x<u.x;
	}
}a[N],b[N];
map<node,int>cnt;
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
		return sum(r)-sum(l-1);	
	}
}
using namespace bit;
void solve(int l,int r){
	if (l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	int nowl=l,nowr=mid+1,tot=0;
	while (nowl<=mid || nowr<=r){
		if (nowr>r) b[++tot]=a[nowl],add(a[nowl].z,cnt[a[nowl]]),++nowl;
		else if (nowl>mid) b[++tot]=a[nowr],f[a[nowr].id]+=sum(a[nowr].z),++nowr;
		else{
			if (a[nowl].y<a[nowr].y || (a[nowl].y==a[nowr].y && a[nowl].z<=a[nowr].z)) 
				b[++tot]=a[nowl],add(a[nowl].z,cnt[a[nowl]]),++nowl;
			else b[++tot]=a[nowr],f[a[nowr].id]+=sum(a[nowr].z),++nowr;
		}
	}
	for (int i=l;i<=mid;++i)
		add(a[i].z,-cnt[a[i]]);
	for (int i=1;i<=tot;++i)
		a[l+i-1]=b[i];
}
int main(){
	freopen("3262.in","r",stdin);
	freopen("3262.out","w",stdout);
	tt=read(),m=read();
	for (int i=1;i<=tt;++i){
		int x=read(),y=read(),z=read();
		if (!cnt[(node){x,y,z,0}]) a[++n]=(node){x,y,z,n};
		++cnt[(node){x,y,z,0}];
	}
	for (int i=1;i<=n;++i)
		cnt[a[i]]=cnt[(node){a[i].x,a[i].y,a[i].z,0}];
	sort(a+1,a+n+1);
	solve(1,n);
	for (int i=1;i<=n;++i){
		f[a[i].id]+=cnt[a[i]]-1;
		p[f[a[i].id]]+=cnt[a[i]];
	}
	for (int i=0;i<tt;++i) Print(p[i]);
	io::flush();
	return 0;
}
