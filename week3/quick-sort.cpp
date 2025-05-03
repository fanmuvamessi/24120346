#include<iostream>
#include<vector>
#include<time.h>
#include<fstream>
using namespace std;

int parti(vector<long long>& arr, int low, int high, long long &dem)
{
    int pivot = arr[(int)rand()%(high-low+1)+low];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        dem=dem+2;
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(vector<long long>& arr, int low, int high, long long &dem)
{
    dem++;
    if (low < high)
    {
        int pivotIndex = parti(arr, low, high, dem);
        quickSort(arr, low, pivotIndex - 1, dem);  // Sort left part
        quickSort(arr, pivotIndex + 1,high, dem); // Sort right part
    }
}

int main()
{

    int n, a;
    long long dem=0;
    ifstream fin("input.txt");
    fin >> n;
    vector<long long> arr;
    for (int i = 0; i < n; i++)
    {
        fin >> a;
        arr.push_back(a);
    }
    fin.close();
    clock_t begin = clock();
    quickSort(arr, 0, n-1,dem);
    clock_t end = clock();
    ofstream fout("output.txt", ios::app);
	//fout<<"Time run: "<<(float)(end-begin)/CLOCKS_PER_SEC<<endl;
	//fout<<"So lan so sanh: "<<dem<<endl;
	for(int i=0;i<n;i++)
        fout<<a[i]<<' ';
    fout<<endl;
    fout.close();
}
