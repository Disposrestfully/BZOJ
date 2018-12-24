#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define read Read<int>
using namespace std;
int ans,cnt=0;
int f[400010],head[400010];
int s[400010],p[400010];
struct node{
	int to,next; 
}a[400010];
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
void init(int x,int y){
	a[++cnt].to=y;
	a[cnt].next=head[x];
	head[x]=cnt;
}
int find(int x){
	if (f[x]==x) return x;
	return f[x]=find(f[x]);
}
int add(int x){
	int fx=find(x);
	for (int i=head[x];i!=0;i=a[i].next)
		if (!p[a[i].to]){
			int fy=find(a[i].to);
			if (fx!=fy){
				f[fx]=f[fy];
				fx=fy;
				ans--;
			}
		}
}
int Ans[200010];
int main(){
	int i,j,k,m,n;
	n=read();m=read();
	for (i=1;i<=m;++i){
		int x,y;
		x=read();y=read();
		init(x,y);init(y,x);
	}
	k=read();
	for (i=1;i<=k;++i){
		s[i]=read();
		p[s[i]]=1;
	}
	ans=n-k;
	for (i=0;i<n;i++)
		f[i]=i;
	for (i=0;i<n;++i)
		if (!p[i])
			add(i);
	Ans[k+1]=ans;
	for (i=k;i>=1;--i){
		ans++;
		p[s[i]]=0;
		add(s[i]);
		Ans[i]=ans;
	}
	for (i=1;i<=k+1;++i)
		printf("%d\n",Ans[i]);
	return 0;
}
