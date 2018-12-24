#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#define y1 Y1
#define read() Re.Read()
#define lowbit(i) i&(-i)
#define getchar() Re.Get_Char()
using namespace std;
typedef long long ll;
const int N=1e5+5;
struct Readint{
	char buffer[1<<15],*S,*T; 
	inline char Get_Char(){  
    	if(S==T){  
     	   T=(S=buffer)+fread(buffer,1,1<<15,stdin);
      	  if(S==T) return EOF;  
    	}  
    	return *S++;  
	}
	int Read(){
	    char c;  
	    int re=0;  
	    for (c=Get_Char();c<'0'||c>'9';c=Get_Char()){
    		if (c==EOF) return -1;
    	}	
 	   	while(c>='0'&&c<='9')  
           	re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();  
    	return re;  
	}
}Re;
namespace print{
    static const int BUF=50000000;
    char buf[BUF],*h=buf;
    inline void put(char ch){
        h==buf+BUF?(fwrite(buf,1,BUF,stdout),h=buf):0;
        *h++=ch;
    }
    inline void putint(int num){
        static char _buf[30];
        sprintf(_buf,"%d",num);
        for (char *s=_buf;*s;s++)put(*s);
    }
    inline void finish(){
        fwrite(buf,1,h-buf,stdout);
    }
};
int C=0;
struct node{
	int a[4][4];
}a[N<<2];
int c[N][3],n;
char opt;
void solve(node &x){
	if (x.a[1][0]+x.a[3][1]+x.a[3][2]+x.a[2][0]==3)
		x.a[1][0]=x.a[3][1]=x.a[3][2]=x.a[2][0]=1;
	x.a[3][0]|=((x.a[3][1]&x.a[1][0])|(x.a[3][2]&x.a[2][0]));
	x.a[2][1]|=((x.a[2][0]&x.a[1][0])|(x.a[3][1]&x.a[3][2]));
}
node merge(node u,node v){
	node x;
	memset(x.a,0,sizeof(x.a));
	x.a[1][0]=(u.a[1][0]&v.a[1][0])|(u.a[3][0]&v.a[2][1]);
	x.a[3][2]=(u.a[3][2]&v.a[3][2])|(u.a[2][1]&v.a[3][0]);
	x.a[2][0]=u.a[2][0];
	x.a[3][1]=v.a[3][1];
	x.a[2][1]=(u.a[2][1]&v.a[1][0]);
	x.a[3][0]=(u.a[1][0]&v.a[3][0]);
	solve(x);
	return x;
}
node assign(int l){
	node x;
	memset(x.a,0,sizeof(x.a));
	x.a[1][0]=c[l][1];
	x.a[3][2]=c[l][2];
	x.a[2][0]=c[l][0];
	x.a[3][1]=c[l+1][0];
	solve(x);
	return x;
}
void build(int x,int l,int r){
	//printf("%d %d %d\n",x,l,r);
	if (l==r){
		a[x]=assign(l);
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build((x<<1)+1,mid+1,r);
	a[x]=merge(a[x<<1],a[(x<<1)+1]);
}
node query(int x,int l,int r,int L,int R){
	//if (C==132) printf("%d %d %d %d %d\n",x,l,r,L,R);
	if (l>=L && r<=R){
		/*if (C==132 && L==6 && R==7)
			printf("%d %d %d\n",a[x<<1].a[3][1],a[x<<1].a[1][0],a[(x<<1)+1].a[3][2]);*/
		return a[x];
	}
	int mid=(l+r)>>1;
	if (mid<R && mid>=L) return merge(query(x<<1,l,mid,L,R),query((x<<1)+1,mid+1,r,L,R));
	else if (mid>=L) return query(x<<1,l,mid,L,R);
	else return query((x<<1)+1,mid+1,r,L,R);
}
void update(int x,int l,int r,int pos){
	//printf("%d %d %d %d\n",x,l,r,pos);
	if (l==r){
		//if (C==80006)printf("%d %d %d %d\n",l,c[l][1],c[l][2],c[l][0]);
		a[x]=assign(l);
		//if (C==80006)printf("%d %d %d %d\n",a[x].a[1][0],c[l][1],c[l][2],c[l][0]);
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) update(x<<1,l,mid,pos);
	if (pos>mid) update((x<<1)+1,mid+1,r,pos);
	a[x]=merge(a[x<<1],a[(x<<1)+1]);
}
int main(){
	//freopen("7.in","r",stdin);
	//freopen("7s.out","w",stdout);
	n=read();
	build(1,1,n-1);
	while (1){
		opt=0;
		while (opt>'Z' || opt<'A') opt=getchar();
		if (opt=='E') break;
		int r1=read(),c1=read(),r2=read(),c2=read();
		if (opt=='C'){
			if (r1==r2){
				if (c1>c2) swap(c1,c2);
				c[c1][r1]=0;
				update(1,1,n-1,c1);
			}else{
				c[c1][0]=0;
				if (c1!=1) update(1,1,n-1,c1-1);
				if (c1!=n) update(1,1,n-1,c1);
			}
		}else if (opt=='O'){
			if (r1==r2){
				if (c1>c2) swap(c1,c2);
				c[c1][r1]=1;
				update(1,1,n-1,c1);
			}else{
				c[c1][0]=1;
				if (c1!=1) update(1,1,n-1,c1-1);
				if (c1!=n) update(1,1,n-1,c1);
			}
		}else{
			++C;
			if (c1==c2){
				node x,y;
				if (c1==1) x.a[3][1]=c[1][0];
				else x=query(1,1,n-1,1,c1-1);
				if (c1==n) y.a[2][0]=c[n][0];
				else y=query(1,1,n-1,c1,n-1);
				if (x.a[3][1] || y.a[2][0]) print::put('Y');
				else print::put('N');
			}else{
				//printf("Go\n");
				if (c1>c2){
					swap(c1,c2);
					swap(r1,r2);
				}
				//if (C==132) printf("%d %d %d %d\n",r1,c1,r2,c2);
				node x,y,z;
				if (c1==1) x.a[3][1]=c[c1][0];
				else x=query(1,1,n-1,1,c1-1);
				if (c2==n) y.a[2][0]=c[n][0];
				else y=query(1,1,n-1,c2,n-1);
				z=query(1,1,n-1,c1,c2-1);
			//	if (C==132) printf("%d %d %d %d %d %d %d\n",c[6][0],c[6][1],c[6][2],c[7][0],c[7][1],c[7][2],c[8][0]);
				//if (C==132) printf("%d %d %d %d %d\n",z.a[3][0],z.a[1][0],z.a[3][2],z.a[2][0],z.a[3][1]);
				z.a[2][0]|=x.a[3][1];
				z.a[3][1]|=y.a[2][0];
				solve(z);
				r1=r1==1?0:2;
				r2=r2==1?1:3;
				if (z.a[max(r1,r2)][min(r1,r2)]) print::put('Y');
				else print::put('N');
			}
			print::put('\n');
		}
		//printf("C==%d\n",++C);
	}
	print::finish();
	return 0;
}

