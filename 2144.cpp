#include<bits/stdc++.h>
typedef long long ll;
#define int ll
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
const int N=1e5+5;
struct node{
	int l,mid,r;
	inline void init(){
		l=read(),mid=read(),r=read();
		if (l>r) swap(l,r);
		if (mid>r) swap(mid,r);
		if (l>mid) swap(l,mid);
	}
	inline bool operator == (const node &u)const{
		return (l==u.l && mid==u.mid && r==u.r);	
	}
}s,t;
inline int get_dep(node x){
	int res=0;
	int l=x.l,mid=x.mid,r=x.r;
	while (mid-l!=r-mid){
		if (mid-l>r-mid){
			int t=r-mid,k=(mid-l)/t;
			if ((mid-l)%t==0) --k;
			res+=k,r-=k*t,mid-=k*t;
		}else{
			int t=mid-l,k=(r-mid)/t;
			if ((r-mid)%t==0) --k;
			res+=k,l+=k*t,mid+=k*t;
		}
	}
	return res;
}
inline node move(node x,int d){
	int l=x.l,mid=x.mid,r=x.r;
	while (mid-l!=r-mid && d){
		if (mid-l>r-mid){
			int t=r-mid,k=(mid-l)/t;
			if ((mid-l)%t==0) --k;
			k=min(k,d);
			r-=k*t,mid-=k*t,d-=k;
		}else{
			int t=mid-l,k=(r-mid)/t;
			if ((r-mid)%t==0) --k;
			k=min(k,d);
			l+=k*t,mid+=k*t,d-=k;
		}
	}
	return (node){l,mid,r};
}
signed main(){
	freopen("2144.in","r",stdin);
	freopen("2144.out","w",stdout);
	s.init(),t.init();
	int sd=get_dep(s),td=get_dep(t);
	if (move(s,sd)==move(t,td)){
		puts("YES");
		if (sd>td) s=move(s,sd-td);
		else t=move(t,td-sd);
		if (t==s){
			printf("%lld\n",abs(sd-td));
			return 0;
		}
		int ans=abs(sd-td);
		for (int i=30;~i;--i){
			int now=(1<<i);
			if (!(move(s,now)==move(t,now))){
				ans+=now<<1,s=move(s,now),t=move(t,now);
				//printf("%lld (%lld,%lld,%lld) (%lld,%lld,%lld)\n",now,s.l,s.mid,s.r,t.l,t.mid,t.r);	
			}
		}
		ans+=2;
		printf("%lld\n",ans);
	}else puts("NO");
	return 0;
}
