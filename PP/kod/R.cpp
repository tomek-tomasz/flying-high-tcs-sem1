#include<iostream>

class point{
    private:
        int x;
        int y;
    public:
        point(int a, int b);
        point();
        int getX();
        int getY();
        void print();
};
point::point(int a, int b){
    x=a;
    y=b;
}
point::point(){
    x=0;
    y=0;
}
int point::getX(){
    return x;
}
int point::getY(){
    return y;
}
void point::print(){
    std::cout<<x<<' '<<y<<std::endl;
}



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



class queue{
    private:
        int a;
        int b;
        int k;
        int n;
        point* t;
    public:
        queue();
        queue(int m);
        void enqueue(const point &x);
        point dequeue();
        point front();
        bool empty();
        bool full();
        void clear();
        void resize(int m);
        ~queue();
};



queue::queue(){
    n = 15;
    a = 0;
    b = 0;
    k = 0;
    t = new point[n];
}

queue::queue(int m){
    n = m;
    a = 0;
    b = 0;
    k = 0;
    t = new point[n];
}

void queue::enqueue(const point &x){
    if(k==n) throw (std::string) "ENQUEUE"; 
    a = (n+a-1)%n;
    t[a] = x;
    k++;
}

point queue::dequeue(){
    if(k==0) throw (std::string) "DEQUEUE";
    b=(n+b-1)%n;
    k--;
    return t[b];
}

point queue::front(){
    if(k==0) throw (std::string) "FRONT";
    return t[(n+b-1)%n];
}

bool queue::empty(){
    if(k==0) return true;
    return false;
}

bool queue::full(){
    if(k==n) return true;
    return false;
}

void queue::clear(){
    a = b;
    k = 0;
}

void queue::resize(int m){
    if(m<=n) return;
    point* T;
    T = new point[m];
    for(int i=0; i<k; i++) T[(a+i)%m] = t[(a+i)%n];
    delete[] t;
    t = T;
    n = m;
    b = (a+k)%m;
}

queue::~queue(){
    delete[] t;
}