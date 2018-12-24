#include<bits/stdc++.h>
#define read() Read<int>()
#define int ll
#define update seg_tree::UPDATE
#define query seg_tree::QUERY
#define build seg_tree::BUILD
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
typedef long long ll;
const int N=1e5+5;
const ll inf=1e18;
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
int n,a[N],sum,tim;
int L[N],R[N],ans[N];
int rk[N],id[N];
namespace seg_tree{
	#define ls (x<<1)
	#define rs (ls^1)
	ll MN[N<<2];
	void BUILD(int x,int l,int r){
		if (l==r){
			MN[x]=inf;
			return;
		}
		int mid=(l+r)>>1;
		BUILD(ls,l,mid);
		BUILD(rs,mid+1,r);
		MN[x]=min(MN[ls],MN[rs]);
	}
	void UPDATE(int x,int l,int r,int pos,int k){
		if (l==r){
			MN[x]=k;
			return;
		}	
		int mid=(l+r)>>1;
		if (pos<=mid) UPDATE(ls,l,mid,pos,k);
		else UPDATE(rs,mid+1,r,pos,k);
		MN[x]=min(MN[ls],MN[rs]);
	}
	ll QUERY(int x,int l,int r,int LL,int RR){
		/*++tim;
		if (tim<=50)printf("%lld %lld %lld %lld %lld %lld %lld\n",x,ls,rs,l,r,LL,RR);*/
		if (LL<=l && r<=RR){
			//++tim;
			return MN[x];
		}
		ll res=inf,s1,s2;
		int mid=(l+r)>>1;
		if (LL<=mid){
			/*cout<<"*"<<ls<<endl;
			res=min(res,QUERY(ls,l,mid,LL,RR));*/
			s1=QUERY(ls,l,mid,LL,RR);
			res=min(res,s1);
		}
		if (RR>mid){
			/*cout<<"#"<<rs<<endl;
			res=min(res,QUERY(rs,mid+1,r,LL,RR));*/
			s2=QUERY(rs,mid+1,r,LL,RR);
			res=min(res,s2);
		}
		return res;
	}
}
inline int calc(int x,int y){
	int res=sum;
	if (x>y) swap(x,y);
	if (y==x+1){
		if (x==1) res-=abs(a[3]-a[y]),res+=abs(a[3]-a[x]);
		else if (y==n) res-=abs(a[n-2]-a[x]),res+=abs(a[n-2]-a[y]);
		else res-=abs(a[x-1]-a[x])+abs(a[y+1]-a[y]),res+=abs(a[x-1]-a[y])+abs(a[y+1]-a[x]);
		//printf("%lld %lld %lld\n",x,y,res);
		return res;
	}
	if (x==1) res-=abs(a[2]-a[1]);
	else res-=abs(a[x-1]-a[x])+abs(a[x+1]-a[x]);
	if (y==n) res-=abs(a[n]-a[n-1]);
	else res-=abs(a[y-1]-a[y])+abs(a[y+1]-a[y]);
	if (x==1) res+=abs(a[2]-a[y]);
	else res+=abs(a[x-1]-a[y])+abs(a[x+1]-a[y]);
	if (y==n) res+=abs(a[x]-a[n-1]);
	else res+=abs(a[y-1]-a[x])+abs(a[y+1]-a[x]);
	//printf("%lld %lld %lld\n",x,y,res);		
	return res;
}
namespace sub1{
//ai<Lj && aj>Ri
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline bool cmp2(int x,int y){
		return L[x]<L[y];
	}
	int id1[N],id2[N],vis[N];
	inline int get_val(int x){
		return L[x]+R[x]+(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		for (int i=2;i<n;++i) id1[i]=id2[i]=i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+2,id2+n,cmp2);
		int now=2;
		vis[1]=vis[n]=1;
		for (int i=2;i<n;++i)
			 update(1,1,n,rk[id2[i]],get_val(id2[i]));
		for (int i=2;i<n;++i){
			for (;now<n && L[id2[now]]<a[id1[i]];++now)
				update(1,1,n,rk[id2[now]],inf),vis[id2[now]]=1;
			int x=id1[i],d=-L[x]-R[x]-(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			if (!vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (!vis[x]) update(1,1,n,rk[x],inf);
			if (!vis[x-1]) update(1,1,n,rk[x-1],inf);
			ans[x]=min(ans[x],sum+d+query(1,1,n,max(rk[x+1],rk[x-1]),n));
			if (!vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (!vis[x]) update(1,1,n,rk[x],get_val(x));
			if (!vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
namespace sub2{
//ai<Lj && Li<aj<Ri
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline bool cmp2(int x,int y){
		return L[x]<L[y];
	}
	int id1[N],id2[N],vis[N];
	inline int get_val(int x){
		return L[x]+R[x]-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		for (int i=2;i<n;++i) id1[i]=id2[i]=i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+2,id2+n,cmp2);
		int now=2;
		vis[1]=vis[n]=1;
		for (int i=2;i<n;++i)
			 update(1,1,n,rk[id2[i]],get_val(id2[i]));
		for (int i=2;i<n;++i){
			for (;now<n && L[id2[now]]<a[id1[i]];++now)
				update(1,1,n,rk[id2[now]],inf),vis[id2[now]]=1;
			int x=id1[i],d=R[x]-L[x]-(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			if (!vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (!vis[x-1]) update(1,1,n,rk[x-1],inf);
			if (!vis[x]) update(1,1,n,rk[x],inf);
			ans[x]=min(ans[x],sum+d+query(1,1,n,min(rk[x+1],rk[x-1]),max(rk[x+1],rk[x-1])));
			if (!vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (!vis[x]) update(1,1,n,rk[x],get_val(x));
			if (!vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
namespace sub3{
//ai>Rj && Li<aj<Ri
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline bool cmp2(int x,int y){
		return R[x]<R[y];
	}
	int id1[N],id2[N],vis[N];
	inline int get_val(int x){
		return -L[x]-R[x]-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		for (int i=2;i<n;++i) id1[i]=id2[i]=i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+2,id2+n,cmp2);
		int now=2;
		for (int i=2;i<n;++i){
			for (;now<n && R[id2[now]]<=a[id1[i]];++now)
				update(1,1,n,rk[id2[now]],get_val(id2[now])),vis[id2[now]]=1;
			int x=id1[i],d=R[x]-L[x]+(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			if (vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (vis[x]) update(1,1,n,rk[x],inf);
			if (vis[x-1]) update(1,1,n,rk[x-1],inf);
			ans[x]=min(ans[x],sum+d+query(1,1,n,min(rk[x+1],rk[x-1]),max(rk[x+1],rk[x-1])));
			if (vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (vis[x]) update(1,1,n,rk[x],get_val(x));
			if (vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
namespace sub4{
//ai>Rj && aj<Li
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline bool cmp2(int x,int y){
		return R[x]<R[y];
	}
	int id1[N],id2[N],vis[N];
	inline int get_val(int x){
		//printf("%lld %lld\n",x,-R[x]-L[x]-(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]));
		return -R[x]-L[x]-(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		for (int i=2;i<n;++i) id1[i]=id2[i]=i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+2,id2+n,cmp2);
		/*for (int i=2;i<n;++i)
			printf("%lld ",id2[i]);
		printf("\n");*/
		int now=2;
		for (int i=2;i<n;++i){
			for (;now<n && R[id2[now]]<=a[id1[i]];++now)
				update(1,1,n,rk[id2[now]],get_val(id2[now])),vis[id2[now]]=1;
			int x=id1[i],d=L[x]+R[x]+(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			if (vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (vis[x]) update(1,1,n,rk[x],inf);
			if (vis[x-1]) update(1,1,n,rk[x-1],inf);
			ans[x]=min(ans[x],sum+d+query(1,1,n,1,min(rk[x+1],rk[x-1])));
			if (vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (vis[x]) update(1,1,n,rk[x],get_val(x));
			if (vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
namespace sub5{
//Lj<ai<Rj && aj<Li
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline int get_pos(int x){
		return x>0?L[x]:R[-x];
	}
	inline bool cmp2(int x,int y){
		if (abs(x)==abs(y)) return x>y;
		int u=x>0?L[x]:R[-x];
		int v=y>0?L[y]:R[-y];
		return u<v;
	}
	int id1[N],id2[N<<1],vis[N],tt;
	inline int get_val(int x){
		return R[x]-L[x]-(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		tt=0;
		for (int i=2;i<n;++i) id1[i]=i;
		for (int i=2;i<n;++i) id2[++tt]=i;
		for (int i=2;i<n;++i) id2[++tt]=-i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+1,id2+tt+1,cmp2);
		int now=1;
		for (int i=2;i<n;++i){
			int x=id1[i],d=L[x]+R[x]-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			for (;now<=tt && get_pos(id2[now])<=a[id1[i]];++now){
				int y=id2[now];
				if (y>0){
					if (vis[y]){
						vis[y]=0;
						continue;
					}
					update(1,1,n,rk[y],get_val(y));
					vis[y]=1;
				}else{
					y=-y;
					/*if (get_pos(y)==get_pos(-y)){
						ans[x]=min(ans[x],sum+d+get_val(y));
					}*/
					update(1,1,n,rk[y],inf);
					--vis[y];
				}
			}
			if (vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (vis[x]) update(1,1,n,rk[x],inf);
			if (vis[x-1]) update(1,1,n,rk[x-1],inf);
			ans[x]=min(ans[x],sum+d+query(1,1,n,1,min(rk[x+1],rk[x-1])));
			if (vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (vis[x]) update(1,1,n,rk[x],get_val(x));
			if (vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
namespace sub6{
//Lj<ai<Rj && aj>Ri
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline int get_pos(int x){
		return x>0?L[x]:R[-x];
	}
	inline bool cmp2(int x,int y){
		if (abs(x)==abs(y)) return x>y;
		return get_pos(x)<get_pos(y);
	}
	int id1[N],id2[N<<1],vis[N],tt;
	inline int get_val(int x){
		return R[x]-L[x]+(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		tt=0;
		for (int i=2;i<n;++i) id1[i]=i;
		for (int i=2;i<n;++i) id2[++tt]=i;
		for (int i=2;i<n;++i) id2[++tt]=-i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+1,id2+tt+1,cmp2);
		int now=1;
		for (int i=2;i<n;++i){
			int x=id1[i],d=-L[x]-R[x]-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			for (;now<=tt && get_pos(id2[now])<=a[id1[i]];++now){
				int y=id2[now];
				if (y>0){
					if (vis[y]){
						vis[y]=0;
						continue;
					}
					update(1,1,n,rk[y],get_val(y));
					vis[y]=1;
				}else{
					y=-y;
					update(1,1,n,rk[y],inf);
					--vis[y];
				}
			}
			if (vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (vis[x]) update(1,1,n,rk[x],inf);
			if (vis[x-1]) update(1,1,n,rk[x-1],inf);
			ans[x]=min(ans[x],sum+d+query(1,1,n,max(rk[x+1],rk[x-1]),n));
			if (vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (vis[x]) update(1,1,n,rk[x],get_val(x));
			if (vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
namespace sub7{
//ai<Lj && aj<Li
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline bool cmp2(int x,int y){
		return L[x]<L[y];
	}
	int id1[N],id2[N],vis[N];
	inline int get_val(int x){
		return L[x]+R[x]-(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		for (int i=2;i<n;++i) id1[i]=id2[i]=i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+2,id2+n,cmp2);
		int now=2;
		vis[1]=vis[n]=1;
		for (int i=2;i<n;++i)
			 update(1,1,n,rk[id2[i]],get_val(id2[i]));
		for (int i=2;i<n;++i){
			for (;now<n && L[id2[now]]<a[id1[i]];++now)
				update(1,1,n,rk[id2[now]],inf),vis[id2[now]]=1;
			int x=id1[i],d=L[x]+R[x]-(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			if (!vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (!vis[x]) update(1,1,n,rk[x],inf);
			if (!vis[x-1]) update(1,1,n,rk[x-1],inf);
			ans[x]=min(ans[x],sum+d+query(1,1,n,1,min(rk[x+1],rk[x-1])));
			if (!vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (!vis[x]) update(1,1,n,rk[x],get_val(x));
			if (!vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
namespace sub8{
//ai>Rj && aj>Ri
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline bool cmp2(int x,int y){
		return R[x]<R[y];
	}
	int id1[N],id2[N],vis[N];
	inline int get_val(int x){
		return -L[x]-R[x]+(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		for (int i=2;i<n;++i) id1[i]=id2[i]=i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+2,id2+n,cmp2);
		int now=2;
		for (int i=2;i<n;++i){
			for (;now<n && R[id2[now]]<=a[id1[i]];++now)
				update(1,1,n,rk[id2[now]],get_val(id2[now])),vis[id2[now]]=1;
			int x=id1[i],d=-R[x]-L[x]+(a[x]<<1)-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			if (vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (vis[x]) update(1,1,n,rk[x],inf);
			if (vis[x-1]) update(1,1,n,rk[x-1],inf);
			ans[x]=min(ans[x],sum+d+query(1,1,n,max(rk[x+1],rk[x-1]),n));
			if (vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (vis[x]) update(1,1,n,rk[x],get_val(x));
			if (vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
namespace sub9{
//Lj<ai<Rj && Li<aj<Ri
	inline bool cmp1(int x,int y){
		return a[x]<a[y];
	}
	inline int get_pos(int x){
		return x>0?L[x]:R[-x];
	}
	inline bool cmp2(int x,int y){
		if (abs(x)==abs(y)) return x>y;
		int u=x>0?L[x]:R[-x];
		int v=y>0?L[y]:R[-y];
		return u<v;
	}
	int id1[N],id2[N<<1],vis[N],tt;
	inline int get_val(int x){
		return R[x]-L[x]-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
	}
	inline void solve(){
		build(1,1,n);
		memset(vis,0,sizeof(vis));
		tt=0;
		for (int i=2;i<n;++i) id1[i]=i;
		for (int i=2;i<n;++i) id2[++tt]=i;
		for (int i=2;i<n;++i) id2[++tt]=-i;
		sort(id1+2,id1+n,cmp1);
		sort(id2+1,id2+tt+1,cmp2);
		int now=1;
		for (int i=2;i<n;++i){
			int x=id1[i],d=-L[x]+R[x]-abs(a[x]-a[x-1])-abs(a[x]-a[x+1]);
			for (;now<=tt && get_pos(id2[now])<=a[id1[i]];++now){
				int y=id2[now];
				if (y>0){
					if (vis[y]){
						vis[y]=0;
						continue;
					}
					update(1,1,n,rk[y],get_val(y));
					vis[y]=1;
				}else{
					y=-y;
					/*if (get_pos(y)==get_pos(-y)){
						ans[x]=min(ans[x],sum+d+get_val(y));
					}*/
					update(1,1,n,rk[y],inf);
					--vis[y];
				}
			}
			if (vis[x+1]) update(1,1,n,rk[x+1],inf);
			if (vis[x]) update(1,1,n,rk[x],inf);
			if (vis[x-1]) update(1,1,n,rk[x-1],inf);
			//printf("%lld %lld\n",x,query(1,1,n,1,min(rk[x+1],rk[x-1])));
			ans[x]=min(ans[x],sum+d+query(1,1,n,min(rk[x+1],rk[x-1]),max(rk[x+1],rk[x-1])));
			if (vis[x+1]) update(1,1,n,rk[x+1],get_val(x+1));
			if (vis[x]) update(1,1,n,rk[x],get_val(x));
			if (vis[x-1]) update(1,1,n,rk[x-1],get_val(x-1));
		}
	}
}
inline bool cmp(int x,int y){
	return a[x]<a[y];
}
signed main(){
	freopen("1099.in","r",stdin);
	freopen("1099.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i){
		a[i]=read();id[i]=i;
		if (i!=1) sum+=abs(a[i]-a[i-1]);
	}
	for (int i=1;i<=n;++i) ans[i]=sum;
	if (n==2){
		printf("%lld\n%lld\n",sum,sum);
		return 0;
	}
	sort(id+1,id+n+1,cmp);
	for (int i=1;i<=n;++i) rk[id[i]]=i;
	for (int i=2;i<=n;++i) ans[i]=min(ans[i],calc(1,i)),ans[1]=min(ans[1],calc(1,i));
	for (int i=1;i<n;++i) ans[i]=min(ans[i],calc(i,n)),ans[n]=min(ans[n],calc(i,n));
	for (int i=1;i<n;++i) ans[i]=min(ans[i],calc(i,i+1)),ans[i+1]=min(ans[i+1],calc(i,i+1));
	for (int i=2;i<n;++i)
		L[i]=min(a[i+1],a[i-1]),R[i]=max(a[i+1],a[i-1]);
	sub1::solve();
	sub2::solve();
	sub3::solve();
	sub4::solve();
	sub5::solve();
	sub6::solve();
	sub7::solve();
	sub8::solve();
	sub9::solve();
	//printf("%lld %lld %lld %lld %lld %lld\n",L[930],a[3],R[930],L[3],a[930],R[3]);
	for (int i=1;i<=n;++i)
		Print(ans[i]);
	io::flush();
	return 0;
}
