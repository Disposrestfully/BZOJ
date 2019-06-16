#include<bits/stdc++.h>
inline int read(){
	int x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		ch=getchar();
		if (ch=='-') w=-1;	
	}
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*w;
}
using namespace std;
typedef long long ll;
const int N=1e6+5;
const int Mod=1e9+7;
char s[N];
int n,ans,T;
int fail[N][21],dep[N];
inline void KMP(){
	fail[0][0]=1,fail[1][0]=0,dep[1]=1;
	for (int i=2;i<=n;++i){
		int las=fail[i-1][0];
		while (las && s[las+1]!=s[i]) las=fail[las][0];
		if (s[las+1]==s[i]) fail[i][0]=las+1;
		else fail[i][0]=0;
		dep[i]=dep[fail[i][0]]+1;
		for (int j=1;j<=20;++j)
			fail[i][j]=fail[fail[i][j-1]][j-1];
	}
}
int main(){
	freopen("3670.in","r",stdin);
	freopen("3670.out","w",stdout);
	T=read();
	while (T--){
		scanf("%s",s+1);
		n=strlen(s+1);
		KMP(),ans=1;
		for (int i=1;i<=n;++i){
			int now=i;
			for (int j=20;~j;--j)
				if ((fail[now][j]<<1)>i)
					now=fail[now][j];
			now=fail[now][0];
			ans=1ll*ans*(dep[now]+1)%Mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
