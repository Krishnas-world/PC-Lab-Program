#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int *a, int l, int m, int r){
    int n1=m-l+1,n2=r-m,i=0,j=0,k=l;
    int *L=malloc(n1*sizeof(int)),*R=malloc(n2*sizeof(int));
    for(int x=0;x<n1;x++)L[x]=a[l+x];
    for(int x=0;x<n2;x++)R[x]=a[m+1+x];
    while(i<n1&&j<n2) a[k++]=L[i]<R[j]?L[i++]:R[j++];
    while(i<n1) a[k++]=L[i++];
    while(j<n2) a[k++]=R[j++];
    free(L); free(R);
}
void sort(int *a,int l,int r,int d){
    if(l>=r) return;
    int m=(l+r)/2;

    if(d){
        #pragma omp parallel sections
        {
            #pragma omp section
            { sort(a,l,m,d-1); }

            #pragma omp section
            { sort(a,m+1,r,d-1); }
        }
    } else {
        sort(a,l,m,0);
        sort(a,m+1,r,0);
    }

    merge(a,l,m,r);
}

int main(){
    int n=500000;
    int *a=malloc(n*sizeof(int)), *b=malloc(n*sizeof(int));
    for(int i=0;i<n;i++) a[i]=b[i]=rand();

    double t=omp_get_wtime();
    sort(a,0,n-1,0);
    printf("Seq: %f\n", omp_get_wtime()-t);

    t=omp_get_wtime();
    sort(b,0,n-1,2);
    printf("Par: %f\n", omp_get_wtime()-t);

    free(a); free(b);
}
