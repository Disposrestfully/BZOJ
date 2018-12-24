#pragma GCC optimize (2)
#pragma G++ optimize (2)
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#define read() Re.Read()
#define lowbit(i) i&(-i)
#define Getchar() Re.Get_Char()
using namespace std;
typedef long long ll;
const int N=3e5+5;
const int inf=2e9;
struct Readint{
	char buffer[1<<15],*S,*T; 
	inline char Get_Char(){  
    	if(S==T){  
     	   T=(S=buffer)+fread(buffer,1,1<<15,stdin);
      	  if(S==T) return EOF;  
    	}  
    	return *S++;  
	}
	int Read(){
	    char c;  
	    int re=0;  
	    for (c=Get_Char();c<'0'||c>'9';c=Get_Char()){
    		if (c==EOF) return -1;
    	}	
 	   	while(c>='0'&&c<='9')  
           	re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();  
    	return re;  
	}
}Re;
namespace print{
    static const int BUF=50000000;
    char buf[BUF],*h=buf;
    inline void put(char ch){
        h==buf+BUF?(fwrite(buf,1,BUF,stdout),h=buf):0;
        *h++=ch;
    }
    inline void putint(int num){
        static char _buf[30];
        sprintf(_buf,"%d",num);
        for (char *s=_buf;*s;s++)put(*s);
    }
    inline void finish(){
        fwrite(buf,1,h-buf,stdout);
    }
};
vector<char>name;
map<vector<char>,int>mp;
map<int,int>cnt;
int tot;
bool operator > (const pair<int,int> &u,const pair<int,int> &v){
	if (u.first!=v.first) return u.first<v.first;
	return u.second>v.second;
}
bool operator < (const pair<int,int> &u,const pair<int,int> &v){
	if (u.first!=v.first) return u.first>v.first;
	return u.second<v.second;
}
struct splay_node{
	pair<int,int>val;
	int fa,sz;
	int next[2];
	vector<char>s;
};
struct splay_tree{
	splay_node a[N];
	int sta[N],top,rt;
	void new_node(int x,int fa,pair<int,int>val){
		a[x].next[0]=a[x].next[1]=0;
		a[x].fa=fa;a[x].val=val;a[x].sz=1;
	}
	void init(){
		top=rt=0;
		for (int i=N-1;i>=1;--i)
			sta[++top]=i;
		new_node(0,0,make_pair(0,0));
		a[0].sz=0;
	}
	void pushup(int x){
		if (!x) return;
		a[x].sz=1;
		if (a[x].next[1]) a[x].sz+=a[a[x].next[1]].sz;
		if (a[x].next[0]) a[x].sz+=a[a[x].next[0]].sz;
	}
	void rotate(int x,int k){
		int y=a[x].fa,z=a[y].fa;
		a[y].fa=x;a[x].fa=z;
		a[y].next[!k]=a[x].next[k];
		if (z) a[z].next[a[z].next[1]==y]=x;
		if (a[x].next[k]) a[a[x].next[k]].fa=y;
		a[x].next[k]=y;
		pushup(y);pushup(x);
	}
	void splay(int x,int goal){
		while (a[x].fa!=goal){
			int y=a[x].fa,z=a[y].fa;
			if (z==goal) rotate(x,a[y].next[0]==x);
			else{
				int k=y==a[z].next[0];
				if (a[y].next[k]==x){
					rotate(x,!k);
					rotate(x,k);
				}else{
					rotate(y,k);
					rotate(x,k);
				}
			}
		}
		pushup(x);
		if (goal==0) rt=x;
	}
	void insert(pair<int,int> val){
		int p=rt;
		while (a[p].next[a[p].val<val]){
			//printf("%d %d %d %d %d\n",val.first,val.second,a[p].val.first,a[p].val.second,a[p].val<val);
			p=a[p].next[a[p].val<val];	
		}
		int x=sta[top--];
		a[p].next[a[p].val<val]=x;
		new_node(x,p,val);
		a[x].s.assign(name.begin(),name.end());
		for (int i=p;i;i=a[i].fa) pushup(i);
		splay(x,0);
		mp[a[x].s]=x;
		/*for (int i=0;i<name.size();++i)
			putchar(name[i]);
		printf(" %d\n",x);*/
		//printf("%d %d %d %d\n",p,x,val.first,val.second);
	}
	inline int get_kth(int x,int k){
		while (x){
			if (a[a[x].next[0]].sz+1==k){
				splay(x,0);
				return x;
			}
			if (a[a[x].next[0]].sz+1<k){
				k-=a[a[x].next[0]].sz+1;
				x=a[x].next[1];
			}else x=a[x].next[0];
		}
		return x;
	}
	void Del(int x){
		if (!x) return;
		a[x].val=make_pair(0,0);
		a[x].sz=0;
		a[x].fa=a[x].next[1]=a[x].next[0]=0;
		sta[++top]=x;
	}
	void del(int x){
		x=get_rank(a[x].val);
		int l=get_kth(rt,x-1),r=get_kth(rt,x+1);
		splay(l,0);splay(r,l);
		Del(a[r].next[0]);
		a[r].next[0]=0;
		pushup(r);pushup(l);
	}	
	int get_rank(pair<int,int> x){
		int rk=1,p=rt;
		while (p){
			if (a[p].val>x || a[p].val==x) p=a[p].next[0];
			else{
				rk+=a[a[p].next[0]].sz+1;
				p=a[p].next[1];
			}	
		}
		return rk;
	}
	void dfs(int x){
		if (a[x].next[0]) dfs(a[x].next[0]);
		if (a[x].val.first>-inf && a[x].val.first<inf){
			printf("%d %d\n",a[x].val.first,a[x].val.second);
			for (int i=0;i<a[x].s.size();++i)
				putchar(a[x].s[i]);
			printf(" %d\n",x);	
		}
		if (a[x].next[1]) dfs(a[x].next[1]);
	}
}S;
int main(){
//	freopen("1.in","r",stdin);
//	freopen("1s.out","w",stdout);
	int T=read();
	S.init();
	S.insert(make_pair(-inf,inf));
	S.insert(make_pair(inf,-inf));
	//printf("Go\n");
	while (T--){
		//printf("%d\n",T);
		char ch=0;
		while (ch!='?' && ch!='+') ch=Getchar();
		if (ch=='+'){
			name.clear();
			while (1){
				ch=Getchar();
				if (ch==' ') break;
				name.push_back(ch);
			}
			int x=read();
			if (!cnt[x]) cnt[x]=1;
			else ++cnt[x];
			pair<int,int>p=make_pair(x,cnt[x]);
			if (mp[name]) S.del(mp[name]);
			else ++tot;
			S.insert(p);
		}else{
			ch=Getchar();
			if (ch<'0' || ch>'9'){
				//int tim=clock();
				name.clear();
				while (ch!='\n'){
					name.push_back(ch);
					ch=Getchar();
				}
				//printf("%d %d\n",tot,S.get_rank(S.a[mp[name]].val));
				print::putint(S.get_rank(S.a[mp[name]].val)-1);
				print::put('\n');
			}else{
				int x=0;
				while (ch>='0' && ch<='9'){
					x=(x<<1)+(x<<3)+ch-'0';
					ch=Getchar();
				}	
				++x;	
				//int tim=clock();		
				for (int i=1;i<=10;++i){
					//int tim=clock();
					int k=S.get_kth(S.rt,x);
				//	printf("%d\n",clock()-tim);
					if (S.a[k].val.first>-inf && S.a[k].val.first<inf){
						if (i!=1) print::put(' ');
						for (int j=0;j<S.a[k].s.size();++j)
							print::put(S.a[k].s[j]);
					}
					++x;
				}
				print::put('\n');
				//printf("%d\n",clock()-tim);
			}
			//print::finish();
		}
	}
	//S.dfs(S.rt);
	print::finish();
	return 0;
}
