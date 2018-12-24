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
int n,m,top;
struct node{
	int l,r,w;
}a[100010];
int chk(node x,node y){
	if (x.l<y.l) return 1;
	if (x.l==y.l && x.r<y.r) return 1;
	return 0;
}
void push(int l,int r,int w){
	a[++top].l=l;a[top].r=r;
	a[top].w=w;
	int p=top,q=top/2;
	while (q>0 && chk(a[p],a[q])){
		node temp=a[p];a[p]=a[q];a[q]=temp;
		p=q;q/=2;
	}
}
void del(){
	a[1]=a[top];
	top--;
	int p=1,q=2;
	while ((chk(a[q],a[p]) && q<=top) || (chk(a[q+1],a[p]) && q+1<=top)){
		if (q+1<=top && chk(a[q+1],a[q])) q++;
		node temp=a[p];a[p]=a[q];a[q]=temp;
		p=q;q*=2;
	}
}
int solve(){
	node p=a[1];
	del();
	while (top){
		node q=a[1];
		del();
		if (q.l==p.l){
			if (q.r==p.r){
				if (q.w!=p.w) return 0;	
			}else push(p.r+1,q.r,q.w-p.w);
		}
		p=q;
	}
	return 1;
}
int main(){
	//freopen("trader.in","r",stdin);
	//freopen("trader.out","w",stdout);
	int T=read();
	while (T--){
		n=read();m=read();
		top=0;
		for (int i=1;i<=m;++i){
			int l=read(),r=read(),w=read();
			push(l,r,w);	
		}
		if (solve()) printf("true\n");
		else printf("false\n");
	}
	return 0;
}

