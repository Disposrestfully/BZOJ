#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
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
int n,m,k,cnt,t;
struct node{
	int to,next;
}a[2010];
int head[1010],sz[1010];
int p[1010],cet[1010],q[1010];
void init(int x,int y){
	a[++cnt].to=y;
	a[cnt].next=head[x];
	head[x]=cnt;
}
void dfs(int x,int father){
	q[++t]=x;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y!=father){
			dfs(y,x);
			if (sz[x]+sz[y]>=m){
				sz[x]=0;
				cet[++k]=x;
				while (q[t]!=x)
					p[q[t--]]=k;
			}else sz[x]+=sz[y];
		}
	}
	sz[x]++;
}
void solve(int x,int father,int y){
	if (p[x]) y=p[x];
	else p[x]=y;
	for (int i=head[x];i;i=a[i].next)
		if (a[i].to!=father)
			solve(a[i].to,x,y);
}
int main(){
	n=read();m=read();
	if (n<m){
		printf("0\n");
		return 0;
	}
	for (int i=1;i<n;++i){
		int x=read(),y=read();
		init(x,y);init(y,x);
	}
	dfs(1,0);
	if (!k) cet[++k]=1;
	solve(1,0,k);
	printf("%d\n",k);
	for (int i=1;i<n;++i) 
		printf("%d ",p[i]);
	printf("%d\n",p[n]);
	for (int i=1;i<k;++i)
		printf("%d ",cet[i]);
	printf("%d\n",cet[k]);
	return 0;
}
