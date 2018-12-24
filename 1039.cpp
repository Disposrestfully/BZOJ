#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
using namespace std;
typedef long long ll;
const int N=2e5+5;
namespace pb_ds{   
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0; 
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100]; 
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
struct point{
	int x,y;
	inline point operator - (const point &u){
		return (point){x-u.x,y-u.y};
	}
	inline int operator * (const point &u){
		return x*u.y-y*u.x;
	}
	inline int operator ^ (const point &u){
		return x*u.x+y*u.y;
	}
}pt[N];
int gcd(int x,int y){
	if (!y) return x;
	return gcd(y,x%y);
}
struct tnode{
	int da,db,dc,crs;
	inline bool operator < (const tnode &u)const{
		if (da!=u.da) return da<u.da;
		if (db!=u.db) return db<u.db;
		if (dc!=u.dc) return dc<u.dc;
		return crs<u.crs;
	}
};
tnode get(point a,point b,point c){
	tnode res;
	res.da=(b-a)^(b-a);
	res.db=(c-b)^(c-b);
	res.dc=(a-c)^(a-c);
	res.crs=(b-a)*(c-b);
	if (res.crs<0) res.crs=-1;
	if (res.crs>0) res.crs=1;
	int k=gcd(res.da,gcd(res.db,res.dc));
	res.da/=k;res.db/=k;res.dc/=k;
	return res;
}
int n,m;
map<tnode,int>mp[N];
vector<int>s[N];
int tot,cnt,rev[N];
int ans[N],w[N],fail[N],las[N];
queue<int>q;
vector<tnode>d;
inline void ins(){
	int now=0;
	for (int i=0;i<d.size();++i){
		if (d[i].crs) rev[cnt]=0;
		if (!mp[now][d[i]]) mp[now][d[i]]=++tot;
		now=mp[now][d[i]];
	}
	s[now].push_back(cnt);
}
inline void build(){
	for (map<tnode,int>::iterator it=mp[0].begin();it!=mp[0].end();++it)
		q.push(it->second);
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (map<tnode,int>::iterator it=mp[x].begin();it!=mp[x].end();++it){
			tnode to=it->first;
			int y=it->second,p=fail[x];
			while (p && !mp[p][to]) p=fail[p];
			if (mp[p][to]) p=mp[p][to];
			fail[y]=p;
			las[y]=s[fail[y]].empty()?las[fail[y]]:fail[y];
			q.push(y);
		}
	}
}
inline void solve(){
	int p=0;
	for (int i=0;i<d.size();++i){
		tnode x=d[i];
		while (!mp[p][x] && p) p=fail[p]; 
		if (mp[p][x]) p=mp[p][x];
		for (int j=p;j;j=las[j])
			++w[j];
	}
}
inline void init(){
	++cnt;
	int k=read();
	d.clear();
	rev[cnt]=1;
	for (int i=1;i<=k;++i)
		pt[i].x=read(),pt[i].y=read();
	if (k<3){
		ans[cnt]=n-k+1;
		return;
	}
	for (int i=1;i<=k-2;++i)
		d.push_back(get(pt[i],pt[i+1],pt[i+2]));
	ins();
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=read();m=read();
	for (int i=1;i<=m;++i)
		init();
	build();
	d.clear();
	for (int i=1;i<=n;++i)
		pt[i].x=read(),pt[i].y=read();
	if (n>=3){
		for (int i=1;i<=n-2;++i)
			d.push_back(get(pt[i],pt[i+1],pt[i+2]));
		solve();d.clear();
		for (int i=1;i<=n;++i)
			pt[i].x=-pt[i].x;
		for (int i=1;i<=n-2;++i)
			d.push_back(get(pt[i],pt[i+1],pt[i+2]));
		solve();
	}
	for (int i=1;i<=tot;++i){
		for (int j=0;j<s[i].size();++j)
			ans[s[i][j]]+=w[i]/(rev[s[i][j]]+1);
	}
	for (int i=1;i<=m;++i)
		printf("%d\n",ans[i]);	
	return 0;
}
