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
const int N=2e6+100;
char s[N],t[N];
int n,m,len,tim,tot=1,rt=1;
int ch[N][26],ed[N];
int cnt[N],fail[N];
int dfn[N],sz[N],ans[N];
queue<int>q;
vector<int>g[N];
inline void ins(int x){
	int now=rt;
	for (int i=1;i<=m;++i){
		t[++len]=s[i];
		if (!ch[now][s[i]-'a']) ch[now][s[i]-'a']=++tot;
		now=ch[now][s[i]-'a'];
	}
	t[++len]='#',ed[x]=now;
}
inline void get_fail(){
	fail[rt]=0,q.push(rt);
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (int i=0;i<26;++i)
			if (ch[x][i]){
				int now=fail[x];
				while (now && !ch[now][i]) now=fail[now];
				if (ch[now][i]) fail[ch[x][i]]=ch[now][i];
				else fail[ch[x][i]]=rt;
				q.push(ch[x][i]);
				g[fail[ch[x][i]]].push_back(ch[x][i]);
			}else ch[x][i]=ch[fail[x]][i];
	}
} 
inline void solve(){
	int now=rt;
	for (int i=1;i<=len;++i){
		if (t[i]=='#'){
			now=rt;
			continue;
		}
		now=ch[now][t[i]-'a'];
		++cnt[now];
	}
}
void dfs(int x){
	dfn[x]=++tim,sz[x]=1;
	for (int i=0,ssz=g[x].size();i<ssz;++i){
		int y=g[x][i];
		dfs(y),sz[x]+=sz[y];
	}
}
inline bool chk(int x,int y){
	return (dfn[x]<=dfn[y] && dfn[y]<=dfn[x]+sz[x]-1);
}
int main(){
	freopen("3172.in","r",stdin);
	freopen("3172.out","w",stdout);
	n=read();
	for (int i=0;i<26;++i) ch[0][i]=1;
	for (int i=1;i<=n;++i){
		scanf("%s",s+1);
		m=strlen(s+1);
		ins(i);
	}
	get_fail(),solve(),dfs(1);
	for (int i=1;i<=tot;++i)
		if (cnt[i]){
			for (int j=1;j<=n;++j)
				if (chk(ed[j],i))
					ans[j]+=cnt[i];
		}
	for (int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}
