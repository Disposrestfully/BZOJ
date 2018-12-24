#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
inline int ReadInt() {
    static int n, ch;
    n = 0, ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}

const int MAX_N = 10 + 2, MAX_V = 50;
const int LCM = 2520, MAX_COST = LCM * 2 * MAX_N;
const double INF = 1e50, eps = 1e-8;

int n, lim_x[MAX_N], lim_y[MAX_N], time_cost[MAX_V], L;

double dp[MAX_N][MAX_N][MAX_COST];

inline double cal(int v) {
    return (double)L / (80 - 0.03 * v * v);
}

inline void tension(double &a, const double &b) {
    if (b < a) a = b;
}

inline int dcmp(const double &a) {
    return fabs(a) < eps ? 0 : (a < 0 ? -1 : 1);
}

void solve() {
    int x1 = ReadInt() - 1, y1 = ReadInt() - 1, x2 = ReadInt() - 1, y2 = ReadInt() - 1, t1 = ReadInt(), t2 = ReadInt();
    int dx = x2 - x1 > 0 ? 1 : -1, dy = y2 - y1 > 0 ? 1 : -1;
    int delta_x = abs(x1 - x2), delta_y = abs(y1 - y2);
    dp[0][0][0] = 0;
    for (int i = 0; i <= delta_x; ++i)
        for (int j = 0; j <= delta_y; ++j)
            for (int t = 0; t < MAX_COST; ++t) if (dp[i][j][t] != INF) {
                static int x, y, rx, ry;
                x = i + 1, y = j;
                if (x <= delta_x) {
                    ry = y1 + y * dy;
                    for (int v = 1; v * 5 <= lim_x[ry] && t + time_cost[v] < MAX_COST; ++v)
                        tension(dp[x][y][t + time_cost[v]], dp[i][j][t] + cal(v * 5));
                }
                x = i, y = j + 1;
                if (y <= delta_y) {
                    rx = x1 + x * dx;
                    for (int v = 1; v * 5 <= lim_y[rx] && t + time_cost[v] < MAX_COST; ++v)
                        tension(dp[x][y][t + time_cost[v]], dp[i][j][t] + cal(v * 5));
                }
            }
    int min_time = -1, min_oil = -1;
    for (int t = 0; t < MAX_COST; ++t) if (dp[delta_x][delta_y][t] != INF) {
        double ti = (double)t * L / LCM * 12;
        if (dcmp(ti - t1) >= 0 && dcmp(t2 - ti) >= 0) {
            if (min_time == -1) min_time = t;
            if (min_oil == -1) min_oil = t;
            else if (dcmp(dp[delta_x][delta_y][t] - dp[delta_x][delta_y][min_oil]) == -1) min_oil = t;
        }
    }
    if (min_time == -1) return puts("No"), void();
    printf("%d %.2lf\n", (int)ceil((double)min_time * L / LCM  * 12), dp[delta_x][delta_y][min_time]);
    printf("%d %.2lf\n", (int)ceil((double)min_oil * L / LCM * 12), dp[delta_x][delta_y][min_oil]);
}

int main() {
    n = ReadInt(), L = ReadInt();
    for (int i = 0; i < n; ++i) lim_x[i] = ReadInt();
    for (int i = 0; i < n; ++i) lim_y[i] = ReadInt();
    for (int i = 1; i <= MAX_V / 5; ++i) time_cost[i] = LCM / i;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int t = 0; t < MAX_COST; ++t)
                dp[i][j][t] = INF;
    solve();
    return 0;
}

