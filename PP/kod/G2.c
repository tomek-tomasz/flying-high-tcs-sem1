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


void write(int r, long long x,  char T[r+1]){
    long long max = (1LL<<(r-1))-1;
    long long min = -(1LL<<(r-1));
    if (r!=64 && (x > max || x < min)){
        T[0] = '\0';
        return;
    }
    if(x<0){
        unsigned long long y = (1ULL<<r)+x;
        bin(r, y, T);
    }else bin(r, (unsigned long long)x, T);
}


long long read(char n[65]){
    int len = strlen(n);
    if(n[0] == '0'){
        long long number=0;
        int i=0;
        while(n[i] != '\0'){
            number = number*2 + (n[i] - '0');
            i++;
        }
        return number;
    }
    else{
        long long pom=0;
        int i=1;
        while(n[i] != '\0'){
            pom = pom*2 + (n[i] - '0');
            i++;
        }
        long long odwr = (1ULL<<(len-1))-pom;
        return -odwr;
    }
}


int main(){
    int z;
    scanf("%d",&z);
    char s[10],n[65],T[65];
    int r;
    long long x;
    for(int m=0;m<z;m++){
        scanf("%s",s);
        if(strcmp(s, "WRITE") == 0){
            scanf("%d %lld",&r,&x);
            write(r,x,T);
            if(T[0] == '\0') printf("ERROR\n");
            else printf("%s\n",T);
        }
        else if(strcmp(s, "READ") == 0){
            scanf("%s",n);
            long long wynik=read(n);
            printf("%lld\n",wynik);
        }
    }
    return 0;
}