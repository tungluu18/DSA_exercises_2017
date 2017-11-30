#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;

const int maxN = 111111;
int a[maxN], n;
int b[maxN]; //temporary array used in radix sort and merge sort

void binaryRadixSort(int a[], int n) {
    for (int log=0; log<20; ++log) {
        int counting[2] = {0,0};
        for (int i=0; i<n; ++i) counting[(a[i]>>log)&1]++;
        counting[1] += counting[0];
        for (int i=n-1; i>=0; --i) {
            b[--counting[(a[i]>>log)&1]] = a[i];
        }
        for (int i=0; i<n; ++i) a[i] = b[i];
    }
}

void quickSort(int a[], int l, int r) {
    if (l>=r) return;
    int pivot = l+rand()%(r-l+1);
    int key = a[pivot];
    int i=l, j=r;
    while (i<=j) {
        while (i<=r && a[i]<key) ++i;
        while (j>=l && a[j]>key) --j;
        if (i<=j) swap(a[i++],a[j--]);
    }
    quickSort(a,l,j);
    quickSort(a,i,r);
}

void mergeSort(int a[], int l, int r) {
    if (l==r) return;
    int mid=(l+r)>>1;
    mergeSort(a,l,mid), mergeSort(a,mid+1,r);
    for (int bi=l,i=l,j=mid+1; bi<=r; ++bi) {
        if (i>mid) b[bi] = a[j++];
        else if (j>r) b[bi] = a[i++];
        else b[bi] = (a[i]<a[j] ? a[i++] : a[j++]);
    }
    for (int i=l; i<=r; ++i) a[i] = b[i];
}

int main() {
    freopen("a.txt", "r", stdin);
    srand(time(NULL));
    cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i];

    //mergeSort(a,0,n-1);
    //quickSort(a,0,n-1);
    //binaryRadixSort(a,n);

    for (int i=0; i<n; ++i) cout << setw(3) << a[i];
}

