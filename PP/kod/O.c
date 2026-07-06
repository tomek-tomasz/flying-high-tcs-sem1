#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

struct ruch{
    int x;
    int y;
}; typedef struct ruch ruch;




int backtracking(int n, int m, int M[n][m], int Pom[n][m], int p, ruch P[p],  int a, int b, int k, int c){
    if(M[a][b]==1) k--;
    if(k==0){
        Pom[a][b] = c;
        return 1;
    }
    M[a][b] += 3;
    for(int r = 0; r<p; r++){
        int r_x = a+P[r].x;
        int r_y = b+P[r].y;
        if(r_x>=0 && r_x<n && r_y>=0 && r_y<m && M[r_x][r_y]!=2 && M[r_x][r_y]<3){
            if(backtracking(n, m, M, Pom, p, P, r_x, r_y, k, c+1)==1){
                Pom[a][b] = c;
                return 1;
            }
        }
    }
    M[a][b] -= 3;
    return 0;
}

int main(){
    int z,p,n,m,a,b;
    scanf("%d", &z);
    for(int s=0;s<z;s++){
        scanf("%d", &p);
        ruch P[p];
        for(int i = 0; i<p; i++){
            int x,y;
            scanf("%d %d", &x, &y);
            P[i].x=x;
            P[i].y=y;
        }
        scanf("%d %d %d %d", &n, &m, &a, &b);
        int M[n][m];
        int k=0;
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                scanf("%d", &M[i][j]);
                if(M[i][j]==1) k++;
            }
        }
        int Pom[n][m];
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m;j++) Pom[i][j] = 0;
        }
        if(backtracking(n, m, M, Pom, p, P, a-1, b-1, k, 1) == 0) printf("NIE\n");
        else{
            printf("TAK\n");
            for(int i = 0; i<n; i++){
                for(int j = 0; j<m; j++) printf("%d ", Pom[i][j]);
                printf("\n");
            }
            
        }
    }
    return 0;    
}