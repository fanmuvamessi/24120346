#include<iostream>
#include<time.h>
#include<fstream>
using namespace std;

int find_min(int a[], int pos, int n, long long &dem)
{
	int ans = pos;
	for (int i = pos + 1; i < n; i++)
	{
	    dem=dem+2;
		if (a[ans] > a[i])
		{
			ans = i;
		}
	}
	return ans;
}
void selectionsort(int a[], int n,long long &dem)
{
	int pos = 0;
	while (pos < n)
	{
	    dem++;
		swap(a[find_min(a, pos, n, dem)], a[pos]);
		pos++;
	}
	dem++;
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
	selectionsort(a, n,dem);
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
