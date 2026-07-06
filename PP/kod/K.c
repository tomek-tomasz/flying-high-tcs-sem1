#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(){
    int z,n,m;
    scanf("%d", &z);
    for(int s=0;s<z;s++){
        scanf("%d %d", &n, &m);
        int *T = malloc(n * sizeof(int));
        int *A = malloc(n * sizeof(int));
        int *B = malloc(n * sizeof(int));
        int *P = malloc(m * sizeof(int));
        for(int i = 0; i < n; i++){
            scanf("%d", T + i);            
        }

        memset(P,-1,m*sizeof(int)); 
        int pointer=0;
        for (int i = 0; i < n; i++){
            int last_pos = *(P + *(T + i));
            if(last_pos >= pointer)pointer = last_pos + 1;
            *(B + i) = i - pointer + 1;
            *(P + *(T + i))= i;
        }
        memset(P,n,m*sizeof(int));
        pointer = n - 1;
        for (int i = n-1; i >= 0; i--){
            int next_pos = *(P + *(T + i));
            if(next_pos <= pointer) pointer = next_pos - 1;
            *(A + i) = pointer - i + 1; 
            *(P + *(T + i))= i;
        }
        // for (int i = 0; i < n; i++){
        //     int counter=0;
        //     for (int j = i+1; j<n; j++){
        //         if (*(P + *(T + j)) == 1) break;
        //         else{
        //             *(P + *(T + j))=1;
        //             counter++;
        //         } 
        //     }
        //     *(B + i)=counter;
        //     for (int k = 0; k < m; k++){
        //         *(P + k)=0;
        //     }
        //     counter=0;
        //     for (int j = 1; j<=i; j++){
        //         if (*(P + *(T + i - j)) == 1) break;
        //         else{
        //             *(P + *(T + i - j))=1;
        //             counter++;
        //         } 
        //     }
        //     *(A + i)=counter;
        //     for (int k = 0; k < m; k++){
        //         *(P + k)=0;
        //     }
        // }
        int wynik=0;
        int max=-1;
        int L=0;
        int R=0;
        for (int i=2; i < n; i++){
            int current_L=0;
            if(i > 0) current_L = *(B + i - 1);
            int current_R=0;
            if(i < n - 1) current_R = *(A + i + 1);

            if (current_L + current_R > max){
                max=current_L + current_R;
                wynik=i;
                L=current_L;
                R=current_R; 
            }
        
        }  
        printf("%d %d %d\n", wynik, L,R);
        free(T);
        free(A);
        free(B);
        free(P);
    }
    return 0;    
}