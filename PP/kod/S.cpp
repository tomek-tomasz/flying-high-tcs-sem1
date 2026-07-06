#include<iostream>
class stack{
    private:
        int n;
        int k;
        long long* t;
    public:
        stack();
        stack(int m);
        void push(const long long &x);
        long long pop();
        long long top();
        bool empty();
        bool full();
        void clear();
        void resize(int m);
        ~stack();
};

stack::stack(){
    k = 0;
    n = 15;
    t = new long long[n];
}

stack::stack(int m){
    k = 0;
    n=m;
    t = new long long[n];
}

void stack::push(const long long &x){
    if(k==n) throw (std::string)"PUSH";
    t[k] = x;
    k++;
}

long long stack::pop(){
    if(k==0) throw (std::string)"POP";
    k--;
    return t[k];
}

long long stack::top(){
    if(k==0) throw (std::string)"TOP";
    return t[k-1];
}

bool stack::empty(){
    if(k==0) return true;
    return false;
}

bool stack::full(){
    if(k==n) return true;
    return false;
}

void stack::clear(){
    k=0;
}

void stack::resize(int m){
    if(m<=n) return;
    long long* T;
    T = new long long[m];
    for(int i=0; i<k; i++) T[i]=t[i]; 
    delete[] t;
    t=T;
    n=m;
}

stack::~stack(){
    delete[] t;
}




int alfabet[26];
std::string current;
std::string onp;
stack stos_onp(100000);
stack stos_val(100000);


char axiology(char a){
    if(a=='-') return 1;
    if(a=='+') return 1;
    if(a=='/') return 2;
    if(a=='*') return 2;
    if(a=='^') return 3;
    return 0;
}

long long exp(long long a, long long b){
    if(b<=0) return 1;
    long long wynik = exp(a,b/2);
    if(b%2==0) return wynik * wynik;
    else return a * wynik * wynik;
}

int main(){
    int z, w;
    std::cin >> z;
    while(z--){
        for(int i=0; i<26; i++) std::cin >> alfabet[i];
        scanf("%d", &w);
        for(int j=0; j<w; j++){
            onp.clear();
            stos_onp.clear();
            stos_val.clear();
            std::cin>>current;
            current+=')';
            int size = current.size();
            for(int i=0; i<size; i++){
                char c = current[i];
                if(isalpha(c)){
                    onp+=c;
                }
                else if(c=='(') stos_onp.push(c);
                else if(c == ')'){
                    while(!stos_onp.empty()){
                        char top = (char) stos_onp.top();
                        if(top == '('){
                           stos_onp.pop();
                           break; 
                        }
                        onp += (char) stos_onp.pop();
                    }
                }
                else{
                    while(!stos_onp.empty()){
                        char top = (char) stos_onp.top();
                        if(top=='(') break;
                        if(axiology(top) >= axiology(c)) onp += (char) stos_onp.pop();
                        else break;
                    }
                    stos_onp.push(c);
                }
            }
            std::cout << onp << std::endl;
            int onp_size = onp.size();
            for(int i=0; i<onp_size; i++){
                char c = onp[i];
                if(isalpha(c)) stos_val.push(alfabet[c - 'a']);
                else{
                    long long b = stos_val.pop();
                    long long a = stos_val.pop();
                    if(c=='+') stos_val.push(a+b);
                    else if(c=='-') stos_val.push(a-b);
                    else if(c=='*') stos_val.push(a*b);
                    else if(c=='/'){
                        if(b==0) stos_val.push(0);
                        else stos_val.push(a/b);
                    } 
                    else if(c=='^') stos_val.push(exp(a,b));
                }
            }
            std::cout << stos_val.pop() << std::endl;
        }

    }
}