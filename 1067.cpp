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
int a[50010],s[50010],n,m;
int mx[500010][17],lg[50010];
void RMQ(){
	for (int j=1;j<=16;++j)
		for (int i=1;i<=n;++i)
				if (i+(1<<j)<=n+1)
					mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);	

}
int getmx(int l,int r){
	int x=lg[r-l+1];
	return max(mx[l][x],mx[r-(1<<x)+1][x]);
}
int find(int x){
	if (x<a[1]) return 0;
	if (x>a[n]) return n;
	int l=1,r=n;
	while (l<r){
		int mid=(l+r)>>1;
		if (a[mid]<x) l=mid+1;
		else r=mid;
	}	
	if (a[r]==x) return r; 
	return r-1;
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i){
		a[i]=read();
		if (i==1) s[i]=1;
		else s[i]=a[i]==a[i-1]+1?s[i-1]+1:s[i-1];
		mx[i][0]=read();
		lg[i]=i<=1?0:lg[i>>1]+1;
	}
	RMQ();
	/*for (int i=1;i<=n;++i)
		printf("%d ",s[i]);
	printf("\n");*/
	m=read();
	while (m--){
		int y=read(),x=read();
		if (x<y){
			printf("false\n");
			continue;	
		}
		int px=find(x),py=find(y);
	//	printf("%d %d %d %d\n",y,x,py,px);
		if (a[px]!=x && a[py]!=y){
			printf("maybe\n");
			continue;	
		}
		if (a[px]!=x && a[py]==y){
			if (px==py){
				printf("maybe\n");
				continue;	
			}
			int u=getmx(py,px),v=getmx(py+1,px);
			if (u!=mx[py][0] || mx[py][0]==v){
				printf("false\n");
				continue;
			}else{
				printf("maybe\n");
				continue;	
			}
		}
		if (a[px]==x && a[py]!=y){
			++py;
			if (px==py){
				printf("maybe\n");
				continue;	
			}
			int u=getmx(py,px),v=getmx(py,px-1);
			if (u!=mx[px][0] || mx[px][0]==v){
				printf("false\n");
				continue;
			}else{
				printf("maybe\n");
				continue;	
			}
		}
		int flag=0,sum=s[px]-s[py];
		if (sum==x-y) flag=1;
		if (mx[px][0]>mx[py][0]){
			printf("false\n");
			continue;	
		}
		if (px==py+1){
			if (flag) printf("true\n");
			else printf("maybe\n");	
			continue;
		}
		int u=getmx(py+1,px),v=getmx(py+1,px-1);
	//	printf("%d %d\n",u,v);
		if (u!=mx[px][0] || mx[px][0]==v){
			printf("false\n");
			continue;
		}else{
			if (flag) printf("true\n");
			else printf("maybe\n");	
		}
	}
	return 0;
}

