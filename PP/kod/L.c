#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(){
    int z,n1,n2,m1,m2;
    scanf("%d", &z);
    for(int s=0;s<z;s++){
        scanf("%d %d",&n1,&n2);
        int **N = malloc(n1 * sizeof(int*));
        for(int i = 0; i < n1; i++){
            *(N + i) = malloc(n2 * sizeof(int));
            for(int j = 0; j < n2; j++) scanf("%d", *(N + i) + j);
        }

        scanf("%d %d",&m1,&m2);
        if(n2!=m1){
            int kosz;
            for(int i = 0; i < m1*m2; i++) scanf("%d",&kosz);
            for(int i = 0; i < n1; i++) free(*(N+i));
            free(N);
            printf("ERROR\n");
            continue;
        }
        int **M = malloc(m1 * sizeof(int*));
        for(int i = 0; i < m1; i++){
            *(M + i) = malloc(m2 * sizeof(int));
            for(int j = 0; j < m2; j++) scanf("%d", *(M + i) + j);
        }
        int n = n1;
        int m = m2;
        int v = n2;
        int **C = malloc(n1*sizeof(int*));
        for(int i = 0; i < n1; i++){
            *(C + i) = calloc(m,sizeof(int));
        }
        for(int i = 0; i < n; i++){
            for(int k = 0; k < v; k++){
                for(int j = 0; j < m; j++){
                    int n_ik = *(*(N + i) + k);
                    int m_kj = *(*(M + k) + j);
                    *(*(C + i) + j) = (*(*(C + i) + j) + (n_ik * m_kj)) % 1000;
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int val = *(*(C+i)+j);
                if(val<100)printf("0");
                if(val<10)printf("0");
                printf("%d ", val);
            }
            printf("\n");
        }
        for(int i = 0; i < n1; i++){
            free(*(N+i));
            free(*(C+i));
        }
        for(int i = 0; i < m1; i++) free(*(M+i));
        free(N);
        free(M);
        free(C);
        
    }
    return 0;    
}