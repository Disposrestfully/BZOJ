#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int MaxN = 20 + 5;

int n, m, Tot;
int Pow[MaxN];

void PrintCh(int x) {
	if (x < 10) printf("%d", x);
	else printf("%c", 'A' + x - 10);
} 

int main() 
{
	scanf("%d%d", &n, &m);
	Pow[0] = 1;
	for (int i = 1; i <= n; ++i) Pow[i] = Pow[i - 1] * m;
	Tot = Pow[n];
	int x, y;
	for (int i = 0; i < Tot; ++i) {
		for (int j = n - 1; j >= 0; --j) {
			x = i / Pow[n - j]; 
			y = (i / Pow[n - j - 1]) % m;
			if (x & 1) PrintCh(m - y - 1);
			else PrintCh(y);
		}
		printf("\n");
	}
	return 0;
}
