
#include <bits/stdc++.h>
using namespace std;
const int maxn = 300010;
int in_LR[maxn];//in_LR == tot :在L,R之间 
int a[maxn], mx[maxn];
int main() {
	int n, tot = 0, L, R, ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		if(a[i] != 1) continue;
		mx[i] = 1;
		for (int j = i - 1; a[j] != 1 && j >= 1; j--)
			mx[j] = max(mx[j + 1], a[j]);
		for (int j = i + 1; j <= n && a[j] != 1; j++)
			mx[j] = max(mx[j - 1], a[j]);
		//处理最大值在左半边的情况
		tot++;
		L = i, R = i;
		while(in_LR[a[L]] != tot && L >= 1) {
			in_LR[a[L]] = tot;//放入R和L之间 
			L--;
		}
		for (L++; L <= i; in_LR[a[L++]] = tot - 1) {
			while(R > i && (R - L + 1 > mx[L] || mx[R] >= mx[L])) 
				in_LR[a[R--]] = tot - 1;
			while(R < n && R - L + 1 < mx[L]) {
				if(in_LR[a[R + 1]] == tot || a[R + 1] >= mx[L]) break;
				in_LR[a[++R]] = tot;
			}
			if(R - L + 1 == mx[L]) ans++;
		}
		//处理最大值在右半边的情况
		tot++;
		L = i, R = i;
		while(in_LR[a[R]] != tot && R <= n) {
			in_LR[a[R]] = tot;//放入R和L之间 
			R++;
		}
		for (R--; R > i; in_LR[a[R--]] = tot - 1) {
			while(L < i && (R - L + 1 > mx[R] || mx[L] >= mx[R])) 
				in_LR[a[L++]] = tot - 1;
			while(L > 1 && R - L + 1 < mx[R]) {
				if(in_LR[a[L - 1]] == tot || a[L - 1] >= mx[R]) break;
				in_LR[a[--L]] = tot;
			}
			if(R - L + 1 == mx[R]) ans++;
		}
	}
	printf("%d\n", ans);
}