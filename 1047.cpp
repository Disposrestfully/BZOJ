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
int n,m,k,tot=0,cnt=0;
struct node{
	int x,w;
}mx[10010],mn[10010];
int a[1010][1010];
struct fk{
	int mn,mx;
}s[1010][1010];
fk ans[1010][1010];
void addmx(int x,int w){
	mx[++tot].x=x;
	mx[tot].w=w;
	int p=tot,q=tot/2;
	while (mx[p].w>mx[q].w && q>=1){
		node temp=mx[p];
		mx[p]=mx[q];mx[q]=temp;
		p=q;q=p/2;
	}
}
void addmn(int x,int w){
	mn[++cnt].x=x;
	mn[cnt].w=w;
	int p=cnt,q=cnt/2;
	while (mn[p].w<mn[q].w && q>=1){
		node temp=mn[p];
		mn[p]=mn[q];mn[q]=temp;
		p=q;q=p/2;
	}
}
void delmx(){
	mx[1]=mx[tot];
	tot--;
	int p=1,q=2;
	while ((mx[p].w<mx[q].w && q<=tot) || (mx[p].w<mx[q+1].w && q+1<=tot)){
		if (mx[q].w<mx[q+1].w && q+1<=tot) q++;
		node temp=mx[p];
		mx[p]=mx[q];mx[q]=temp;
		p=q;q*=2;
	}
}
void delmn(){
	mn[1]=mn[cnt];
	cnt--;
	int p=1,q=2;
	while ((mn[p].w>mn[q].w && q<=cnt) || (mn[p].w>mn[q+1].w && q+1<=cnt)){
		if (mn[q].w>mn[q+1].w && q+1<=cnt) q++;
		node temp=mn[p];
		mn[p]=mn[q];mn[q]=temp;
		p=q;q*=2;
	}
}
int getmx(int l,int r){
	while (1){
		if (mx[1].x<=r && mx[1].x>=l)
			return mx[1].w;
		delmx();	
	}
}
int getmn(int l,int r){
	while (1){
		if (mn[1].x<=r && mn[1].x>=l)
			return mn[1].w;
		delmn();	
	}
}
int main(){
	//freopen("squa.in","r",stdin);
	n=read();m=read();k=read();
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			a[i][j]=read();
	for (int i=1;i<=n;++i){
		cnt=tot=0;
		for (int j=1;j<=m;++j){
			addmx(j,a[i][j]);
			addmn(j,a[i][j]);
			if (j>=k){
				s[i][j].mn=getmn(j-k+1,j);
				s[i][j].mx=getmx(j-k+1,j);
			}
		}
	}
	//printf("\n");
	for (int j=k;j<=m;++j){
		cnt=tot=0;
		for (int i=1;i<=n;++i){
			//printf("%d %d %d %d\n",i,j,s[i][j].mn,s[i][j].mx);
			addmx(i,s[i][j].mx);
			addmn(i,s[i][j].mn);
			if (i>=k){
				ans[i][j].mn=getmn(i-k+1,i);
				ans[i][j].mx=getmx(i-k+1,i);	
			}
		}
	}
	int Ans=2e9;
	for (int i=k;i<=n;++i)
		for (int j=k;j<=m;++j){
			Ans=Ans<(ans[i][j].mx-ans[i][j].mn)?Ans:(ans[i][j].mx-ans[i][j].mn);
			//printf("%d %d %d %d\n",i,j,ans[i][j].mn,ans[i][j].mx);	
		}
	printf("%d\n",Ans);
	return 0;
}

