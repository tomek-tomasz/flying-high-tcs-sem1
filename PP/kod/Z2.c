#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>




struct pair{
    char *A;
    int count;
};
typedef struct pair pair;



int main(){
    int z;
    scanf("%d",&z);
    for(int m=1;m<=z;m++){
	    int n;
        scanf("%d",&n);
        char **T=(char **)malloc(n*sizeof(char*));
        for(int i=0;i<n;i++)T[i]=(char *)malloc(1001*sizeof(char));
        for(int i=0;i<n;i++){
            scanf("%s", T[i]);
            for(int c=0; T[i][c] != '\0'; c++) T[i][c] = (char)tolower(T[i][c]);
        }
        char **P = (char **)malloc(n * sizeof(char *));
        for (int i = 0; i < n; i++) {
            P[i] = T[i];
        }
        for(int gap=n/2; gap>0; gap/=2){
            for(int i=gap;i<n;i++){
                char *key = P[i];
                int j = i - gap;
                while (j >= 0 && strcmp(P[j], key) > 0) {
                    P[j + gap] = P[j];
                    j = j - gap;
                }
                P[j + gap] = key;
            }
        }
        pair *Z = (pair *)malloc(n * sizeof(pair));
        int k = 0;
        Z[0].A = P[0];
        Z[0].count = 1;

        for(int l=1;l<n;l++){
     	    if (strcmp(Z[k].A, P[l]) == 0) Z[k].count++;
     	    else{
     		    k++;
     		    Z[k].A=P[l];
     		    Z[k].count=1;    	
     	    }
        }
        int K=k+1;
        for(int gap=K/2; gap>0; gap/=2){
            for(int i=gap;i<K;i++){
                pair pom = Z[i];
                int j = i - gap;
                while ( j >= 0 && (Z[j].count < pom.count || (Z[j].count == pom.count && strcmp(Z[j].A, pom.A) > 0))){
                    Z[j + gap] = Z[j];
                    j = j - gap;
                }
                Z[j + gap] = pom;
            }
        }            
        printf("%d\n",k+1);
        for(int i=0; i<=k;i++){
     	    printf("%s %d\n", Z[i].A, Z[i].count);
    	    Z[i].count=0;
        }
        for (int i = 0; i < n; i++) {
            free(T[i]);
        }
        free(T);
        free(P);
        free(Z);
    }
    return 0;
}