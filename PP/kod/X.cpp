#include<iostream>
#include<algorithm>

struct B{
    std::string a;
    std::string t;
};

std::string lower(const std::string &s){
    std::string s1=s;
    int siz = s.size();
    for(int i=0; i<siz; i++) s1[i] = tolower(s1[i]);
    return s1;
}

class D{
    private:
        friend class f;
        int A[128]={0,};
    public:
        D(){
            A[' '] = 0;
        }
        void scan(){
            for(int i=1; i<27; i++){
                char c;
                std::cin>>c;
                A[(int)c]=i;
            }
        }
};

class f{
    private:
        D dial;
    public:
        f(D in){
            dial = in;
        }
        bool strcmp(const std::string &a, const std::string &b){
            int ord_a, ord_b, s;
            if(a.size()<b.size()) s = a.size(); else s = b.size();
            for(int i=0; i<s; i++){
                ord_a = dial.A[tolower(a[i])];
                ord_b = dial.A[tolower(b[i])]; 
                if(ord_a < ord_b){
                    return true;
                }
                else if(ord_b < ord_a){
                    return false;
                }
            }
            if(a.size()<b.size()) return true; else return false;
        }
        bool operator()(const B &x, const B &y){
            if(strcmp(x.a,y.a)) return true;
            else if(strcmp(y.a, x.a)) return false;
            return strcmp(x.t,y.t);
        }

};


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string a1,a2;
    int z,n,k;
    std::cin>>z;
    while(z--){
        std::cin>>n>>k;
        B lib[10000];
        std::for_each(lib, lib + n, [](B &b){
            std::cin>>b.a;
            std::string line;
            getline(std::cin,line);
            line.erase(0,1);
            b.t = line;
        });
        D dial[10];
        for(int j=0; j<k; j++){
            dial[j].scan();
            f cmp_dial(dial[j]);
            std::sort(lib, lib + n ,cmp_dial);
            std::cin>>a1>>a2;
            std::for_each(lib, lib + n, [](B &b){std::cout<<b.a<<" "<<b.t<<"\n";});
            int i=0;
            std::for_each(lib, lib + n, [a1, &i](B &b){if(lower(b.a) == lower(a1)) i++;});
            std::cout << i << " ";
            B* w = std::find_if(lib, lib + n, [a2](B &b){if(lower(b.a) == lower(a2)) return true;else return false;});
            if(w == lib + n) std::cout<< "BRAK\n";
            else std::cout<< w->t << "\n";
        }
        
    }
}