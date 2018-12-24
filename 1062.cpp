#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
#define y1 Y1
using namespace std;
typedef long long ll;
const int N=2005;
const int M=1e6+5;
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
int s[2][N][N<<1];
int n,len;
struct node{
	int x;
	int y1,y2;
}a[M];
inline void add(int x,int k){
	for (int i=a[x].x+1;i<N;i+=lowbit(i)){
		for (int j=a[x].y1+1;j<N<<1;j+=lowbit(j)) s[0][i][j]+=k;
		for (int j=a[x].y2+1;j<N<<1;j+=lowbit(j)) s[1][i][j]+=k;
	}
}
inline int Sum(int x,int y,int k){
	int res=0;
	if (x<0 || y<0) return 0;
	++x,++y;
	x=min(x,(len<<1)+1);
	y=min(y,(len<<2)+1);
	for (int i=x;i;i-=lowbit(i))
		for (int j=y;j;j-=lowbit(j))
			res+=s[k][i][j];
	return res;
}
inline int sum(int k,int x1,int y1,int x2,int y2){
	return Sum(x2,y2,k)-Sum(x1-1,y2,k)-Sum(x2,y1-1,k)+Sum(x1-1,y1-1,k);
}
inline int solve(int t,int l,int r){
	int d=(r==len),k=len<<1;
	int res=sum(0,t,l+t,r+t,k<<1)+sum(0,0,l+t-k,r+t-k-d,k<<1);
	res+=sum(1,k-r+t+d,l-t,k,k<<1)+sum(1,t-r,l-t+k,t-1,k<<1);
	return res;
}
int main(){
	//freopen("1.in","r",stdin);	
	n=read();len=read();
	while (n--){
		int opt=read(),t=read();
		if (opt==1){
			int c=read(),l=read(),r=read(),d=read();
			a[c].x=(t+(len<<1)-(l*d))%(len<<1);
			a[c].y1=r-l+a[c].x;
			a[c].y2=r-l-a[c].x+(len<<1);
			add(c,1);
		}else if (opt==2){
			int l=read(),r=read();
			Print(solve(t%(len<<1),l,r));
		}else{
			int c=read();
			add(c,-1);
		}
	}
	io::flush();
	return 0;
}
