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
int f[1050][1010];
int cnt[10],n;
char s[10]; 
int main(){
	int T=read();
	while (T--){
		scanf("%s",s);
		n=read();
		memset(cnt,0,sizeof(cnt));
		memset(f,0,sizeof(f));
		int l=strlen(s),k=(1<<l)-1;
		for (int i=0;i<l;++i)
			cnt[s[i]-'0']++;
		f[0][0]=1;	
		for (int i=0;i<k;++i)
			for (int j=0;j<n;++j)
				for (int t=0;t<l;++t)
					if (!(i&(1<<t))){
						int p=j*10+s[t]-'0';
						p%=n;
						f[i+(1<<t)][p]+=f[i][j]; 
					}
		for (int i=0;i<=9;++i)
			for (int j=2;j<=cnt[i];++j)
				f[k][0]/=j;
		printf("%d\n",f[k][0]); 
	}
	return 0;
}

