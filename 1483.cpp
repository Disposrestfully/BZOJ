#include<bits/stdc++.h>
#define read() Read<int>()
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
using namespace std;
typedef long long ll;
const int N=1e6+5;
int n,m,mx,tot,ans,num=1;
int a[N],c[N];
int p[N];
set<int>s[N];
set<int>::iterator iter;
int main(){
	freopen("1483.in","r",stdin);
	freopen("1483.out","w",stdout);
	n=ans=read();m=read();
	for (int i=1;i<=n;++i) p[i]=m+10;
	for (int i=1;i<=n;++i){
		a[i]=read();
		mx=max(mx,a[i]);
		s[a[i]].insert(i);
		if (i!=1 && a[i]==a[i-1]) p[i]=1,--ans;
	}
	for (int i=1;i<=mx;++i)
		if (!s[i].empty()) c[i]=i;
	for (int i=1;i<=m;++i){
		int opt=read();
		if (opt==2){
			printf("%d\n",ans);
		}else{
			++num;
			int x=read(),y=read();
			if (x==y || !c[x] || s[c[x]].empty()) continue;
			if (!c[y] || s[c[y]].empty()) c[y]=c[x],c[x]=0;
			if (s[c[x]].size()>s[c[y]].size()){
				for (iter=s[c[y]].begin();iter!=s[c[y]].end();iter++){
					int now=*iter;
					s[c[x]].insert(now);
					if (s[c[x]].count(now+1) && p[now+1]>num) 
						p[now+1]=num,--ans;
					if (s[c[x]].count(now-1) && p[now]>num) 
						p[now]=num,--ans;
				}
				s[c[y]]=set<int>();
				c[y]=c[x],c[x]=0;
			}else{
				for (iter=s[c[x]].begin();iter!=s[c[x]].end();iter++){
					int now=*iter;
					s[c[y]].insert(now);
					if (s[c[y]].count(now+1) && p[now+1]>num) 
						p[now+1]=num,--ans;
					if (s[c[y]].count(now-1) && p[now]>num) 
						p[now]=num,--ans;
				}
				s[c[x]]=set<int>();
				c[x]=0;
			}
		}
	}
	return 0;
}
