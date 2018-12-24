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
int f[510];
int n,m,l=0,r;
int ans1=-1,ans2=-1;
int S,T;
struct node{
	int x,y,w;
}a[5010];
int cmp(node x,node y){
	return x.w<y.w;	
}
int gcd(int x,int y){
	if (x%y==0) return y;
	return gcd(y,x%y);
} 
void clear(){
	for (int i=1;i<=n;++i)
		f[i]=i;
}
int find(int x){
	if (x==f[x]) return x;
	return f[x]=find(f[x]);
}
void link(int x,int y){
	int fx=find(x),fy=find(y);
	if (fx!=fy) f[fx]=fy;	
}
void update(){
	if (l==-1) return;
	int L=a[l].w,R=a[r].w;
	int x=gcd(L,R);
	L/=x;R/=x;
	if (ans1==-1 || ans1*L>ans2*R){
		ans1=R;
		ans2=L;
		return;
	}
}
int main(){
	//freopen("comf.in","r",stdin);
	n=read();m=read();
	clear();
	for (int i=1;i<=m;++i){
		a[i].x=read();
		a[i].y=read();
		a[i].w=read();	
		link(a[i].x,a[i].y);
	}
	S=read();T=read();
	if (find(S)!=find(T)){
		printf("IMPOSSIBLE\n");
		return 0;	
	}
	sort(a+1,a+m+1,cmp);
	for (l=1;l<=m;++l){
		clear();
		r=-1;
		for (int i=l;i<=m;++i){
			link(a[i].x,a[i].y);
			if (find(S)==find(T)){
				r=i;
				break;	
			}
		}
		if (r==-1) break;
		update();
	}
	if (ans2==1) printf("%d\n",ans1);
	else printf("%d/%d\n",ans1,ans2);
	return 0; 
}

