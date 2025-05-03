#include<iostream>
#include<time.h>
#include<fstream>
using namespace std;

void merge1(int arr[], int left, int mid, int right, int &dem)
{
    int i = left, j = mid + 1, k = 0;
    int temp[right - left + 1];
    while (i <= mid && j <= right)
    {
        dem=dem+3;
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
            temp[k++] = arr[j++];
    }
    dem++;
    while (i <= mid)
    {
        dem++;
        temp[k++] = arr[i++];
    }
    while (j <= right)
    {
        dem++;
        temp[k++] = arr[j++];
    }
    dem=dem+2;
    for (int x = 0; x < k; x++)
    {
        dem++;
        arr[left + x] = temp[x];
    }
}

void mergeSort(int arr[], int left, int right, int &dem)
{
    dem++;
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, dem);
        mergeSort(arr, mid + 1, right, dem);
        merge1(arr, left, mid, right, dem);
    }
}



int main()
{
    int n, dem=0;
    ifstream fin("input.txt");
    fin>>n;
    int a[n];
    for(int i=0;i<n;i++)
        fin>>a[i];
    fin.close();
    clock_t begin = clock();
    mergeSort(a, 0, n - 1, dem);
    clock_t end = clock();
    ofstream fout("output.txt", ios::app);
	//fout<<"Time run: "<<(float)(end-begin)/CLOCKS_PER_SEC<<endl;
	//fout<<"So lan so sanh: "<<dem<<endl;
	for(int i=0;i<n;i++)
        fout<<a[i]<<' ';
    fout<<endl;
    fout.close();
}
