#include<iostream>
using namespace std;
int N;
int factorial(int n)
{
	int ans = 1;
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}
int main()
{
	cin >> N;
	cout << factorial(N);
	return 0;
}