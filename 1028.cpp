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
int s[500010],a[500010];
int n,m,tot=0;
int ans[500010];
void dfs(int x){
	for (int i=1;i<=n;++i){
		if (s[i]>=2){
			int flag=1;
			s[i]-=2;
			for (int j=1;j<=n+2;++j)
				a[j]=s[j];
			for (int j=1;j<=n+2;++j){
				/*printf("%d %d %d\n",x,i,j);
				for (int k=1;k<=n;++k)
						printf("%d ",a[k]);
					printf("\n");*/
				if (a[j]<0){
					flag=0;
					break;
				}
				a[j]%=3;
				a[j+1]-=a[j];
				a[j+2]-=a[j];
			}
			s[i]+=2;
			if (flag){
				ans[++tot]=x;
				return;	
			}
		}
	}
}
int main(){
//	freopen("m.in","r",stdin);
//	freopen("m.out","w",stdout); 
	n=read();m=read();
	for (int i=1;i<=3*m+1;++i)
		s[read()]++;
	for (int i=1;i<=n;++i){
		s[i]++;
		dfs(i);
		s[i]--;
	}
	if (!tot) printf("NO\n");
	else{
		for (int i=1;i<tot;++i)
			printf("%d ",ans[i]);
		printf("%d\n",ans[tot]);
	}
	return 0;
}

