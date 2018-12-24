#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<complex>
using namespace std;
const int N=1e5+5;
const int S=1e8;
const int Bit=8;
const double Pi=acos(-1);
typedef complex<double> cd;
typedef long long LL;
void qprint(LL x,LL cnt){
	if (cnt<Bit) qprint(x/10,cnt+1);
	putchar(x%10+'0');
}
char s[N];
struct huge_num{	
	LL a[N],l;
	bool f;
	void print(){
		if (l==1 && a[0]==0){
			printf("0\n");
			return;
		}
		if (f) putchar('-');
		printf("%lld",a[l-1]);
		for (int i=l-2;i>=0;--i)
			qprint(a[i],1);
		putchar('\n');
	}
	void read(){
		memset(a,0,sizeof(a));
		scanf("%s",s);
		int k=strlen(s);
		f=(s[0]=='-');
		l=0;
		for (int i=f;i<k;++i)
			if (i<k-i-(f^1)) swap(s[i],s[k-i-(f^1)]);
		for (int i=f;i<k;i+=Bit){
			for (int j=min(i+Bit-1,k-1);j>=i;--j)
				a[l]=(a[l]<<1)+(a[l]<<3)+s[j]-'0';
			++l;
		}
		while (l>1 && !a[l-1]) --l;
	}
	void val(LL x){
		memset(a,0,sizeof(a));
		f=(x<0);l=0;
		x=max(x,-x);
		LL now=1;
		while (x){
			if (now<S){
				a[l]+=now*(x%10);
				now*=10;
			}else{
				a[++l]=x%10;
				now=10;
			}
			x/=10;
		}
		++l;
	}
	void Div(LL x){
		LL now=0;
		f^=(x<0);
		x=max(x,-x);
		for (int i=l-1;i>=0;--i){
			LL k=a[i];
			a[i]=(now*S+a[i])/x;
			now=(now*S+k)%x;
		}
		while (l>1 && !a[l-1]) --l;
	}
	LL Mod(LL x){
		LL now=0;
		for (int i=l-1;i>=0;--i)
			now=(now*S+a[i])%x;
		return f?x-now:now;
	}
}f[20];
struct huge_int{
	LL cmp(huge_num x,huge_num y){
		if (x.f!=y.f) return x.f==1?-1:1;
		if (x.l!=y.l) return x.l<y.l?-1:1;
		if (x.f){
			x.f=y.f=0;
			return cmp(y,x);
		}
		for (int i=x.l-1;i>=0;--i)
			if (x.a[i]!=y.a[i])
				return x.a[i]<y.a[i]?-1:1;
		return 0;
	}
	huge_num sub(huge_num x,huge_num y){
		if (x.f!=y.f){
			y.f=x.f;
			return add(x,y);
		}
		huge_num res;
		res.f=0;
		if (cmp(x,y)==-1){
			swap(x,y);
			res.f=1;
		}
		res.l=max(x.l,y.l);
		for (int i=0;i<res.l;++i)
			res.a[i]=x.a[i]-y.a[i];
		for (int i=0;i<res.l-1;++i)
			if (res.a[i]<0){
				res.a[i]+=S;
				--res.a[i+1];
			}
		while (res.l>1 && !res.a[res.l-1]) --res.l;
		return res;
	}
	huge_num add(huge_num x,huge_num y){
		if (x.f!=y.f){
			if (y.f==1){
				y.f=0;
				return sub(x,y);
			}else{
				x.f=0;
				return sub(y,x);
			}
		}
		x.l=max(x.l,y.l);
		for (int i=0;i<x.l;++i)
			x.a[i]+=y.a[i];
		for (int i=0;i<x.l-1;++i){
			x.a[i+1]+=x.a[i]/S;
			x.a[i]%=S;
		}
		while (x.a[x.l-1]>S){
			x.a[x.l]+=x.a[x.l-1]/S;
			x.a[x.l-1]%=S;
			++x.l;
		}
		return x;
	}
	huge_num mul(huge_num x,huge_num y){
		huge_num res;
		res.val(0);
		res.f=x.f^y.f;
		res.l=x.l+y.l;
		for (int i=0;i<x.l;++i)
			for (int j=0;j<y.l;++j){
				res.a[i+j]+=x.a[i]*y.a[j];
				int k=i+j;
				while (res.a[k]>S){
					res.a[k+1]+=res.a[k]/S;
					res.a[k]%=S;
					++k;
				}
			}
		while (res.l>1 && !res.a[res.l-1]) --res.l;
		return res;
	}
	huge_num Pow(huge_num x,int y){
		huge_num res;
		res.val(1);
		while (y){
			if (y&1) res=mul(res,x);
			x=mul(x,x);
			y>>=1;
		}
		return res;
	}
}H;
int n,d;
int main(){
	f[0].val(1);
	scanf("%d%d",&n,&d);
	if (d==0){
		printf("1\n");
		return 0;
	}
	for (int i=1;i<=d;++i){
		f[i]=H.Pow(f[i-1],n);
		f[i]=H.add(f[i],f[0]);
	}
	huge_num ans=H.sub(f[d],f[d-1]);
	ans.print();
	return 0;
}
