#include<iostream>
#include<time.h>
#include<fstream>
using namespace std;

 void heapify(int arr[], int n, int i, int &dem)
 {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    dem=dem+5;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, dem);
    }
 }

void heapSort(int arr[], int n, int &dem)
{
    for (int i = n/2 - 1; i >= 0; i--)
    {
        dem++;
        heapify(arr, n, i, dem);
    }
    for (int i = n - 1; i > 0; i--)
    {
        dem++;
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, dem);
    }
 }

 int main()
{
    int n, dem=0;
    ifstream fin("input.txt");
    fin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        fin >> a[i];
    fin.close();
    clock_t begin = clock();
    heapSort(a,n,dem);
    clock_t end = clock();
    ofstream fout("output.txt", ios::app);
	//fout<<"Time run: "<<(float)(end-begin)/CLOCKS_PER_SEC<<endl;
	//fout<<"So lan so sanh: "<<dem<<endl;
	for(int i=0;i<n;i++)
        fout<<a[i]<<' ';
    fout<<endl;
	fout.close();
}
