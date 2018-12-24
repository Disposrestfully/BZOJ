#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define read Read<int>
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
	int x,w;
}q[2010];
int a[2010][2010],l[2010][2010];
int n,m,top=0,ans1=0,ans2=0;
void init(int x,int w){
	int p=x;
	while (top && q[top].w>w){
		ans1=max(ans1,min(q[top].w,x-q[top].x)*min(q[top].w,x-q[top].x));
		ans2=max(ans2,q[top].w*(x-q[top].x));	
		p=q[top].x;
		top--;
	}
	q[++top].x=p;
	q[top].w=w;
}
void solve(int x){
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			l[i][j]=a[i][j]==x?l[i][j-1]+1:0;
	for (int j=1;j<=m;++j){
		top=0;
		for (int i=1;i<=n;++i)
			init(i,l[i][j]);
		init(n+1,0);
	}
}	
int main(){
	n=read();m=read();
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			a[i][j]=read();
			if (i%2!=j%2) a[i][j]^=1;	
		}	
	solve(0);
	solve(1);
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}

