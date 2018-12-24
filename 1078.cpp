#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<sys/mman.h>
#define y1 Y1
#define read() Inputs::Read()
#define lowbit(i) i&(-i)
using namespace std;
typedef long long ll;
const int N=55;
namespace Inputs{
    char* s;
    int a[24];
    void io(){s=(char*)mmap(NULL,1 << 26 ,PROT_READ,MAP_PRIVATE,fileno(stdin),0);}
    void scan(char* u){
        while(*s<48)
            ++s;
        while(*s>32)
            *u++=*s++;
        *u=0;
    }
    int Read(){
        int Hibiki=0,v=1;
        while(*s<48)
            v=*s++^45?1:-1;
        while(*s>32)
            Hibiki=Hibiki*10+*s++-48;
        return Hibiki*v;
    }
};
int next[N][2];
int fa[N],n;
int sta[N],top;
int main(){
	//freopen("1.in","r",stdin);
	Inputs::io();
	n=read();
	for (int i=1;i<=n;++i){
		int x=read()+1;
		if (x>100){
			x-=100;
			next[x][1]=i+1;	
		}else next[x][0]=i+1;
		fa[i+1]=x;
	}
	++n;
	/*for (int i=1;i<=n;++i)
		printf("%d %d\n",next[i][0],next[i][1]);*/
	int rt=1;
	while (n--){
		int pos=0;
		for (int i=rt;i;i=next[i][0])
			if (!next[i][1]){
				pos=i;
				break;
			}
		if (next[pos][0] && !next[next[pos][0]][0]) pos=next[pos][0];
		if (next[pos][0]) fa[next[pos][0]]=fa[pos];
		if (fa[pos]) next[fa[pos]][0]=next[pos][0];
		sta[++top]=pos-1;
		if (pos==rt){
			rt=next[pos][0];
			continue;
		}
		for (int i=fa[pos];i;i=fa[i])
			swap(next[i][0],next[i][1]);
	}
	for (int i=top;i>=1;--i)
		printf("%d ",sta[i]);
	printf("\n");
	return 0;
}
