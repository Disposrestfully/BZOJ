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
const int N=3e5+5;
struct node{
	int opt,tim,pos,id;
	inline bool operator < (const node &u)const{
		if (tim!=u.tim) return tim<u.tim;
		return opt<u.opt;		
	}
}a[N*3],b[N];
inline bool cmp(node u,node v){
	if (u.id!=v.id) return u.id<v.id;
	if (u.pos!=v.pos) return u.pos<v.pos;
	return u.tim<v.tim;
}
int n,m,q,tot,num,cnt;
int val[N<<1],las[N];
int ans[N],vis[N];
struct Set{
	priority_queue<int,vector<int>,greater<int> >q1,q2;
	inline void init(){
		q1=q2=priority_queue<int,vector<int>,greater<int> >();
	}
	inline void insert(int x){
		q1.push(x);
	}
	inline void erase(int x){
		q2.push(x);
	}
	inline int top(){
		while (!q2.empty() && q2.top()==q1.top())
			q1.pop(),q2.pop();
		return q1.empty()?1e9:q1.top();
	}
};
multiset<int>s[N],head;
namespace seg{
	#define ls (x<<1)
	#define rs (ls|1)
	#define mid ((l+r)>>1)
	Set ss[N*3];
	int mn[N*12];
	inline void pushup(int x){
		mn[x]=min(mn[ls],mn[rs]);
	}
	void build(int x,int l,int r){
		mn[x]=1e9;
		if (l==r){
			ss[l].init();
			return;
		}
		build(ls,l,mid),build(rs,mid+1,r);
	}	
	void update(int x,int l,int r,int pos,int opt,int w){
		if (l==r){
			if (opt==-1) ss[l].erase(w);
			else ss[l].insert(w);
			mn[x]=ss[l].top();
			//if (opt==-1) printf("w==%d mn==%d %d\n",w,mn[x]);
			return;
		}
		if (pos<=mid) update(ls,l,mid,pos,opt,w);
		else update(rs,mid+1,r,pos,opt,w);
		pushup(x);
	}
	int query(int x,int l,int r,int L,int R){
		if (L>R) return 1e9;
		if (L<=l && r<=R){
			//if (L==13) printf("%d %d %d %d %d\n",l,r,mn[x],mn[ls],mn[rs]);
			return mn[x];
		}
		int res=1e9;
		if (L<=mid) res=min(res,query(ls,l,mid,L,R));
		if (R>mid) res=min(res,query(rs,mid+1,r,L,R));
		return res;
	}
}
using namespace seg;
inline void ins(int x,int id){
	s[id].insert(x);
	if (!vis[id]) ++cnt;
	++vis[id];
	multiset<int>::iterator pre,nxt,it;
	pre=s[id].lower_bound(x);
	nxt=s[id].upper_bound(x);
	if (pre!=s[id].begin()){
		--pre;
		update(1,1,num,x,1,*pre);
	}
	if (nxt!=s[id].end()){
		if (nxt!=s[id].begin()) update(1,1,num,*nxt,-1,*pre);
		update(1,1,num,*nxt,1,x);
	}else{
		if (~las[id]){
			it=head.lower_bound(las[id]);
			head.erase(it);
		}
		las[id]=x;
		head.insert(las[id]);
	}
}
inline void del(int x,int id){
	multiset<int>::iterator pre,nxt,it;
	it=s[id].lower_bound(x);
	s[id].erase(it);
	--vis[id];
	if (!vis[id]) --cnt;
	pre=s[id].lower_bound(x);
	nxt=s[id].upper_bound(x);
	if (pre!=s[id].begin()){
		--pre;
		update(1,1,num,x,-1,*pre);
	}
	if (nxt!=s[id].end()){
		if (nxt!=s[id].begin()) update(1,1,num,*nxt,1,*pre);
		update(1,1,num,*nxt,-1,x);
	}else{
		it=head.lower_bound(las[id]);
		head.erase(it);
		nxt=s[id].end();
		if (nxt!=s[id].begin()){
			--nxt,las[id]=*nxt;
			if (~*nxt) head.insert(*nxt);
		}else las[id]=-1;
	}
}	
inline bool chk(int l,int r){
	//printf("%d\n",*head.begin());
	//printf("%d %d %d %d\n",l,r,query(1,1,num,r+1,num),*head.begin());
	if (*head.begin()<l) return 0;
	if (query(1,1,num,r+1,num)<l) return 0;
	return 1;
}
inline int solve(int x){
	if (cnt<m) return -1;
	int l=0,r=2e8,res=-1;
	//printf("%d %d %d\n",val[4],x,val[50]);
	while (l<=r){
		int Mid=(l+r)>>1;
		int L=lower_bound(val+1,val+num+1,x-Mid)-val;
		int R=upper_bound(val+1,val+num+1,x+Mid)-val;
		while ((R>1 && val[R]>x+Mid) || R>num) --R;
		//printf("%d %d %d\n",Mid,L,R);
		//printf("%d\n",Mid);
		if (chk(L,R)) res=Mid,r=Mid-1;
		else l=Mid+1;
	}
	return res;
}
int main(){
	//freopen("5462.in","r",stdin);
	//freopen("5462.out","w",stdout);
	n=read(),m=read(),q=read();
	for (int i=1;i<=n;++i){
		b[i].pos=read(),b[i].id=read();
		b[i].tim=read(),b[i].opt=read();
		val[++num]=b[i].pos;
	}
	sort(b+1,b+n+1,cmp);
	for (int i=1;i<=n;++i){
		if (!tot || a[tot].pos!=b[i].pos || a[tot].id!=b[i].id || a[tot].opt<b[i].tim)
			a[++tot]=b[i];
		else a[tot].opt=max(a[tot].opt,b[i].opt);
	}
	for (int i=1,tt=tot;i<=tt;++i){
		a[++tot]=a[i];
		a[tot].tim=a[i].opt;
		a[tot].opt=1,a[i].opt=-1;
	}
	for (int i=1;i<=q;++i){
		int pos=read(),tim=read();
		a[++tot]=(node){0,tim,pos,i};
		val[++num]=pos;
	}
	sort(a+1,a+tot+1),sort(val+1,val+num+1);
	/*for (int i=1;i<=tot;++i)
		printf("[%d,%d,%d,%d]\n",a[i].opt,a[i].tim,a[i].pos,a[i].id);*/
	num=unique(val+1,val+num+1)-val-1;
	/*for (int i=1;i<=num;++i)
		printf("%d ",val[i]);
	puts("");*/
	for (int i=1;i<=tot;++i)
		a[i].pos=lower_bound(val+1,val+num+1,a[i].pos)-val;
	memset(las,-1,sizeof(las));
	build(1,1,num);
	for (int i=1;i<=m;++i) s[i].insert(-1);
	for (int i=1;i<=tot;++i){
		//printf("%d %d\n",i,num);
		//printf("[%d,%d,%d,%d]\n",a[i].opt,a[i].tim,a[i].pos,a[i].id);
		if (!a[i].opt) /*printf("%d\n",a[i].id),*/ans[a[i].id]=solve(val[a[i].pos]);	
		else if (~a[i].opt) del(a[i].pos,a[i].id);
		else ins(a[i].pos,a[i].id);
	//	printf("%d\n",*head.begin());
	}
	for (int i=1;i<=q;++i){
		Print(ans[i]);
		if (i%100000==0 || i==q) io::flush();
	}
	return 0;
}
