#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=1e6+5;
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
int n,ans1,ans2;
int a[N],vis[N],d[N];
queue<int>q;
int main(){
	//freopen("isaac.in","r",stdin);
	//freopen("isaac.out","w",stdout);	
	n=ans2=read();
	for (int i=1;i<=n;++i)
		++d[a[i]=read()];
	for (int i=1;i<=n;++i)
		if (!d[i]){
			--ans2;
			for (int j=i;!vis[j];j=a[j])
				vis[j]=1;
			q.push(i);	
		}
	for (int i=1;i<=n;++i)
		if (!vis[i] && a[i]!=i){
			for (int j=i;!vis[j];j=a[j])
				vis[j]=1;
			--ans2;	
		}
	memset(vis,0,sizeof(vis));
	while (!q.empty()){
		int x=q.front();
		vis[x]=1;
		q.pop();
		if (!vis[a[x]]){
			++ans1;
			vis[a[x]]=1;
			--d[a[a[x]]];
			if (!d[a[a[x]]]) q.push(a[a[x]]);
		}
	}
	for (int i=1;i<=n;++i){
		if (!vis[i]){
			int sz=0;
			for (int j=i;!vis[j];j=a[j])
				vis[j]=1,++sz;
			ans1+=((sz+1)>>1);
		}
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}

