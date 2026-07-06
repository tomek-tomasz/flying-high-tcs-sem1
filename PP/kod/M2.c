#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

struct hobbit{
    int x;
    int y;
    char *imie;
};typedef struct hobbit hobbit;

int xcompare(const void* h1, const void* h2){
    return (*(hobbit*)h1).x - (*(hobbit*)h2).x;
}

int dystans(hobbit h1, hobbit h2){
    int delta_x = abs(h2.x-h1.x);
    return delta_x + abs(h1.y) + abs(h2.y);
}

void bsort(void *T, int n, int size, int cmp( const void *a, const void *b)){
    char change=1;
    int* a=malloc(size);
    for(int i=1;i<n && change;i++){
        change=0;
        for(int j=0;j<n-i;j++){
            if(cmp(T + size * j,T + size * (j+1))>0){
                memcpy(a,T + j * size, size);
                memcpy(T + j * size, T + (j + 1) * size, size);
                memcpy(T + (j + 1) * size, a, size);
                change=1;
            }
        }
    }
    free(a);
}

int main(){
    int z,n;
    scanf("%d", &z);
    for(int s=0;s<z;s++){
        scanf("%d",&n);
        char imie[n][11];
        hobbit H[n];
        for(int i = 0; i < n; i++){
            int x,y;
            scanf("%d %d %s", &x, &y, imie[i]);
            H[i].x=x;
            H[i].y=y;
            H[i].imie=imie[i];
        }
        //for(int i=0; i<n; i++)printf("%d %d %s\n", H[i].x, H[i].y, H[i].imie);
        bsort(H,n,sizeof(hobbit), xcompare);
        //for(int i=0; i<n; i++)printf("%d %d %s\n", H[i].x, H[i].y, H[i].imie);
        hobbit L[n];
        L[0]=H[0];
        int min_dystans = dystans(H[0],H[1]);
        hobbit min_h1 = H[0];
        hobbit min_h2 = H[1];
        for(int i = 1; i < n; i++){
            int dys_HL = dystans(H[i],L[i-1]);
            int dys_HH = dystans(H[i],H[i-1]);
            if(dys_HL < dys_HH){
                L[i] = L[i-1];
                if(dys_HL < min_dystans){
                    min_dystans = dys_HL;
                    min_h1 = H[i];
                    min_h2 = L[i];
                }
            }
            else{
                L[i]=H[i-1];
                if(dys_HH < min_dystans){
                    min_dystans = dys_HH;
                    min_h1 = H[i];
                    min_h2 = L[i];
                } 
                
            }
        }
        printf("%d\n%s %s\n", min_dystans, min_h1.imie, min_h2.imie);

    }
    return 0;    
}