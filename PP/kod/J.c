#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h> 



int main(){
    int z;
    scanf("%d", &z);
    for(int m=0;m<z;m++){
        //printf("\n");
        int n,k;
        scanf("%d %d", &n, &k);
        //printf("%d %d\n", n, k);
        unsigned short int T[512]={0,};
        for(int i=0;i<n;i++){
            int rejestr;
            scanf("%d: ", &rejestr);
            //printf("%d: ", rejestr);
            char line[300];
            fgets(line, 300, stdin);
            char rozkaz[6];
            char adr[2];
            int val;
            if(sscanf(line, "%s %s %d", rozkaz, adr, &val)==3){
                unsigned short int a=0,b=0,c=0,d=0;

                if(val<0) a=1<<15;
                else a=0;
                
                switch (rozkaz[0]) {
                    case 'A': // ADD, AND
                        if (rozkaz[1] == 'D') b = 8 << 11; // ADD
                        else b = 12 << 11;                // AND
                        break;
                    case 'J': // JUMP, JNEG, JZERO
                        if (rozkaz[1] == 'U') b = 4 << 11; // JUMP
                        else if (rozkaz[1] == 'N') b = 5 << 11; // JNEG
                        else b = 6 << 11; // JZERO
                        break;
                    case 'L': // LOAD
                        b = 2 << 11;
                        break;
                    case 'N': // NULL, NOT
                        if (rozkaz[1] == 'U') b = 0;       // NULL
                        else b = 14 << 11;                // NOT
                        break;
                    case 'O': // OR
                        b = 13 << 11;
                        break;
                    case 'S': // STOP, STORE, SUB, SHL, SHR
                        switch (rozkaz[1]) {
                            case 'T': // STOP, STORE
                                if (rozkaz[3] == 'P') b = 1 << 11; // STOP
                                else b = 3 << 11;                 // STORE
                                break;
                            case 'U': // SUB
                                b = 9 << 11;
                                break;
                            case 'H': // SHL, SHR
                                if (rozkaz[2] == 'L') b = 10 << 11; // SHL
                                else b = 11 << 11;                  // SHR
                                break;
                        }
                        break;
                    case 'X': // XOR
                        b = 15 << 11;
                        break;
                    default:
                        b = 0; 
                        break;
                }

                switch(adr[0]){
                    case '.' : c=0; break;
                    case '@' : c=1<<9; break;
                    case '*' : c=2<<9; break;
                    case '+' : c=3<<9; break;
                }
                d=abs(val);

                T[rejestr]=a+b+c+d;
            }else{
                sscanf(line, " %d", &val);
                if(val<0) T[rejestr] = (1<<15) + (unsigned short int)(-val);
                else T[rejestr] = (unsigned short int)val;
            }
        }

        int AC=0,PC=0,IR=0,OP=0,IR_adr=0;
        while(1){
            IR=T[PC];
            PC++;
            unsigned short int a,b,c,d;
            a=(IR & (1<<15))>>15;
            b=(IR & (15<<11))>>11;
            c=(IR & (3<<9))>>9;
            d=(IR & (511));
            if(a==1)IR_adr=-d;
            else IR_adr=d;
            
            int limit=1<<15;
            int value;
            switch(c){
                case 0 : OP=IR_adr; break;
                case 1 :
                    value=T[IR_adr];
                    if(value>limit) OP=-(value & (limit-1));
                    else OP=value;
                    break;
                case 2 :
                    value=T[T[IR_adr]];
                    if(value>limit) OP=-(value & (limit-1));
                    else OP=value;
                    break;
                case 3 :
                    value=T[AC+IR_adr];
                    if(value>limit) OP=-(value & (limit-1));
                    else OP=value;
                    break;
            }

            switch(b){
                case 0 : break;
                case 1 : break;
                case 2 : AC=OP; break;
                case 3 : if(AC<0)T[OP]=(1<<15)-AC; else T[OP]=AC; break;
                case 4 : PC=OP; break;
                case 5 : if(AC<0)PC=OP; break;
                case 6 : if(AC==0)PC=OP; break;
                case 8 : AC+=OP; break;
                case 9 : AC-=OP; break;
                case 12 : AC=(AC & OP); break;
                case 13 : AC=(AC | OP); break;
                case 14 : AC=(~AC); break;
                case 15 : AC=(AC ^ OP); break;
                case 10 : AC=AC<<OP; break;
                case 11 : AC=AC>>OP; break;
            }
            printf("PC: %d, AC: %d, OP: %d, IR_adr: %d,  [%d, %d, %d, %d, %d, %d]  (%d, %d, %d)\n", PC, AC, OP, IR_adr,T[30],T[31],T[32],T[48],T[49],T[50], b, c, d);
            if(b==1) break;
        }

        for(int j=0;j<k;j++){
            int pom;
            scanf("%d", &pom);
            int a=(int)T[pom]>>15;
            printf("%d ", a? -(T[pom] & ((1<<15)-1)) : (T[pom] & ((1<<15)-1)));
        }
        printf("\n");


    }
    return 0;
}