#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
long long read(){
	long long x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		  if (ch=='-') w=-1;
		  ch=getchar();
	}
	while (ch<='9' && ch>='0'){
		  x=(x<<1)+(x<<3)+ch-'0';
		  ch=getchar();
	}
	return x*w;
}
const long long N=5e5+10;
long long n,m,len,type;
long long ch[N][2],rk[N],p[N];
long long mn[N*3],c[N],h[N];
long long cnt,rt,ans=0;
char s[N];
void build(long long &rt,long long l,long long r){
	if (!rt) return;
	rk[rt]=l+r;
	long long mid=(l+r)>>1;
	build(ch[rt][0],l,mid);
	build(ch[rt][1],mid,r);
} 
void rotate(long long &rt,long long y,long long l,long long r){
	long long k=ch[rt][y^1];
	ch[rt][y^1]=ch[k][y];
	ch[k][y]=rt;
	rt=k;
	build(rt,l,r);
}
void init(long long &rt,long long l,long long r){
	if (!rt){
		rt=cnt;
		rk[rt]=l+r;
		return;
	}
	long long mid=(l+r)>>1;
	if (c[cnt]<c[rt] || (c[cnt]==c[rt] && rk[cnt-1]<rk[rt-1])){
		init(ch[rt][0],l,mid);
		if (h[ch[rt][0]]>h[rt])	rotate(rt,1,l,r);
	}else{
		init(ch[rt][1],mid,r);
		if (h[ch[rt][1]]>h[rt])	rotate(rt,0,l,r);
	}
}
void solve(long long rt,long long l,long long r,long long pos){
	if (l==r) return;
	long long L=rt<<1,R=L^1;
	long long mid=(l+r)>>1;
	if (pos<=mid) solve(L,l,mid,pos);
	else solve(R,mid+1,r,pos);
	mn[rt]=rk[p[mn[L]]]<=rk[p[mn[R]]]?mn[L]:mn[R];
}
void get_min(long long x,long long l,long long r){
	if (l==r){
		p[l]=read();
		mn[x]=l;
		return;
	}
	long long L=x<<1,R=L^1;
	long long mid=(l+r)>>1;
	get_min(L,l,mid);
	get_min(R,mid+1,r);
	mn[x]=rk[p[mn[L]]]<=rk[p[mn[R]]]?mn[L]:mn[R];
}
void insert(long long x){
	c[++cnt]=x;
	h[cnt]=rand()*rand();
	init(rt,1,1ll<<61);	
}
long long ask(long long rt,long long l,long long r,long long L,long long R){
	if (L<=l && R>=r) return mn[rt];
	long long mid=(l+r)>>1;
	long long l2=rt<<1,r2=l2^1;
	if (R<=mid) return ask(l2,l,mid,L,R);
	if (L>mid) return ask(r2,mid+1,r,L,R);
	long long x=ask(l2,l,mid,L,R),y=ask(r2,mid+1,r,L,R);
	return rk[p[x]]<=rk[p[y]]?x:y;
}
int main(){
	//freopen("p.in","r",stdin);
	//freopen("p.out","w",stdout);
	n=read();m=read();
	len=read();type=read();
	scanf("%s",s);
	for (long long i=0;i<len;++i)
		insert(s[len-i-1]-'a');
	/*for (int i=1;i<=n;++i)
		printf("%d ",c[i]);
	printf("\n");*/
	get_min(1,1,n);
	/*for (int i=1;i<=n;++i)
		printf("%d ",mn[i]);
	printf("\n");*/
	while (m--){
		char ch=0;
		while (ch!='I' && ch!='C' && ch!='Q')
			ch=getchar();
		if (ch=='I'){
			long long k=read(); 
			if (type) k^=ans;
			insert(k);
			len++;	
		}else if (ch=='C'){
			long long pos=read();
			p[pos]=read();
			solve(1,1,n,pos);		
		}else{
			long long l=read(),r=read();	
			ans=ask(1,1,n,l,r);
			printf("%lld\n",ans); 
		}
	}
	return 0;
}

