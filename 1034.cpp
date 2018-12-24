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
int n,ans;
int f1,f2,l1,l2;
int a[1000010],s[1000010];
int cmp(int x,int y){
	return x<y; 
}
int main(){
	n=read();
	for (int i=1;i<=n;++i) a[i]=read();
	for (int i=1;i<=n;++i) s[i]=read();
	sort(a+1,a+n+1,cmp);
	sort(s+1,s+n+1,cmp);
	f1=f2=1;l1=l2=n;ans=0;
	while (f1<=l1 && f2<=l2){
		if (a[f1]>s[f2]){
			f1++;f2++;
			ans+=2;	
		}else if (a[l1]>s[l2]){
			ans+=2;
			l1--;l2--;	
		}else{
			ans+=(a[f1]==s[l2]);
			l2--;f1++;	
		}
	}	
	printf("%d ",ans);
	f1=f2=1;l1=l2=n;ans=0;
	while (f1<=l1 && f2<=l2){
		if (s[f1]>a[f2]){
			f1++;f2++;
			ans+=2;	
		}else if (s[l1]>a[l2]){
			ans+=2;
			l1--;l2--;	
		}else{
			ans+=(s[f1]==a[l2]);
			l2--;f1++;	
		}
	}	
	printf("%d\n",2*n-ans);
	return 0;
}

