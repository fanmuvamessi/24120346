#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<fstream>
using namespace std;

void countingSort(vector<int>& arr, int exp, int &dem)
{
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};
    for (int i = 0; i < n; i++)
    {
        dem++;
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++)
    {
        dem++;
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        dem++;
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    for (int i = 0; i < n; i++)
    {
        dem++;
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr, int &dem)
{
    int maxNum = *max_element(arr.begin(), arr.end());
    dem=dem+ arr.size();
    for (int exp = 1; maxNum / exp > 0; exp *= 10)
    {
        dem++;
        countingSort(arr, exp, dem);
    }
}

int main()
{
    int n, a, dem=0;
    ifstream fin("input.txt");
    fin >> n;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        fin >> a;
        arr.push_back(a);
    }
    fin.close();
    clock_t begin = clock();
    radixSort(arr,dem);
    clock_t end = clock();
    ofstream fout("output.txt", ios::app);
	//fout<<"Time run: "<<(float)(end-begin)/CLOCKS_PER_SEC<<endl;
	//fout<<"So lan so sanh: "<<dem<<endl;
	for(int i=0;i<n;i++)
        fout<<a[i]<<' ';
    fout<<endl;
    fout.close();
    return 0;
}

