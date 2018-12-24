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
int s[5010][5010]; 
int n,m,rx,ry;
int main(){
//	freopen("bomb.in","r",stdin);
	n=read();m=read();
	for (int i=1;i<=n;++i){
		int x,y;
		x=read();y=read();
		rx=rx>x?rx:x;
		ry=ry>y?ry:y;
		s[x][y]+=read();	
	}
	for (int i=1;i<=rx;++i)
		s[i][0]+=s[i-1][0];
	for (int i=1;i<=ry;++i)
		s[0][i]+=s[0][i-1];
	for (int i=1;i<=rx;++i)
		for (int j=1;j<=ry;++j)
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	int ans=0;
	for (int i=0;i<=rx;++i)
		for (int j=0;j<=ry;++j){
			int k=s[i][j];
			if (i>=m) k-=s[i-m][j];
			if (j>=m) k-=s[i][j-m];
			if (i>=m && j>=m) k+=s[i-m][j-m];
			ans=max(ans,k);
			//printf("%d %d %d\n",i,j,s[i][j]);	
		}
	printf("%d\n",ans);
	return 0;
}

