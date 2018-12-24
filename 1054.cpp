#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
char c[5];
int vis[20][20][20][20]={0};
int s[5],t[5];
struct node{
	int p[5],time;
}a[100010];
int main(){
	for (int i=1;i<=4;++i){
		scanf("%s",c);
		for (int j=0;j<=3;++j)
			s[i]+=(1<<(3-j))*(c[j]-'0');
		a[1].p[i]=s[i];
	}
//	printf("%d %d %d %d %d\n",a[1].p[1],a[1].p[2],a[1].p[3],a[1].p[4],a[1].time);
	a[1].time=0;
	//printf("%d %d %d %d %d\n",a[1].p[1],a[1].p[2],a[1].p[3],a[1].p[4],a[1].time);
	vis[a[1].p[1]][a[1].p[2]][a[1].p[3]][a[1].p[4]]=1;
	for (int i=1;i<=4;++i){
		scanf("%s",c);
		for (int j=0;j<=3;++j)
			t[i]+=(1<<(3-j))*(c[j]-'0');
	}
	int f=0,l=1;
	while (f<l){
		f++;
		//printf("%d %d %d %d %d\n",a[f].p[1],a[f].p[2],a[f].p[3],a[f].p[4],a[f].time);
		if (a[f].p[1]==t[1] && a[f].p[2]==t[2] && a[f].p[3]==t[3] && a[f].p[4]==t[4]){
			printf("%d\n",a[f].time);
			return 0;
		}
		for (int i=1;i<=4;++i){
			for (int j=0;j<=3;++j){
				if (a[f].p[i]&(1<<j)){
					if (i-1>0 && !(a[f].p[i-1]&(1<<j))){
						a[++l]=a[f];
						a[l].p[i-1]+=(1<<j);
						a[l].p[i]-=(1<<j);
						a[l].time++;
						if (vis[a[l].p[1]][a[l].p[2]][a[l].p[3]][a[l].p[4]]) l--;
						else vis[a[l].p[1]][a[l].p[2]][a[l].p[3]][a[l].p[4]]=1;
					}
					if (j-1>=0 && !(a[f].p[i]&(1<<(j-1)))){
						a[++l]=a[f];
						a[l].p[i]+=(1<<(j-1));
						a[l].p[i]-=(1<<j);
						a[l].time++;
						if (vis[a[l].p[1]][a[l].p[2]][a[l].p[3]][a[l].p[4]]) l--;
						else vis[a[l].p[1]][a[l].p[2]][a[l].p[3]][a[l].p[4]]=1;
					}
					if (i+1<=4 && !(a[f].p[i+1]&(1<<j))){
						a[++l]=a[f];
						a[l].p[i+1]+=(1<<j);
						a[l].p[i]-=(1<<j);
						a[l].time++;
						if (vis[a[l].p[1]][a[l].p[2]][a[l].p[3]][a[l].p[4]]) l--;
						else vis[a[l].p[1]][a[l].p[2]][a[l].p[3]][a[l].p[4]]=1;	
					}
					if (j+1<=3 && !(a[f].p[i]&(1<<(j+1)))){
						a[++l]=a[f];
						a[l].p[i]+=(1<<(j+1));
						a[l].p[i]-=(1<<j);
						a[l].time++;
						if (vis[a[l].p[1]][a[l].p[2]][a[l].p[3]][a[l].p[4]]) l--;
						else vis[a[l].p[1]][a[l].p[2]][a[l].p[3]][a[l].p[4]]=1;
					}
				}	
			}
		}		
	}
	return 0;
}

