#include<iostream>
#include<string>

class vector{
    private:
        std::string *t;
        int capacity;
        int size;
    public:
        vector(int a=4, int b=0, const std::string &c=""){
            capacity = a;
            size = b;
            t = new std::string[capacity]();
            for(int i=0; i<size; i++) t[i] = c;
        }

        vector(const vector &v){
            capacity = v.capacity;
            size = v.size;
            t = new std::string[capacity]();
            for(int i=0; i<size; i++) t[i] = v.t[i];
        }

        void add(const std::string &x){
            int old_size = size; 
            resize(size+1);
            t[old_size]=x;
        }

        int getSize() const {
            return size;
        }

        void resize(int new_size){
            if(capacity >= new_size){
                for(int i=0; i+size<new_size; i++) t[i+size]="";
                size = new_size;
                return;
            } 
            int double_capacity = capacity>0 ? capacity<<1 : 1;
            std::string* t_new = new std::string[double_capacity]();
            for(int i=0; i<double_capacity; i++){
                if(i<capacity) t_new[i] = t[i];
                else t_new[i]="";
            }
            capacity = double_capacity;
            std::string* to_delete = t;
            t = t_new;
            delete[] to_delete;
            resize(new_size);
        }

        void clear(){
            size = 0;
        }

        void insert(int i, const std::string &x){
            if(i>size) return;
            int old_size = size;
            resize(size+1);
            for(int j = old_size-i-1; j>=0; j--) t[i+j+1]=t[i+j];
            t[i] = x;
        }

        void erase(int i){
            if(i>=size) return;
            for(int j=0; i+j+1<size; j++){
                t[i+j]=t[i+j+1];
            }
            size--;
            t[size]="";
        }
        
        std::string& operator [](int i){
            if(size==0 && capacity>0) return t[0];
            if(i>=size) return t[size-1];
            return t[i];
        }
        std::string& operator [](int i) const {
            if(size==0 && capacity>0) return t[0];
            if(i>=size) return t[size-1];
            return t[i];
        }

        vector& operator =(const vector &v){
            if(v.capacity>capacity) resize(v.capacity);
            for(int i=0; i<v.capacity; i++){
                if(i<capacity) t[i] = v.t[i];
                else t[i]="";
            }
            capacity = v.capacity;
            size = v.size;
            return *this;
        }

        friend std::ostream& operator <<(std::ostream& stream, const vector &v);
        friend std::istream& operator >>(std::istream& stream, vector &v);
        
        operator bool(){
            if(size == 0) return false;
            return true;
        }
        
        void insertionSort(){
            for(int i=0;i<size-1;i++){
                for(int j=i;j>=0;j--){
                    if(t[j]>t[j+1]){
                        std::string pom=t[j];
                        t[j]=t[j+1];
                        t[j+1]=pom;
                    }
                }   
            }
        }
        
        void sort(int k=0){
            if(size<30){
                insertionSort();
                return;
            }
            vector V[27];
            char f;
            for(int i=0; i<size; i++){
                int s = t[i].length();
                if(k>=s) V[0].add(t[i]);
                else{
                    f = t[i][k];
                    V[f-'A'+1].add(t[i]);
                }
            }
            int counter=0;
            for(int j=1; j<27; j++) V[j].sort(k+1);
            for(int j=0; j<27; j++){
                for(int k=0; k<V[j].size; k++){
                    t[counter] = V[j][k];
                    counter++;
                }
            }
        }

        ~vector(){
            delete[] t;
        }

};

std::ostream& operator <<(std::ostream& stream, const vector &v){
    for(int i=0; i<v.getSize(); i++) stream << v[i] << " ";
    return stream;
}

std::istream& operator >>(std::istream& stream, vector &v){
    for(int i=0; i<v.getSize(); i++) stream >> v[i];
    return stream;
}





int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int z, n;
    std::cin>>z;
    while(z--){
        std::cin >> n;
        vector v(n,n);
        std::cin >> v;
        v.sort();
        std::cout << v << "\n";
        
    }

}