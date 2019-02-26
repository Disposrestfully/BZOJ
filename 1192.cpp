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
int n; 
int ans[10010];
int cmp(int x,int y){
	return x<y;	
}
int main(){
	n=read();
	int cnt=0;
	for (int i=0;1<<i<=n;++i){
		n-=1<<i;
		ans[++cnt]=1<<i;	
	}
	if (n>0 && !n&(n-1)){
		ans[++cnt]=n-1;
		ans[++cnt]=1;	
	}else if (n!=0) ans[++cnt]=n;
	sort(ans+1,ans+cnt+1,cmp);
	printf("%d\n",cnt);
/*	for (int i=2;i<=cnt;++i)
		printf(" %d",ans[i]);
	printf("\n");*/
	return 0;
}

