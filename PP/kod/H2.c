#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
 


int main(){
    int z;
    scanf("%d",&z);
    int n,m,t,u,k;
    unsigned long long T[300][160];
    for(int j=0;j<z;j++){
        scanf("%d %d %d %d %d",&n,&m,&t,&u,&k);
        getchar();
        int blocks = (m+63)/64;
        for(int i=0;i<n;i++){
            for(int b=0;b<blocks;b++){
                T[i][b]=0;
            }
            for(int j=0;j<m;j++){
                char c = getchar();
                if(c=='1'){
                    T[i][j/64] |= (1ULL<<(j%64));
                }
            }
            getchar();
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
                for(int b=0;b<blocks;b++){
                    unsigned long long np=T[p][b],nq=T[q][b];
                    unsigned long long A = (np & nq);
                    counter+=__builtin_popcountll(A);
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
            uni=(uni%1000)*(uni%1000)%1000;
            k=k>>1;
        }
        if(wynik<10) printf("00");
        else if(wynik<100) printf("0");
        printf("%lld\n",wynik);

    }
    return 0;
}