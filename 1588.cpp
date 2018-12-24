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
int n,m,tot=0,ans=0,root; 
int left[100010],right[100010];
int father[100010],key[100010];
void zig(int x){
	int y=father[x];
	left[y]=right[x];
	father[right[x]]=y;
	father[x]=father[y];
	if (y==left[father[y]])
		left[father[y]]=x;
	else
		right[father[y]]=x;		
	father[y]=x;
	right[x]=y;
}
void zag(int x){
	int y=father[x];
	right[y]=left[x];
	father[left[x]]=y;
	father[x]=father[y];
	if (y==left[father[y]])
		left[father[y]]=x;
	else
		right[father[y]]=x;		
	father[y]=x;
	left[x]=y;
}
void splay(int x,int y){
	while (y!=father[x]){
		if (y==father[father[x]]){
			if (left[father[x]]==x) zig(x);
			else zag(x);	
		}else{
			int p=father[x];	
			if (left[father[p]]==p && left[p]==x){
				zig(p);
				zig(x);	
			}else if(right[father[p]]==p && right[p]==x){
				zag(p);
				zag(x);	
			}else if(right[father[p]]==p && left[p]==x){
				zig(x);
				zag(x);
			}else{
				zag(x);
				zig(x);	
			}
		}
	}
	if (y==0) root=x;
}
int insert(int x){
	int p=root;
	while ((key[p]>x && left[p]) || (key[p]<x && right[p]) || (key[p]==x)){
		if (key[p]==x){
			splay(p,0); 
			return 0;
		}
		if (key[p]>x) p=left[p];
		else p=right[p];
	}
	key[++tot]=x;
	father[tot]=p;
	left[tot]=right[tot]=0;
	if (key[p]>x) left[p]=tot;
	else right[p]=tot;
	splay(tot,0);
	return 1;
}
int pre(int x){
	int p=left[x];
	if (!p) return -1;
	while (right[p])
		p=right[p];
	return key[x]-key[p];
}
int next(int x){
	int p=right[x];
	if (!p) return -1;
	while (left[p])
		p=left[p];
	return key[p]-key[x];
}
int main(){
	n=read();
	for (int i=1;i<=n;++i){
		int k=read();
		if (i==1){
			ans+=k;
			root=0;
			right[root]=0;
			left[root]=0;
			key[root]=0;
			insert(k);
			continue;	
		}
		if (!insert(k)) continue;
		int s1=pre(root),s2=next(root);
		//printf("%d %d\n",s1,s2);
		int temp=s1>s2?s2:s1;
		if (s1==-1) temp=s2;
		if (s2==-1) temp=s1;
		ans+=temp;
	}
	/*for (int i=1;i<=tot;++i)
		printf("%d %d %d %d\n",key[i],father[i],left[i],right[i]);*/
	printf("%d\n",ans);
	return 0;
}

