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
double a[20][20],x[20];
struct node{
	double p[20];
}s,q;
int n;
int main(){
	//freopen("sp.in","r",stdin);
	//freopen("sp.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i)
		scanf("%lf",&q.p[i]);
	for (int i=1;i<=n;++i){
		double k=0;
		for (int j=1;j<=n;++j){
			scanf("%lf",&s.p[j]);
			a[i][j]=2*(s.p[j]-q.p[j]);
			k+=(s.p[j]*s.p[j])-(q.p[j]*q.p[j]);
		}
		a[i][n+1]=k;
	}
/*	for (int i=1;i<=n;++i){
		for (int j=1;j<=n+1;++j)
			printf("%.3lf ",a[i][j]);
		printf("\n");		
	}*/
	int col=1;
	for (int k=1;k<=n && col<=n;k++,col++){
		double mx=fabs(a[k][col]);
		int pos=k;
		for (int i=k+1;i<=n;++i)
			if (mx<a[i][col]){
				mx=a[i][col];
				pos=i;	
			}
		if (pos!=k)
			for (int i=1;i<=n+1;++i)
				swap(a[pos][i],a[k][i]);
		if (a[k][col]==0){
			--k;
			continue;	
		}
		for (int i=k+1;i<=n;++i){
			if (a[i][col]!=0){
				double u=a[k][col]/a[i][col];
				for (int j=col;j<=n+1;++j)
					a[i][j]=a[i][j]*u-a[k][j];
			}
		}
	}
/*	for (int i=1;i<=n;++i){
		for (int j=1;j<=n+1;++j)
			printf("%.3lf ",a[i][j]);
		printf("\n");		
	}*/
	for (int i=n;i>=1;--i){
		double temp=0;
		for (int j=i+1;j<=n;++j)
			temp+=a[i][j]*x[j];
		x[i]=(a[i][n+1]-temp)/a[i][i];
	}
	for (int i=1;i<n;++i)
		printf("%.3lf ",x[i]);
	printf("%.3lf\n",x[n]);
	return 0;
}

