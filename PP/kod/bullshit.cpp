#include<iostream>

using namespace std;


int main(){
    int T[5][5];
    int k=0;
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            T[i][j] = k;
            k++;
        }
    }
    int* p = (int*)T;
    for(int l=0; l<25; l++){
        cout<<*(p+l)<<endl;
    }
        

}