#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>




int NWD(int a, int b){
    if(b == 0) return a;
    if(a == 0) return b;
    if(a == b) return a;
    int r_a = a&1;
    int r_b = b&1;
    if(r_a == 1 && r_b == 1) return b<a ? NWD(b, (a-b)>>1) : NWD(a, (b-a)>>1);
    if(r_a == 1 && r_b == 0) return NWD(a, b>>1);
    if(r_a == 0 && r_b == 1) return NWD(a>>1, b);
    if(r_a == 0 && r_b == 0) return NWD(a>>1, b>>1)<<1; 

}


int main(){
    int z,a,b;
    scanf("%d", &z);
    for(int s=0;s<z;s++){
        scanf("%d %d", &a, &b);
        printf("%d\n", NWD(a,b));
    }
    return 0;    
}