#include<iostream>
using namespace std;

int binary(int a[], int n, int x) 
{
    int l = 0, r = n - 1;
    while (l <= r) 
    {
        int m = (l + r) / 2;
        if (a[m] == x)
            return m;
        else if (a[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1; 
}

void findd(int a[],int n,int target)
{
    int checkk[10000], x;
    memset(checkk,0, sizeof checkk);
    for (int i = 0; i < n; i++)
    {
        x = target - a[i];
        //cout << a[i]<<' ';
        //cout << checkk[a[i]]<<' '<<binary(a, n, x)<<' ';
        int ok = binary(a, n, x);
        if (checkk[a[i]] == 0 && ok >= 0 && ok != i)
        {
            cout << "YES";
            return;
        }
        else
            checkk[a[i]] = 1;
    }
    cout << "NO";
}

int main()
{
    int n, a[10000], target;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> target;
    findd(a, n, target);
    return 0;
}
