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
const int N=2e5+5;
struct node{
	int x,w;
}q[N];
int top=0,Mod;
int n,t,len;
void find(int x){
	int l=1,r=top;
	while (l<r){
		int mid=(l+r)>>1;
		if (q[mid].x<x) l=mid+1;
		else r=mid;	
	}
	t=q[r].w;
	printf("%d\n",q[r].w);
}
int main(){
	n=read();Mod=read();
	while (n--){
		char c=0;
		while (c!='A' && c!='Q') c=getchar();
		if (c=='A'){
			int x=(read()+t)%Mod;
			while (top>0 && q[top].w<x) --top;
			q[++top].w=x;
			q[top].x=++len;
		}else{
			int x=read();
			find(len-x+1);	
		}
	}
	return 0;
}

