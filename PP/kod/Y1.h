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
            std::string s="";
            if(size==0) return s;
            if(i>=size) return t[size-1];
            return t[i];
        }
        std::string& operator [](int i) const {
            std::string s="";
            if(size==0) return s;
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
