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
int p[20]={0,2,3,5,7,11,13,17,19,23,29,31,37};
int n,mx=0,ans=0; 
int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res*=x;
		x*=x;
		y>>=1;
	}
	return res;
}
void dfs(int x,int cnt,long long now,int pre){
	if (now>n || now<0) return;
	if (x==12){
		if (mx<cnt || (mx==cnt && ans>now)){
			mx=cnt;
			ans=now;	
		}
		return;
	}
	for (int i=0;i<=pre;++i){
		if (now*Pow(p[x],i)>n) break;
		dfs(x+1,cnt*(i+1),now*Pow(p[x],i),i);
	}
}
int main(){
	n=read();
	dfs(1,1,1,30);
	printf("%d\n",ans);
	return 0;
}

