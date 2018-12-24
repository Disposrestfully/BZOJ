#include "iostream"  
#include "stdlib.h"  
#include "stdio.h"  
#include "vector"  
  #define read Read<int>
using namespace std;  
  
const int N=1000005;  
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
  
struct Edge{int to,next; bool ok;} e[2*N]; int head[N],tmp;  
inline void add(int u,int v){  
    ++tmp; e[tmp].to=v; e[tmp].next=head[u]; e[tmp].ok=true; head[u]=tmp;  
    ++tmp; e[tmp].to=u; e[tmp].next=head[v]; e[tmp].ok=true; head[v]=tmp;  
}  
  
int n,value[N];  
typedef long long ll;  
int fa[N],q[N],l,r,w;  
ll dp[2][2][N],ans;  
bool vis[N],bf[N];  
  
void tredp (int rt){  
    int i; dp[w][1][rt]=value[rt];  
    vis[rt]=true;  
    for (i=head[rt]; i; i=e[i].next){  
        int k=e[i].to;  
        if (e[i].ok&&dp[w][1][k]==0){  
            tredp(k);  
            dp[w][0][rt]+=max(dp[w][0][k],dp[w][1][k]);  
            dp[w][1][rt]+=dp[w][0][k];  
        }  
    }  
    vis[rt]=false;  
}  
  
ll dfs(int t){  
    l=1; r=0; q[++r]=t;  
    bf[t]=1; int u=-1,v=-1;  
    while (l<=r){  
        int k=q[l++],i;  
        for (i=head[k]; i; i=e[i].next){  
            int to=e[i].to;  
            if (!bf[to]||fa[k]!=to){  
                if(bf[to]){  
                    e[i%2?i+1:i-1].ok=e[i].ok=false;  
                    u=k; v=to; l=r+1; break;  
                }  
                bf[to]=true;  
                fa[to]=k;  
                q[++r]=to;  
            }  
        }  
    }  
    w=0;  
    if (u==-1&&v==-1){  
        tredp(t); return max(dp[0][0][t],dp[0][1][t]);  
    }  
    tredp(u); w=1; tredp(v);  
    return max(dp[0][0][u],dp[1][0][v]);  
}  
  
int main(){  
    n=read(); int i,a;  
    for (i=1;i<=n;i++){  
        value[i]=read();  
        a=read(); add(i,a);  
    }  
    for (i=1;i<=n;i++){  
        if (!dp[0][1][i]){  
            ans += dfs(i);  
        }  
    }  
    cout << ans << endl;  
    return 0;  
}  
