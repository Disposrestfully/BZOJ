#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<sys/mman.h>
#define y1 Y1
#define read() Re.Read()
#define lowbit(i) i&(-i)
//#define Get_Char() getchar()
using namespace std;
typedef long long ll;
const int N=55;
int n,A,B,La,Ra,Lb,Rb,fa,fb;
char s[N];
int f[N],l[N],r[N],a[N][N];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
void link(int u,int v){
	int fx=find(u),fy=find(v);
	f[fx]=fy;
}
int p[N][N],c[N][N];
int chk(int x,int y){
	int f=0;
	for (int k1=La;k1<=Ra;++k1){
		for (int k2=Lb;k2<=Rb;++k2){
			if (k1==k2 && c[fa][fb]) continue;
			if (k1!=k2 && fa==fb) continue;
			for (int k3=l[x];k3<=r[x];++k3){
				for (int k4=l[y];k4<=r[y];++k4){
					if (k3==k4 && c[x][y]) continue;
					if (k1==k3 && c[fa][x]) continue;
					if (k1==k4 && c[fa][y]) continue;
					if (k2==k3 && c[fb][x]) continue;
					if (k2==k4 && c[fb][y]) continue;
					if (k1!=k3 && fa==x) continue;
					if (k1!=k4 && fa==y) continue;
					if (k2!=k3 && fb==x) continue;
					if (k2!=k4 && fb==y) continue;
					if (k3!=k4 && x==y) continue;
					int s1=k1+k2,s2=k3+k4;
					if (!f){
						if (s1<s2) f=1;
						if (s1==s2) f=2;
						if (s1>s2) f=-1;
					}else if (s1<s2){
						if (f!=1) return 0;
					}else if (s1>s2){
						if (f!=-1) return 0;
					}else if (s1==s2){
						if (f!=2) return 0;
					}
				}
			}
		}
	}
	return f;
}
int main(){
	scanf("%d%d%d",&n,&A,&B);
	for (int i=1;i<=n;++i)
		f[i]=i,l[i]=1,r[i]=3;
	for (int i=1;i<=n;++i){
		scanf("%s",s+1);
		for (int j=1;j<=n;++j){
			a[i][j]=0;
			if (s[j]=='=') link(i,j),a[i][j]=2;
			if (s[j]=='+') l[i]=max(l[i],l[j]+1),a[i][j]=1;
			if (s[j]=='-') r[i]=min(r[i],r[j]-1),a[i][j]=-1;
		}		
	}
	for (int i=1;i<=n;++i){
		int x=find(i);
		l[x]=max(l[i],l[x]);
		r[x]=min(r[x],r[i]);
	//	printf("%d %d\n",l[i],r[i]);
	}
	for (int t=1;t<=3;++t){
		for (int i=1;i<=n;++i){
			int x=find(i);
			for (int j=1;j<=n;++j){
				int y=find(j);
				if (x==y) continue;
				if (a[i][j]==1){
					r[y]=min(r[y],r[x]-1);
					c[x][y]=1;
					c[y][x]=-1;
				}
				if (a[i][j]==-1){
					l[y]=max(l[y],l[x]+1);
					c[x][y]=-1;	
					c[y][x]=1;
				}
			}
		}	
	}
	fa=find(A);fb=find(B);
	La=l[fa],Lb=l[fb];
	Ra=r[fa],Rb=r[fb];
	/*for (int i=1;i<=n;++i)
		printf("%d %d %d\n",i,l[find(i)],r[find(i)]);
	printf("%d %d %d %d\n",La,Ra,Lb,Rb);*/
	for (int i=1;i<=n;++i){
		if (i==A || i==B) continue;
		for (int j=i+1;j<=n;++j){
			if (j==A || j==B) continue;
			p[i][j]=chk(find(i),find(j));
			//printf("%d %d %d\n",i,j,p[i][j]);
		}
	}
	int ans1=0,ans2=0,ans3=0;
	for (int i=1;i<=n;++i){
		if (i==A || i==B) continue;
		for (int j=i+1;j<=n;++j){
			if (j==A || j==B || !p[i][j]) continue;
			if (p[i][j]==2) ++ans2;
			else if (p[i][j]==-1) ++ans1;
			else ++ans3;
		}
	}
	printf("%d %d %d\n",ans1,ans2,ans3);
	return 0;
}
