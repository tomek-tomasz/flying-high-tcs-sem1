#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int K[32]={0,};
int P1[64]={0,};
int P2[64]={0,};

int backtracking(int n, int m, int k, int i, int flag){
    if(k==0){
        printf("TAK\n");
        return 1;
    }
    for(int j = 0; j<m; j++){
        if(K[j]==0 && P1[i-j+32]==0 && P2[i+j]==0){
            K[j]+=1;
            P1[i-j+32]+=1;
            P2[i+j]+=1;
            if(backtracking(n,m,k-1,i+1,flag)==1){
                if(flag) printf("%d %d\n",j+1,i+1);
                else printf("%d %d\n",i+1,j+1);
                return 1;
            }
            K[j]-=1;
            P1[i-j+32]-=1;
            P2[i+j]-=1;
        }
    }
    return 0;
}

int main(){
    int z,n,m,k,flag;
    scanf("%d", &z);
    for(int s=0;s<z;s++){
        for(int j=0;j<32;j++)K[j]=0;
        for(int j=0;j<64;j++){
            P1[j]=0;
            P2[j]=0;
        }
        scanf("%d %d %d", &n, &m, &k);
        if(k>n || k>m)printf("NIE\n");
        else{
            if(n>m)flag=backtracking(m,n,k,0,1);
            else flag = backtracking(n,m,k,0,0);
        }
        if(flag == 0) printf("NIE\n");
    }
    return 0;    
}