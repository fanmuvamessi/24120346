#include<iostream>
using namespace std;

int twopointers(int a[], int n, int target)
{
	int minn = 10000000;
	int left = 0, s = 0;
	for (int right = 0; right < n; right++)
	{
		s += a[right];
		while (s >= target)
		{
			if (right - left + 1 < minn)
				minn = right - left + 1;
			s -= a[left];
			left++;
		}
	}
	if (minn <= n)
		return minn;
	return 0;
}

int main()
{
	int n, a[10000], target;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> target;
	cout<<twopointers(a, n, target);
	return 0;
}