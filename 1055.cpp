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
int p[4]={22,8,13,6};
int q[26];
int f[210][210][4],k;
struct node{
	int l[20],r[20];
}s[4];
int a[4];
char c[210];
int solve(int l,int r,int x){
	if (f[l][r][x]!=-1) return f[l][r][x];
	if (l==r){
		if (c[l]-'A'==p[x]) f[l][r][x]=1;
		else f[l][r][x]=0;
		return f[l][r][x];
	}
	f[l][r][x]=0;
	for (int i=1;i<=a[x];++i)
		for (int j=l;j<r;++j){
			f[l][r][x]|=((solve(l,j,s[x].l[i])) & (solve(j+1,r,s[x].r[i])));
			if (f[l][r][x]) return 1;	
		}
	return f[l][r][x];
}
int main(){
	for (int i=0;i<4;++i)
		a[i]=read();
	q[22]=0;q[8]=1;q[13]=2;q[6]=3;
	for (int i=0;i<4;++i){
		for (int j=1;j<=a[i];++j){
			scanf("%s",c);
			s[i].l[j]=q[c[0]-'A'];
			s[i].r[j]=q[c[1]-'A'];
		}
	}
	scanf("%s",c);
	k=strlen(c);
	for (int i=0;i<k;++i)
		for (int j=i;j<k;++j)
			for (int t=0;t<4;++t)
				f[i][j][t]=-1;
	int flag=0;
	for (int i=0;i<4;++i)
		if (solve(0,k-1,i)){
			printf("%c",p[i]+'A');
			flag=1;	
		}
	if (!flag) printf("The name is wrong!");
	printf("\n"); 
	return 0;
}

