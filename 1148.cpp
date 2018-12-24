#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const long long N=2e5+5;
long long read(){
	long long x=0;
	char ch=0;
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x;
}
struct node{
	long long c,w;
}a[N],s[N];
long long top=0;
bool cmp(node u,node v){
	return u.c+u.w<v.c+v.w;
}
void insert(node x){
	s[++top]=x;
	long long p=top,q=top>>1;
	while (q>0 && s[p].w>s[q].w){
		swap(s[p],s[q]);
		p>>=1;q>>=1;
	}
}
long long del(){
	long long x=s[1].w;
	s[1]=s[top--];
	long long p=1,q=2;
	while ((q<=top && s[p].w<s[q].w) || (q+1<=top && s[p].w<s[q+1].w)){
		if (q+1<=top && s[q+1].w>s[q].w) ++q;
		swap(s[p],s[q]);
		p=q;q<<=1;
	}
	return x;
}
long long n,mn,tot;
int main(){
	n=read();
	for (long long i=1;i<=n;++i){
		a[i].c=read();
		a[i].w=read();
	}
	tot=0;top=0;
	sort(a+1,a+n+1,cmp);
	for (long long i=1;i<=n;++i){
		insert(a[i]);
		tot+=a[i].w;
		if (tot-a[i].w>a[i].c) tot-=del();
	}
	printf("%lld\n%lld\n",top,tot);
	return 0;
}
