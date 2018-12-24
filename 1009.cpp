#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int read(){
	int x=0,w=1;
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
struct node{
	int a[30][30];
}x;
int n,m,k;
node mult(node x,node y){
	node res;
	for (int i=0;i<m;++i)
		for (int j=0;j<m;++j)
			res.a[i][j]=0;
	for (int i=0;i<m;++i)
		for (int j=0;j<m;++j)	
			for (int t=0;t<m;++t)
				res.a[i][j]=(res.a[i][j]+x.a[i][t]*y.a[t][j])%k;
	return res;			
}
node Pow(node x,int y){
	node res;
	for (int i=0;i<m;++i)
		for (int j=0;j<m;++j)
			res.a[i][j]=0;
	for (int i=0;i<m;++i)
		res.a[i][i]=1;	
	while (y){
		if (y&1) res=mult(res,x);
		x=mult(x,x);
		y>>=1;	
	}
	return res;
}
char s[30];
int next[30];
int main(){
	n=read();m=read();k=read();
	scanf("%s",s+1);
	int p=0;
	for (int i=2;i<=m;++i){
		while (p>0 && s[p+1]!=s[i]) p=next[p];
		if (s[p+1]==s[i]) ++p;
		next[i]=p;	
	}
	for (int i=0;i<m;++i)
		for (int j=0;j<=9;++j){
			int temp=i;
			while (temp>0 && s[temp+1]-'0'!=j) temp=next[temp];	
			if (s[temp+1]-'0'==j) ++temp;
			if (temp!=m) x.a[temp][i]=(x.a[temp][i]+1)%k;
		}
	node y=Pow(x,n);
	int ans=0;
	for (int i=0;i<m;++i)
		ans=(ans+y.a[i][0])%k;
	printf("%d\n",ans); 
	return 0;
}

