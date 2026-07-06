#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


void bin(int r, unsigned long long x, char T[r+1]){
    T[r]='\0';
    for(int j=r-1 ;j>=0;j--){
        //printf("x=%llu\n",x);
        T[j] = (x & 1) + '0';
        x=x>>1;
    }
}
 


int main(){
    char J[65536];
    for(int i=0;i<65536;i++){
        J[i]=__builtin_popcount(i);
    }
    int z;
    scanf("%d",&z);
    int n,m,t,u,k;
    for(int j=0;j<z;j++){
        scanf("%d %d %d %d %d",&n,&m,&t,&u,&k);
        char T[n][m+1];
        for(int i=0;i<n;i++){
            scanf("%s",T[i]);
        }
        //printf("%d %d %d %d %d\n",n,m,t,u,k);
        //for(int i=0;i<n;i++){
        //    printf("%s\n",T[i]);
        //}
        int w[n];
        for(int v=0;v<n;v++) w[v]=0;
        for(int p=0;p<n;p++){
            for(int q=p+1;q<n;q++){
                int counter=0;
                int r=0;
                while(r<m){
                    int e=0;
                    unsigned short int np=0,nq=0;
                    while(e<16){
                        if(T[p][r+e]=='\0') break;
                        np = np*2+(T[p][r+e]-'0');
                        nq = nq*2+(T[q][r+e]-'0');
                        e++;
                    }
                    unsigned short int A = (np & nq);
                    counter+=J[A];
                    r+=16;
                }
                if(counter>=t){
                    w[p]++;
                    w[q]++;
                }
            }
        }   
        int uni=0;     
        for(int c=0;c<n;c++){
            if(w[c]>=u) uni++;
        }
        printf("%d ",uni);
        long long wynik = 1;
        while(k>0){
            if(k & 1) wynik=wynik*uni%1000;
            uni=uni*uni%1000;
            k=k>>1;
        }
        if(wynik<10) printf("00");
        else if(wynik<100) printf("0");
        printf("%lld\n",wynik);

    }
    return 0;
}