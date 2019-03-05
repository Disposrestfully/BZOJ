#include<bits/stdc++.h>
#define read() Read<int>()
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
using namespace std;
typedef long long ll;
const int N=4e4+5;
const int B=205;
int n,m,tot,ans;
int l[B],r[B],s[N];
int a[N],val[N];
int p[B][B],cnt[B][N];
inline void input(){
	n=read(),m=read();
	for (int i=1;i<=n;++i)
		a[i]=val[i]=read();
	sort(val+1,val+n+1);
	for (int i=1;i<=n;++i)
		a[i]=lower_bound(val+1,val+n+1,a[i])-val;
}
inline void init(){
	tot=n/B+1;
	for (int i=1;i<=n;++i) r[i/B+1]=i;
	for (int i=n;i;--i)	l[i/B+1]=i;
	for (int i=1;i<=tot;++i){
		for (int j=1;j<=n;++j)
			cnt[i][j]=cnt[i-1][j];
		for (int j=l[i];j<=r[i];++j)
			++cnt[i][a[j]];
	}
	for (int i=1;i<=tot;++i){
		memset(s,0,sizeof(s));
		for (int j=i;j<=tot;++j){
			for (int k=l[j];k<=r[j];++k){
				++s[a[k]];
				if (s[a[k]]>s[ans] || (s[a[k]]==s[ans] && a[k]<ans)) ans=a[k];
			}
			p[i][j]=ans;
		}
	}
	ans=0;
	memset(s,0,sizeof(s));
}
inline void query(int L,int R){
	int pl=L/B+1,pr=R/B+1;
	if (pl+1<=pr-1) ans=p[pl+1][pr-1];
	else ans=0;
	for (int i=L;i<=R && i<=r[pl];++i){
		++s[a[i]];
		int w1=s[a[i]],w2=s[ans];
		if (pl+1<=pr-1){
			w1+=cnt[pr-1][a[i]]-cnt[pl][a[i]];
			w2+=cnt[pr-1][ans]-cnt[pl][ans];
		}
		if (w1>w2 || (w1==w2 && a[i]<ans)) ans=a[i];
	}
	if (pl!=pr){
		for (int i=l[pr];i<=R;++i){
			++s[a[i]];
			int w1=s[a[i]],w2=s[ans];
			if (pl+1<=pr-1){
				w1+=cnt[pr-1][a[i]]-cnt[pl][a[i]];
				w2+=cnt[pr-1][ans]-cnt[pl][ans];
			}
			if (w1>w2 || (w1==w2 && a[i]<ans)) ans=a[i];
		}
	}
	for (int i=L;i<=R && i<=r[pl];++i) --s[a[i]];
	if (pl!=pr) 
		for (int i=l[pr];i<=R;++i) --s[a[i]];
	Print(ans=val[ans]);
}
int main(){
	freopen("2724.in","r",stdin);
	freopen("2724.out","w",stdout);
	input(),init();
	while (m--){
		int L=read(),R=read();
		L=(L+ans-1)%n+1;
		R=(R+ans-1)%n+1;
		if (L>R) swap(L,R);
		query(L,R);
	}
	io::flush();
	return 0;
}
