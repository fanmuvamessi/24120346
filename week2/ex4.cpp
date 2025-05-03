#include<iostream>
using namespace std;
int s = 0;

int findDays(int a[],int n, int cap) {
    int days = 1; 
    int w = 0;
    for (int i = 0; i < n; i++) {
        if (w + a[i] > cap) {
            days += 1;
            w = a[i]; 
        }
        else {
            w += a[i];
        }
    }
    return days;
}

int leastWeight(int a[],int n, int d) {
    int low = 0, high = s;
    for (int i = 0; i < n; i++)
        if (low < a[i])
            low = a[i];
    while (low <= high) {
        int mid = (low + high) / 2;
        int numberOfDays = findDays(a,n, mid);
        if (numberOfDays <= d)
            high = mid - 1;
        else 
            low = mid + 1;
    }
    return low;
}

int main()
{
    int a[100000], n, d;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		s += a[i];
	}
	cin >> d;
    cout << leastWeight(a, n, d);
    return 0;
}