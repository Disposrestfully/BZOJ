#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int B=330;
inline int read(){
	int x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		ch=getchar();
		if (ch=='-') w=-1;	
	}
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*w;
}
map<int,int>mp;
int p[N],cnt[N];
int Mod,n,tot,m,L,R;
char s[N];
struct node{
	int l,r,id;
	inline bool operator < (const node &u)const{
		if ((l/B+1)==(u.l/B+1)) return r<u.r;
		return l<u.l;
	}
}a[N];
ll now,ans[N];
inline void add(int x,int k){
	if (k==-1) now-=(cnt[x]-1);
	else now+=cnt[x];
	cnt[x]+=k;
}
int main(){
	freopen("4542.in","r",stdin);
	freopen("4542.out","w",stdout);
	Mod=read();
	scanf("%s",s+1);
	n=strlen(s+1);
	m=read();
	if (Mod==2 || Mod==5){
		for (int i=1;i<=n;++i)
			if ((s[i]-'0')%Mod==0){
				p[i]=1,ans[i]=i+1;
			}
		for (int i=1;i<=n;++i)
			p[i]+=p[i-1],ans[i]+=ans[i-1];
		while (m--){
			L=read(),R=read();
			ll res=ans[R]-ans[L-1]-(1ll*(p[R]-p[L-1])*L);
			printf("%lld\n",res);
		}
		return 0;
	}
	for (int i=1;i<=m;++i){
		a[i].l=read(),a[i].r=read()+1;
		a[i].id=i;
	}
	sort(a+1,a+m+1);
	int pw=1;
	for (int i=n;i;--i){
		p[i]=(p[i+1]+((1ll*(s[i]-'0')*pw)%Mod))%Mod;
		if (!mp[p[i]]) mp[p[i]]=++tot;
		pw=10ll*pw%Mod;
	}
	for (int i=1;i<=n+1;++i) p[i]=mp[p[i]];
	//printf("\n");
	L=a[1].l,R=a[1].r;
	for (int i=a[1].l;i<=a[1].r;++i) add(p[i],1);
	ans[a[1].id]=now;
	for (int i=2;i<=m;++i){
		for (;L<a[i].l;++L) add(p[L],-1);
		for (;L>a[i].l;--L) add(p[L-1],1);
		for (;R<a[i].r;++R) add(p[R+1],1);
		for (;R>a[i].r;--R) add(p[R],-1);
		ans[a[i].id]=now;
	}
	for (int i=1;i<=m;++i) 
		printf("%lld\n",ans[i]);
	return 0;
}
