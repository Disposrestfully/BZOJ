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
const ll inf=1e18;
int n,m;
ll b[7][7],bb[7][7];
ll w1[N],w2[N],w3[N];
struct node{
	ll s[5][5];
};
inline void floyd(int tt){
	for (int k=1;k<=tt;++k)
		for (int i=1;i<=tt;++i)
			for (int j=1;j<=tt;++j)	
				b[i][j]=b[j][i]=min(b[i][j],b[i][k]+b[k][j]);
}
namespace seg{
	#define ls (x<<1)
	#define rs (ls|1)
	#define mid (l+r>>1)
	node a[N<<2];
	inline node merge(node u,node v){
		for (int i=1;i<=6;++i){
			for (int j=1;j<=6;++j) 
				b[i][j]=inf;
			b[i][i]=0;
		}
		for (int i=1;i<=4;++i)
			for (int j=1;j<=4;++j){
				int k1=i>2?i+2:i,k2=j>2?j+2:j;
				b[k1][k2]=min(b[k1][k2],u.s[i][j]);
			}
		for (int i=1;i<=4;++i)
			for (int j=1;j<=4;++j){
				int k1=i<=2?i+4:i,k2=j<=2?j+4:j;
				b[k1][k2]=min(b[k1][k2],v.s[i][j]);
			}
		floyd(6);
		node res;
		for (int i=1;i<=4;++i)
			for (int j=1;j<=4;++j)
				res.s[i][j]=b[i][j];
		return res;
	} 
	void update(int x,int l,int r,int pos){
		if (l==r){
			for (int i=1;i<=4;++i){
				for (int j=1;j<=4;++j)
					b[i][j]=inf;
				b[i][i]=0;	
			}
			b[1][2]=b[2][1]=w2[l];
			b[3][4]=b[4][3]=w2[l+1];
			b[1][3]=b[3][1]=w1[l];
			b[2][4]=b[4][2]=w3[l];
			floyd(4);
			for (int i=1;i<=4;++i)
				for (int j=1;j<=4;++j)
					a[x].s[i][j]=b[i][j];
			return;
		}	
		if (pos<=mid) update(ls,l,mid,pos);
		else update(rs,mid+1,r,pos);
		a[x]=merge(a[ls],a[rs]);
	}
	node query(int x,int l,int r,int L,int R){
		if (L<=l && r<=R) return a[x];
		if (R<=mid) return query(ls,l,mid,L,R);
		if (L>mid) return query(rs,mid+1,r,L,R);
		node u=query(ls,l,mid,L,R),v=query(rs,mid+1,r,L,R);
		return merge(u,v);
	}
	void build(int x,int l,int r){
		if (l==r){
			for (int i=1;i<=4;++i){
				for (int j=1;j<=4;++j)
					b[i][j]=inf;
				b[i][i]=0;	
			}
			b[1][2]=b[2][1]=w2[l];
			b[3][4]=b[4][3]=w2[l+1];
			b[1][3]=b[3][1]=w1[l];
			b[2][4]=b[4][2]=w3[l];
			floyd(4);
			for (int i=1;i<=4;++i)
				for (int j=1;j<=4;++j)
					a[x].s[i][j]=b[i][j];
			return;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		a[x]=merge(a[ls],a[rs]);
	}
};
using namespace seg;
int main(){
	freopen("2459.in","r",stdin);
	freopen("2459.out","w",stdout);
	n=read();
	for (int i=1;i<n;++i) w1[i]=read();
	for (int i=1;i<=n;++i) w2[i]=read();
	for (int i=1;i<n;++i) w3[i]=read();
	build(1,1,n-1);
	m=read();
	int cas=0;
	while (m--){
		int opt=read();
		if (opt&1){
			++cas;
			int u=read(),v=read();
			int lu=(u>>1)+(u&1),lv=(v>>1)+(v&1);
			if (lu>lv) swap(lu,lv),swap(u,v);
			if (u==v){
				Print(0);
				continue;
			}
			if (lu^lv){
				//printf("%d %d\n",lu,lv);
				node p;
				for (int i=1;i<=4;++i)
					for (int j=1;j<=4;++j)
						bb[i][j]=inf;
				if (lu!=1){
					p=query(1,1,n-1,1,lu-1);
					bb[1][2]=bb[2][1]=p.s[3][4];
				}
				if (lv!=n){
					p=query(1,1,n-1,lv,n-1);
					bb[3][4]=bb[4][3]=p.s[1][2];
				}
				p=query(1,1,n-1,lu,lv-1);
				for (int i=1;i<=4;++i)
					for (int j=1;j<=4;++j)
						b[i][j]=min(bb[i][j],p.s[i][j]);
				floyd(4);
				u=u&1?1:2,v=v&1?3:4;
				Print(b[u][v]);
			}else{
				ll ans=inf;
				node p;
				if (lu!=1) p=query(1,1,n-1,1,lu-1),ans=min(ans,p.s[3][4]);
				if (lu!=n) p=query(1,1,n-1,lu,n-1),ans=min(ans,p.s[1][2]);
				Print(ans);
			}
		}else{
			int tp=read(),x=read(),w=read();
			if (tp==0) w1[x]=w,update(1,1,n-1,x);
			if (tp==2) w3[x]=w,update(1,1,n-1,x);
			if (tp==1){
				w2[x]=w;
				if (x!=1) update(1,1,n-1,x-1);
				if (x!=n) update(1,1,n-1,x);
			}
		}
	}
	io::flush();
	return 0;
}
