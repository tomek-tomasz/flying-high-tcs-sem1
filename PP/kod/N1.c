#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>







int main(){
    int z,a,b;
    scanf("%d", &z);
    for(int s=0;s<z;s++){
        scanf("%d %d", &a, &b);
        int v2=0;
        while(a != b){
            if(b == 0) b = a;
            if(a == 0) a = b;
            int r_a = a&1;
            int r_b = b&1;
            if(r_a == 1 && r_b == 1){
                if(b<a){
                    int pom=a;
                    a=b;
                    b=(pom-b)>>1;
                }
                else{
                    int pom=b;
                    b=a;
                    a=(pom-a)>>1;
                }
            }
            if(r_a == 1 && r_b == 0) b = b>>1;
            if(r_a == 0 && r_b == 1) a = a>>1;
            if(r_a == 0 && r_b == 0){
                a = a>>1;
                b = b>>1;
                v2++;
            } 
        }
        printf("%d\n", (a << v2));
    }
    return 0;    
}