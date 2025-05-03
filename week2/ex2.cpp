#include<iostream>
using namespace std;

int sentinelLinearSearch(int a[], int n, int k) 
{
	int ans = a[n - 1]; 
	a[n - 1] = k; 
	int i = 0;
	while (a[i] != k)
	{
			i++;
	}
	a[n - 1] = ans; 
	if (i < n - 1 || a[n - 1] == k)
		return i;
	return -1;
}
int main()
{
	int n, k;
	cin >> n;
	int a[1000];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> k;
	cout << sentinelLinearSearch(a, n, k);
	return 0;
}