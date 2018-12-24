#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int read(){
    int x=0,w=1;
    char ch=0;
    while (ch<'0' || ch>'9'){
          if (ch=='-') w=-1;
          ch=getchar();
    }
    while (ch<='9' && ch>='0'){
          x=(x<<1)+(x<<3)+ch-'0';
          ch=getchar();
    }
    return x*w;
}
const int N=2e5+5; 
char s[N],ch;
int Rank[N],sa[N];
int c[N],x[N],y[N];
int n,m,k;
int height[N],nxt[N];
void build(){
    ++n;
    for (int i=0;i<m;++i) c[i]=0;
    for (int i=0;i<n;++i) ++c[x[i]=s[i]];    
    for (int i=1;i<m;++i) c[i]+=c[i-1];
    for (int i=n-1;i>=0;--i) sa[--c[x[i]]]=i;
    for (int k=1;k<=n;k<<=1){
        int cnt=0;
        for (int i=n-k;i<n;++i) y[cnt++]=i;
        for (int i=0;i<n;++i) 
            if (sa[i]>=k) y[cnt++]=sa[i]-k; 
        for (int i=0;i<m;++i) c[i]=0;
        for (int i=0;i<n;++i) ++c[x[y[i]]];
        for (int i=1;i<m;++i) c[i]+=c[i-1];
        for(int i=n-1;i>=0;--i){
            sa[--c[x[y[i]]]]=y[i];
            //y[i]=0;
        }
        swap(x,y);
        cnt=1;x[sa[0]]=0;
        for (int i=1;i<n;++i)
            if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k])
                x[sa[i]]=cnt-1;
            else x[sa[i]]=cnt++;    
        if (cnt>=n) break;
        m=cnt;
    }
}
int main(){
	scanf("%s",s);
	n=strlen(s);
	int l=n;
	for (int i=0;i<n;++i){
		s[i+n]=s[i];
		m=max(m,s[i]-'\0');	
	}
	++m;
	n<<=1;
	s[n]=0;
	build();
	for (int i=0;i<n;++i)
		if (sa[i]<l) printf("%c",s[sa[i]+l-1]);
	printf("\n");
    return 0;
}



