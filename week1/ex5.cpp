#include <iostream>
using namespace std;
bool isSorted (int arr[], int n) {
	if (n == 1 || n == 0)
		return true;
	if (arr[0] > arr[1])
		return false;
	return isSorted(arr + 1, n - 1);
}
int main() {
	int n;
	cin >> n;
	int arr[100];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	if (isSorted(arr, n))
		cout << "The array is sorted." << endl;
	else
		cout << "The array is NOT sorted." << endl;
	return 0;
}