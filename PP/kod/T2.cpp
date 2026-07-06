#include<iostream>

class point{
    private:
        int x;
        int y;
        int nr;
    public:
        point(int a, int b, int num);
        point();
        int getX();
        int getY();
        int getNR();
        void print();
};
point::point(int a, int b, int num){
    x=a;
    y=b;
    nr=num;
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
int point::getNR(){
    return nr;
}
void point::print(){
    std::cout<<x<<' '<<y<<std::endl;
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


int main(){
    int z,n,m;
    std::cin >> z;
    while(z--){
        std::cin >> n >> m;
        short T[n][m], Pom[n][m];
        queue kolejka(n*m);
        queue kolejka1(n*m);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                std::cin >> T[i][j];
                point p(i,j,T[i][j]);
                Pom[i][j]=0;
                if(T[i][j]>=4){
                    if(T[i][j]%2==0) kolejka.enqueue(p);
                    else kolejka1.enqueue(p);
                }
            }
        }
        point wynik(-1, -1, 0);
        while(!kolejka.empty()){
            point p = kolejka.dequeue();
            int x = p.getX();
            int y = p.getY();
            int nr = p.getNR();
            if(x+1<n && Pom[x+1][y]==0 && (T[x+1][y]==0 || T[x+1][y]==3 || (T[x+1][y]>=4 && T[x+1][y]%2==1))){
                if(T[x+1][y]==3){
                    point w(nr, Pom[x][y]+1, 0);
                    wynik = w;
                    break;
                }
                Pom[x+1][y] = Pom[x][y]+1;
                point pp(x+1, y, nr);
                kolejka.enqueue(pp);
            }
            if(x-1>=0 && Pom[x-1][y]==0 && (T[x-1][y]==0 || T[x-1][y]==3 || (T[x-1][y]>=4 && T[x-1][y]%2==1))){
                if(T[x-1][y]==3){
                    point w(nr, Pom[x][y]+1, 0);
                    wynik = w;
                    break;
                }
                Pom[x-1][y] = Pom[x][y]+1;
                point pp(x-1, y, nr);
                kolejka.enqueue(pp);
            }
            if(y+1<m && Pom[x][y+1]==0 && (T[x][y+1]==0 || T[x][y+1]==3 || (T[x][y+1]>=4 && T[x][y+1]%2==1))){
                if(T[x][y+1]==3){
                    point w(nr, Pom[x][y]+1, 0);
                    wynik = w;
                    break;
                }
                Pom[x][y+1] = Pom[x][y]+1;
                point pp(x, y+1, nr);
                kolejka.enqueue(pp);
            }
            if(y-1>=0 && Pom[x][y-1]==0 && (T[x][y-1]==0 || T[x][y-1]==3 || (T[x][y-1]>=4 && T[x][y-1]%2==1))){
                if(T[x][y-1]==3){
                    point w(nr, Pom[x][y]+1, 0);
                    wynik = w;
                    break;
                }
                Pom[x][y-1] = Pom[x][y]+1;
                point pp(x, y-1, nr);
                kolejka.enqueue(pp);
            }            
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++) Pom[i][j]=0;
        }
        point wynik1(-1, -1, 0);
        while(!kolejka1.empty()){
            point p = kolejka1.dequeue();
            int x = p.getX();
            int y = p.getY();
            int nr = p.getNR();
            if(x+1<n && Pom[x+1][y]==0 && (T[x+1][y]==0 || T[x+1][y]==3 || T[x+1][y]==1 || (T[x+1][y]>=4 && T[x+1][y]%2==0))){
                if(T[x+1][y]==3){
                    point w(nr, Pom[x][y]+1, 0);
                    wynik1 = w;
                    break;
                }
                Pom[x+1][y] = Pom[x][y]+1;
                point pp(x+1, y, nr);
                kolejka1.enqueue(pp);
            }
            if(x-1>=0 && Pom[x-1][y]==0 && (T[x-1][y]==0 || T[x-1][y]==3 || T[x-1][y]==1 || (T[x-1][y]>=4 && T[x-1][y]%2==0))){
                if(T[x-1][y]==3){
                    point w(nr, Pom[x][y]+1, 0);
                    wynik1 = w;
                    break;
                }
                Pom[x-1][y] = Pom[x][y]+1;
                point pp(x-1, y, nr);
                kolejka1.enqueue(pp);
            }
            if(y+1<m && Pom[x][y+1]==0 && (T[x][y+1]==0 || T[x][y+1]==3 || T[x][y+1]==1 || (T[x][y+1]>=4 && T[x][y+1]%2==0))){
                if(T[x][y+1]==3){
                    point w(nr, Pom[x][y]+1, 0);
                    wynik1 = w;
                    break;
                }
                Pom[x][y+1] = Pom[x][y]+1;
                point pp(x, y+1, nr);
                kolejka1.enqueue(pp);
            }
            if(y-1>=0 && Pom[x][y-1]==0 && (T[x][y-1]==0 || T[x][y-1]==3 || T[x][y-1]==1 || (T[x][y-1]>=4 && T[x][y-1]%2==0))){
                if(T[x][y-1]==3){
                    point w(nr, Pom[x][y]+1, 0);
                    wynik1 = w;
                    break;
                }
                Pom[x][y-1] = Pom[x][y]+1;
                point pp(x, y-1, nr);
                kolejka1.enqueue(pp);
            }            
        }
        
        if(wynik1.getY()<wynik.getY() || wynik.getY()==-1) wynik1.print();
        else wynik.print();
    }
}
