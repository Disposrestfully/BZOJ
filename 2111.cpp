#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
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
int n,p,l,r,tot;
int f[1000010];
int c[1000010],rev[1000010];
int mult(int x,int y){
	x%=p;y%=p;
	return (int)((long long)x*(long long)y%(long long)p);
}
int add(int x,int y){
	x%=p;y%=p;
	return ((x+y)%p+p)%p;
}
int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=mult(res,x);	
		x=mult(x,x);
		y>>=1;
	}
	return res;
}
int C(int x,int y){
	if (y>x) return 0;
	return mult(c[x],mult(rev[y],rev[x-y]));	
}
int lucas(int x,int y){
	if (y==0) return 1;
	return mult(lucas(x/p,y/p),C(x%p,y%p));	
}
int main(){
	n=read();p=read();
	c[0]=rev[0]=1;
	for (int i=1;i<=n;++i){
		c[i]=mult(c[i-1],i);
		rev[i]=Pow(c[i],p-2);	
	}
	f[0]=f[1]=1;
	tot=2;l=r=0;
	for (int i=2;i<=n;++i){
		if (l==r) tot*=2;
		if (l*2<tot-2) l++;
		else r++;
		int k;
		if (n>p) k=lucas(i-1,l);
		else k=C(i-1,l);
		f[i]=mult(k,mult(f[l],f[r]));	
	}
	printf("%d\n",f[n]);
	return 0;
}

