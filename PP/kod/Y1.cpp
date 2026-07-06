#include<iostream>



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
                size = new_size;
                return;
            } 
            int double_capacity = capacity<<1;
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
            if(i>=size) return t[size-1];
            return t[i];
        }

        vector operator =(const vector &v){
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
        friend std::istream& operator >>(std::istream& stream, const vector &v);
        
        operator bool(){
            if(size == 0) return false;
            return true;
        }

        ~vector(){
            delete[] t;
        }

};

std::ostream& operator <<(std::ostream& stream, const vector &v){
    vector w(v);
    for(int i=0; i<w.getSize(); i++) stream << w[i] << " ";
    return stream;
}

std::istream& operator >>(std::istream& stream, vector &v){
    for(int i=0; i<v.getSize(); i++) stream >> v[i];
    return stream;
}


#include<iostream>
#include <string>
using namespace std;


void insertionSort(vector tab[], int n) {
   for(int a = 1; a < n; ++a)    {
      vector c = tab[a];
      int x = a;
      for(;x > 0 && c[0] < tab[x-1][0]; x--)       {
         tab[x] = tab[x-1];
         tab[x-1] = c;
      }
   }
}

int main() {
   ios_base::sync_with_stdio(false);
   vector data;
   if (!data) cout << "Lista jest pusta." << endl;

   for(int i=0; i<8; ++i) data.add("kkk");

   if (data) {
      for(int i=0; i<8; ++i) cout << data[i] << " ";
      cout << endl;
   }
   vector data2(80);
   data2.resize(8);
   data2[0] = "a";
   data2[1] = "A";
   data2[2] = "b";
   data2[3] = "B";
   data2[4] = "c";
   data2[5] = "d";
   data2[6] = "e";
   data2[7] = "f";

   cout << data2 << " " << data2.getSize() << endl;
   data2.insert(11, "ala");
   data2.insert(8, "koza");
   data2.insert(5, "Viola");
   cout << data2 << " " << data2.getSize() << endl;

   vector data3(data2);
   data3.erase(13);
   data3.erase(5);
   cout << data3 << " " << data3.getSize() << endl;
   cout << data3[5] << endl;

   vector data4(200, 5, "Karolina");
   cout << data4 << " " << data4.getSize() << endl;
   cin >> data4;
   cout << data4 << " " << data4.getSize() << endl;
   cin >> data4;

   data4 = data;
   cout << data4 << " " << data4.getSize() << endl;
   data4.clear();
   data4.insert(0, "worek");
   cout << data4 << " " << data4.getSize() << endl;

   data2 = data2;
   data2[0] = "Tatry";
   cout << data2 << " " << data2.getSize() << endl;

   vector data5 = data2;
   data5.resize(5);
   data5[0] = "abecadlo";
   cout << data5 << " " << data5.getSize() << endl;

   vector tab[6];
   tab[0] = data;
   tab[1] = data2;
   tab[2] = data3;
   tab[3] = data4;
   tab[4] = data5;

   tab[1][0] = "mysza";
   tab[2][0] = "kot";

   insertionSort(tab, 5);
   cout << tab[0] << endl;
   cout << tab[1] << endl;
   cout << tab[2] << endl;
   cout << tab[3] << endl;
   cout << tab[4] << endl;
   cout << data2 << endl;
   return 0;
}