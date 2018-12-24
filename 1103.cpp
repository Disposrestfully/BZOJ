#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define read Read<int>
using namespace std;
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
struct node{
	int to,next;
}a[500010];
int head[250010],s[250010];
int l[250010],r[250010];
int cnt=0,n,m,t=0;
void init(int x,int y){
	a[++cnt].to=y;
	a[cnt].next=head[x];
	head[x]=cnt;
}
void dfs(int x,int father){
	t++;
	l[x]=t;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y!=father)
			dfs(y,x);
	}
	r[x]=t;
}
int lowbit(int x){
	return x&(-x);
}
int main(){
	//freopen("1103.in","r",stdin);
	n=read();
	for (int i=1;i<n;++i){
		int x=read(),y=read();
		init(x,y);init(y,x);
	}
	dfs(1,0);
	for (int i=1;i<=n;++i){
		for (int j=l[i];j<=n;j+=lowbit(j))	
			s[j]++;
		for (int j=r[i]+1;j<=n;j+=lowbit(j))
			s[j]--;
	}
	m=read();
	m=n+m-1;
	while (m--){
		char c;
		scanf("%c",&c);
		if (c=='A'){
			int x=read(),y=read();
			int k=x>y?x:y;
			for (int i=l[k];i<=n;i+=lowbit(i))
				s[i]--;
			for (int i=r[k]+1;i<=n;i+=lowbit(i))
				s[i]++;
		}else{
			int ans=0,x=read();
			for (int i=l[x];i>=1;i-=lowbit(i))
				ans+=s[i];
			printf("%d\n",ans-1);
		}
	}
	return 0;
}
