#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

	static const int MAXN = 100000;
	int tree[30][MAXN];
	int sorted[MAXN];
	int toleft[30][MAXN];

	void build(int l, int r, int dep)
	{
		if (l == r)return;
		int mid = (l + r) >> 1;// >>*
		int same = mid - l + 1;
		for (int i = l; i <= r; i++) if (tree[dep][i] < sorted[mid])same--;
		int lpos = l;
		int rpos = l + mid;
		for (int i = l; i <= r; i++)
		{
			if (tree[dep][i] < sorted[mid])
				tree[dep + 1][lpos++] = tree[dep][i];
			else if (tree[dep][i] == sorted[mid] && same>0)
			{
				tree[dep + 1][lpos++] = tree[dep][i];
				same--;
			}
			else tree[dep + 1][rpos++] = tree[dep][i];
			toleft[dep][i] = toleft[dep][l - 1] + lpos - l;

		}
		build(l, mid, dep + 1);
		build(mid + 1, r, dep + 1);
	}
	int query(int L, int R, int l, int r, int dep, int k)
	{
		if (l == r)return tree[dep][l];
		int mid = (L + R) >> 1;
		int cnt = toleft[dep][r] - toleft[dep][l - 1];
		if (cnt >= k)
		{
			int newl = L + toleft[dep][l - 1] - toleft[dep][L - 1];
			int newr = newl + cnt - 1;
			return query(L, mid, newl, newr, dep + 1, k);

		}
		else
		{
			int newr = r + toleft[dep][R] - toleft[dep][r];
			int newl = newr - (r - 1 - cnt);
			return query(mid + 1, R, newl, newr, dep + 1, k - cnt);
		}
	}
