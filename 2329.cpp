#include<cstdio>
#include<cstring>
#include<algorithm>
#define read Read<int>
using namespace std;
const int N=1e5+50;
const int inf=0;
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
void print(int x,bool f){
	if (x>=10) print(x/10,0);
	putchar(x%10+'0');
	if (f) putchar('\n');
}
struct splay_node{
	int next[2],fa;
	int mn,mx,val,sz,sum;
	int mn_pre,mn_suf;
	int mx_pre,mx_suf;
};
struct splay_tree{
	splay_node a[N];
	int add[N],rev[N],sig[N],neg[N];
	int sta[N],val[N];
	int rt,top;
	void init(){
		memset(add,0,sizeof(add));
		memset(rev,0,sizeof(rev));
		memset(sig,0,sizeof(sig));
		memset(neg,0,sizeof(neg));
		rt=top=0;
		for (int i=N-5;i>=1;--i)
			sta[++top]=i;
		a[0].next[1]=a[0].next[0]=0;
		a[0].val=a[0].mx=a[0].mn=0;
		a[0].sz=a[0].fa=a[0].sum=0;
		a[0].mx_pre=a[0].mx_suf=0;
		a[0].mn_pre=a[0].mn_suf=0;
	}
	void build(int x,int l,int r,int fa,bool s){
		if (l>r){
			sta[++top]=x;
			a[fa].next[s]=0;
			return;
		}
		int mid=(l+r)>>1;
		new_node(x,val[mid],fa);
		a[x].next[0]=sta[top--];
		a[x].next[1]=sta[top--];
		build(a[x].next[0],l,mid-1,x,0);
		build(a[x].next[1],mid+1,r,x,1);
		pushup(x);
	}
	void ADD(int x,int k){
		if (!x) return;
		a[x].val+=k;
		a[x].mn+=k;
		a[x].mx+=k;
		a[x].sum+=a[x].sz*k;
		add[x]+=k;
	}
	void REV(int x){
		if (!x) return;
		swap(a[x].next[0],a[x].next[1]);
		rev[x]^=1;
		swap(a[x].mx_pre,a[x].mx_suf);
		swap(a[x].mn_pre,a[x].mn_suf);
	}
	void NEG(int x){
		if (!x) return;
		neg[x]^=1;
		a[x].val=-a[x].val;
		a[x].sum=-a[x].sum;
		add[x]=-add[x];
		a[x].mx_pre=-a[x].mx_pre;
		a[x].mn_pre=-a[x].mn_pre;
		a[x].mx_suf=-a[x].mx_suf;
		a[x].mn_suf=-a[x].mn_suf;
		a[x].mx=-a[x].mx;
		a[x].mn=-a[x].mn;
		swap(a[x].mx,a[x].mn);
		swap(a[x].mx_pre,a[x].mn_pre);
		swap(a[x].mx_suf,a[x].mn_suf);
		a[x].mx_pre=max(0,a[x].mx_pre);
		a[x].mx_suf=max(0,a[x].mx_suf);
	}
	void SIG(int x,int k){
		if (!x) return;
		add[x]=neg[x]=rev[x]=0;
		a[x].val=k;
		sig[x]=k;
		a[x].sum=a[x].sz*k;
		a[x].mx_suf=a[x].mx_pre=max(a[x].sum,0);
		a[x].mn_suf=a[x].mn_pre=min(a[x].sum,0);
	}
	void new_node(int x,int val,int fa){
		a[x].val=a[x].mn=a[x].mx=val;
		a[x].fa=fa;a[x].sz=1;
		add[x]=rev[x]=0;
		a[x].next[1]=a[x].next[0]=0;
	}
	void Del(int x){
		if (!x) return;
		a[x].val=a[x].mn=a[x].mx=0;
		a[x].next[1]=a[x].next[0]=0;
		a[x].fa=a[x].sz=0;
		add[x]=rev[x]=0;
		sta[++top]=x;
	}
	void pushup(int x){
		if (!x) return;
		int l=a[x].next[0],r=a[x].next[1];
		a[x].sz=a[l].sz+a[r].sz+1;
		a[x].sum=a[l].sum+a[r].sum+a[x].val;
		a[x].mx=a[x].mn=a[x].val;
		if (l){
			a[x].mx=max(a[x].mx,a[l].mx);
			a[x].mn=min(a[x].mn,a[l].mn);
		}
		if (r){
			a[x].mx=max(a[r].mx,a[x].mx);
			a[x].mn=min(a[r].mn,a[x].mn);
		}
		a[x].mx_pre=max(a[l].mx_pre,max(a[l].sum+a[x].val,a[l].sum+a[x].val+a[r].mx_pre));
		a[x].mn_pre=min(a[l].mn_pre,min(a[l].sum+a[x].val,a[l].sum+a[x].val+a[r].mn_pre));
		a[x].mx_suf=max(a[r].mx_suf,max(a[r].sum+a[x].val,a[r].sum+a[x].val+a[l].mx_suf));
		a[x].mn_suf=min(a[r].mn_suf,min(a[r].sum+a[x].val,a[r].sum+a[x].val+a[l].mn_suf));
	}
	void pushdown(int x){
		if (!x) return;
		if (sig[x]){
			SIG(a[x].next[1],sig[x]);
			SIG(a[x].next[0],sig[x]);
			sig[x]=0;
		}
		if (add[x]){
			ADD(a[x].next[1],add[x]);
			ADD(a[x].next[0],add[x]);
			add[x]=0;
		}
		if (rev[x]){
			REV(a[x].next[1]);
			REV(a[x].next[0]);
			rev[x]=0;
		}
		if (neg[x]){
			NEG(a[x].next[1]);
			NEG(a[x].next[0]);
			neg[x]=0;
		}
	}
	void rotate(int x,int k){
		int y=a[x].fa,z=a[y].fa;
		pushdown(y);pushdown(x);
		a[y].fa=x;a[x].fa=z;
		a[y].next[!k]=a[x].next[k];
		if (z) a[z].next[a[z].next[1]==y]=x;
		if (a[x].next[k]) a[a[x].next[k]].fa=y;
		a[x].next[k]=y;
		pushup(y);pushup(x);
	}
	void splay(int x,int goal){
		pushdown(x);
		while (a[x].fa!=goal){
			int y=a[x].fa,z=a[y].fa;
			pushdown(z);pushdown(y);pushdown(x);
			if (z==goal) rotate(x,a[y].next[0]==x);
			else{
				int k=y==a[z].next[0];
				if (a[y].next[k]==x){
					rotate(x,!k);
					rotate(x,k);
				}else{
					rotate(y,k);
					rotate(x,k);
				}
			}
		}
		pushup(x);
		if (goal==0) rt=x;
	}
	void multi_insert(int x){
		int p=rt;
		while ((a[p].val<=x && a[p].next[1]) || (a[p].val>x && a[p].next[0]))
			p=a[p].next[a[p].val<=x];
		int k=sta[top--];
		a[p].next[a[p].val<=x]=k;
		new_node(k,x,p);
		for (int i=p;i;i=a[i].fa)
			pushup(i);
		splay(k,0);
	}
	bool insert(int x){
		int p=rt;
		while ((a[p].val==x) || (a[p].val>x && a[p].next[0]) || (a[p].val<x && a[p].next[1])){
			if (a[p].val==x){
				splay(p,0);
				return 0;
			}
			p=a[p].next[a[p].val<x];
		}
		int k=sta[top--];
		a[p].next[a[p].val<x]=k;
		new_node(k,x,p);
		for (int i=p;i;i=a[i].fa)
			pushup(i);
		splay(k,0);
		return 1;
	}
	void Insert(int x,int k){
		int l=get_kth(rt,k),r=get_kth(rt,k+1);
		splay(l,0);splay(r,l);
		int id=sta[top--];
		new_node(id,x,r);
		a[r].next[0]=id;
		for (int i=r;i;i=a[i].fa)
			pushup(i);
		splay(r,0);
	}
	int get_rank(int x){
		int rk=1,p=rt;
		while (p){
			pushdown(p);
			if (a[p].val>=x) p=a[p].next[0];
			else{
				rk+=a[a[p].next[0]].sz+1;
				p=a[p].next[1];
			}	
		}
		return rk;
	}
	int get_kth(int x,int k){
		while (x){
			pushdown(x);
			if (a[a[x].next[0]].sz+1==k) return x;
			if (a[a[x].next[0]].sz>=k) x=a[x].next[0];
			else{
				k-=(a[a[x].next[0]].sz+1);
				x=a[x].next[1];
			}
		}
	}
	void Add(int l,int r,int k){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		ADD(a[R].next[0],k);
	}
	void Rev(int l,int r){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		REV(a[R].next[0]);
	}
	void del(int x){
		int l=get_kth(rt,x-1),r=get_kth(rt,x+1);
		splay(l,0);splay(r,l);
		Del(a[r].next[0]);
		a[r].next[0]=0;
		pushup(r);pushup(l);
	}
	void dfs(int x){
		pushdown(x);
		if (a[x].next[0]) dfs(a[x].next[0]);
	/*	if (a[x].val!=inf && a[x].val!=-inf){
			if (a[x].val==-1) putchar(')');
			else putchar('(');
		}*/
		if (a[x].next[1]) dfs(a[x].next[1]);
	}
	int get_min(int l,int r){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		return a[a[R].next[0]].mn;
	}
	int get_max(int l,int r){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		return a[a[R].next[0]].mx;
	}
	int get_pre(int x){
		int pre=-inf,p=rt;
		while (p){
			if (pre<a[p].val && a[p].val<x) pre=a[p].val;
			if (a[p].val<x) p=a[p].next[1];
			else p=a[p].next[0];
		}
		return pre;
	}
	int get_nxt(int x){
		int nxt=inf,p=rt;
		while (p){
			if (a[p].val>x && a[p].val<nxt) nxt=a[p].val;
			if (a[p].val>x) p=a[p].next[0];
			else p=a[p].next[1];
		}
		return nxt;
	}
	void assigned(int l,int r,int k){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);
		splay(R,L);
		add[a[R].next[0]]=0;
		SIG(a[R].next[0],k);
		pushup(R);
		pushup(rt);
	}
	void remove(int l1,int r1,int l2,int r2){
		int L=get_kth(rt,l1-1),R=get_kth(rt,r1+1);
		splay(L,0);splay(R,L);
		int k=a[R].next[0];
		a[R].next[0]=0;
		L=get_kth(rt,l2-1),R=get_kth(rt,r2+1);
		splay(L,0);splay(R,L);
		a[R].next[0]=k;
		a[k].fa=R;
	}
	void Neg(int l,int r){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		NEG(a[R].next[0]);
		pushup(R);pushup(L);
	}
	int get_mx_pre(int l,int r){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		return a[a[R].next[0]].mx_pre;
	}
	int get_mx_suf(int l,int r){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		return a[a[R].next[0]].mx_suf;
	}
	int get_mn_pre(int l,int r){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		return a[a[R].next[0]].mn_pre;
	}
	int get_mn_suf(int l,int r){
		if (l>r) swap(l,r);
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0);splay(R,L);
		return a[a[R].next[0]].mn_suf;
	}
}Splay;
char st[N];
int main(){
	//freopen("1.in","r",stdin);
	//freopen("splay.out","w",stdout);
	int n=read(),T=read();
	scanf("%s",st+1);
	Splay.val[1]=-inf;
	Splay.val[n+2]=inf;
	for (int i=1;i<=n;++i)
		Splay.val[i+1]=st[i]==')'?-1:1;
	Splay.init();
	Splay.top--;
	Splay.build(1,1,n+2,0,0);
	Splay.splay(1,0);
	while (T--){
		scanf("%s",st);
		int l=read()+1,r=read()+1;
		if (st[0]=='R'){
			char ch=0,k;
			while (ch!=')' && ch!='(') ch=getchar();
			k=ch==')'?-1:1;
			Splay.assigned(l,r,k);
		}
		if (st[0]=='I') Splay.Neg(l,r);
		if (st[0]=='S') Splay.Rev(l,r);
		if (st[0]=='Q'){
			int x=Splay.get_mn_pre(l,r);
			int y=Splay.get_mx_suf(l,r);
			x=max(x,-x);y=max(y,-y);
			//printf("x==%d y==%d\n",x,y);
			print(((x+1)/2)+((y+1)/2),1);
		}
	//	Splay.dfs(Splay.rt);
	//	Splay.get_mn_pre(95,288);
//		Splay.get_mx_suf(95,288);
//		printf("pre==%d suf==%d\n",Splay.get_mn_pre(95,288),Splay.get_mx_suf(95,288));
	}
	return 0;
}
