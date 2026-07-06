#include<stdio.h>
#include<string.h>
#include<ctype.h>


void convert(int p, int q, char n[61]){
    long long number=0;
    int i=0;
    while(n[i] != '\0'){
        if(isdigit(n[i])){
            number = number * p + (n[i] - '0');
        }
        else if(isalpha(n[i])){
            number = number * p + (n[i] - 'A' + 10);
        }
        i++;
    }
    int j=0;
    if(number == 0){
        n[0] = '0';
        n[1] = '\0';
        return;
    }
    n[0]='\0';
    while(number > 0){
        int rem = number % q;
        for(int k=j+1;k>0;k--){
            n[k] = n[k-1];
        }
        if(rem < 10){
            n[0] = rem + '0';
        }
        else{
            n[0] = rem - 10 + 'A';
        }
        number=number/q;
        j++;
    }
}



int main(){
    int z;
    scanf("%d",&z);
    char s[8],n[61];
    int p,q;
    for(int m=0;m<z;m++){
        scanf("%s %d %d %s",s,&p,&q,n);
        //printf("%s %d %d %s",s,p,q,n);
        convert(p,q,n);
        printf("%s\n",n);
    }
    return 0;
}