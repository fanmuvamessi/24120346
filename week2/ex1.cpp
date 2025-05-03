#include<iostream>
using namespace std;
int linearSearch(int a[], int n, int l) {
	for (int i = 0; i < n; i++) {
		if (a[i] == l) {
			return i; 
		}
	}
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
	cout << linearSearch(a, n, k);
	return 0;
}