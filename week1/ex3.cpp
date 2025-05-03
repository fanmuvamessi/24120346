#include<iostream>
#include<string>
using namespace std;
int N; string st="\0";
void generateBinaryStrings(int n, string str)
{
	if (str.length() == n)
	{
		cout << str << endl;
		return;
	}
	for (char i = '0'; i <= '1'; i++)
	{
		str += i;
		generateBinaryStrings(n, str);
		str.pop_back();
	}
}
int main()
{
	cin >> N;
	generateBinaryStrings(N, st);
	return 0;
}