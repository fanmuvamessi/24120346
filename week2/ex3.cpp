#include<iostream>
using namespace std;

int binary(int a[], int n)
{
	if (a[0] <= a[n - 1])
		return a[0];
	int left = 0, right = n - 1;
	while (left < right)
	{
		int mid = (left + right) >> 1;
		if (a[0] <= a[mid])
			left = mid + 1;
		else
			right = mid;
	}
	return a[left];
}

int main()
{
	int n;
	cin >> n;
	int a[1000];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cout << binary(a, n);
	return 0;
}