#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e3+5;
const int Mod=1e9+7;
int n,m,t;
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
}	
struct node{
	int a[N];
	inline void read(){
		char s[N];
		scanf("%s",s+1);
		for (int i=1;i<=m;++i) a[i]=s[i]-'0';
	}
	inline void print(){
		for (int i=1;i<=n;++i) printf("%d",a[i]);
		printf("\n");
	}
	inline bool operator < (const node &u)const{
		for (int i=1;i<=n;++i)
			if (a[i]!=u.a[i]) return a[i]<u.a[i];
		return 0;
	}
	inline int operator - (const node &u){
		int res=0,s=0;
		for (int i=1;i<=n;++i){
			ad(res,res),ad(res,a[i]);
			ad(s,s),ad(s,u.a[i]);
		}
		ad(res,Mod-s);
		return res;
	}
}p[N],q[N],all,z;
int rk[N];
inline bool cmp(int x,int y){
	return p[x]<p[y];
}
int main(){
	freopen("5285.in","r",stdin);
	freopen("5285.out","w",stdout);
	scanf("%d%d%d",&n,&m,&t);
	for (int i=1;i<=n;++i)
		q[i].read();
	for (int i=1;i<=m;++i){
		rk[i]=i;
		for (int j=1;j<=n;++j)
			p[i].a[j]=q[n-j+1].a[i];	
	}
	for (int i=1;i<=n;++i)
		all.a[i]=1,z.a[i]=0;
	sort(rk+1,rk+m+1,cmp);
	while (t--){
		node now;
		now.read();
		int ans=0;
		for (int i=1;i<m;++i)
			if (now.a[rk[i]]>now.a[rk[i+1]]){
				ans=-1;
				break;
			}
		if (ans==-1){
			printf("0\n");
			continue;
		}
		for (int i=1;i<=m;++i)
			if (now.a[rk[i]]==1){
				if (i==1) ans=p[rk[i]]-z;
				else ans=p[rk[i]]-p[rk[i-1]];
			//	p[rk[i]].print();
			//	p[rk[i-1]].print();
				break;
			}
		if (!now.a[rk[m]]) ans=all-p[rk[m]],ad(ans,1);
		printf("%d\n",ans);
	}
	return 0;
}
