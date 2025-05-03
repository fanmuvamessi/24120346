#include<iostream>
using namespace std;
int N;
int fibonaci(int n)
{
	if (n < 0)
		return -1;
	if (n == 1)
		return 1;
	if (n == 0)
		return 0;
	return (fibonaci(n - 1) + fibonaci(n - 2));
}
int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		cout << fibonaci(i) << ' ';
	return 0;
}