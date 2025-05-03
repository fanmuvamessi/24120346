#include<iostream>
#include<time.h>
#include<fstream>
using namespace std;

void bubblesort(int a[], int n, long long &dem)
{
    for(int i=0;i<n-1;i++)
    {
        dem++;
        for(int j=i+1;j<n;j++)
        {
            dem=dem+2;
            if(a[i]>a[j])
                swap(a[i],a[j]);
        }
    }
}

int main()
{
    int n;
    long long dem=0;
    ifstream fin("input.txt");
    fin>>n;
    int a[n];
    for(int i=0;i<n;i++)
        fin>>a[i];
    fin.close();
    clock_t begin = clock();
    bubblesort(a, n, dem);
    clock_t end = clock();
    ofstream fout("output.txt", ios::app);
    //fout<<"Time run: "<<(float)(end-begin)/CLOCKS_PER_SEC<<endl;
    //fout<<"So lan so sanh: "<<dem<<endl;
    for(int i=0;i<n;i++)
        fout<<a[i]<<' ';
    fout<<endl;
    fout.close();
}
