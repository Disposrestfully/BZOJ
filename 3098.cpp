#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int main(){
	int n=100000,l=20;
	printf("%d %d\n",n,l);
	for (int i=1;i<=n;++i)
		putchar(rand()%26+'a');
	puts("");
	return 0;
}
