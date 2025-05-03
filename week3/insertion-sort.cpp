#include<iostream>
#include<time.h>
#include<fstream>
using namespace std;

void InsertionSort(int a[], int n,long long &dem)
{
    for (int i = 1; i < n; i++)
    {
        dem++;
        int ans=a[i];
        int j=i-1;
        while(j >= 0 && a[j] > ans)
        {
            dem=dem+2;
            a[j+1]=a[j];
            j=j-1;
        }
        dem++;
        a[j+1]=ans;
    }
}
int main()
{
    int n;
    long long dem=0;
    ifstream fin("input.txt");
    fin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        fin >> a[i];
    fin.close();
    clock_t begin = clock();
    InsertionSort(a,n,dem);
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
