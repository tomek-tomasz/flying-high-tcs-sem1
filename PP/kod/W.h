#include<iostream>

class number{
    private:
        int d;
        int znak;
        int* t;
    public:
        number(){
            int* a = new int[202]();
            t = a;
            znak = 1;
            d = 1;
        }
        number(const std::string &num){
            int s = num.size();
            if(num[0]=='-'){
                znak = -1;
                d = num.size()-1;
            }
            else{
                znak = 1;
                d = num.size();
            }
            int* a = new int[202]();
            t = a;
            for(int i=0; i<d; i++){
                t[i]=num[s-i-1] - '0';
            }
        }
        number(const number &x){
            d = x.d;
            znak = x.znak;
            t = new int[202];
            for(int i=0; i<202; i++){
                t[i] = x.t[i];
            }
        }
        number operator =(const number &x){
            d = x.d;
            znak = x.znak;
            for(int i=0; i<202; i++){
                t[i] = x.t[i];
            }
            return *this;
        }
        number operator +=(const number &x){
            if(znak==x.znak){
                return (*this).add(x);
            }
            else{
                number z(x);
                if(znak==1){
                    z.znak = 1;
                    if((*this<z)==-1){
                        z.sub(*this);
                        z.znak=-1;
                        *this=z;
                        return *this;
                    }
                    else{
                        return (*this).sub(x);
                    }
                }
                else{
                    z.znak = -1;
                    if((*this<z)==1 || (*this<z)==0){
                        z.sub(*this);
                        z.znak = 1;
                        *this=z;
                        return *this;
                    }
                    else{
                        return (*this).sub(x);
                    }
                }
            }
        }
        number operator -=(const number &x){
            number z(x);
            z.znak = z.znak*(-1);
            return (*this)+=z;
        }
        number operator ++(){
            number z("1");
            return *this+=z;
        }
        number operator ++(int){
            number y(*this);
            number z("1");
            *this+=z;
            return y;
        }
        number operator --(){
            number z("-1");
            return *this+=z;
        }
        number operator --(int){
            number y(*this);
            number z("-1");
            *this+=z;
            return y;
        }
        number add(const number &x){
            int m, r, w, val;
            if(d>x.d) m=d;
            else m=x.d;
            for(int i=0; i<m; i++){
                val = t[i] + x.t[i]; 
                r = val % 10;
                w = val / 10;
                t[i] = r;
                t[i+1] += w;
            }
            if(t[m]>0) d=m+1;
            else d=m;
            return  *this;
        }
        number sub(const number &x){
            int r, val, last_digit=1;
            for(int i=0; i<d+1; i++){
                val = t[i] - x.t[i];
                r = (val) % 10;
                if(r<0) r+=10;
                t[i] = r;
                if(r>0) last_digit = i+1;
                if(val<0) t[i+1] -= 1;
            }
            d = last_digit;
            return  *this;
        }
        friend number operator *(const number &x, const number &y);
        friend int operator<(const number& A, const number& B);
        friend std::ostream& operator<<(std::ostream &stream, const number &A);    
        friend std::istream& operator>>(std::istream &stream, number &A);
        ~number(){
            delete[] t;
        }
         
};


number operator *(const number &x, const number &y){
    int w, r, last_digit = 1;
    number z;
    if((z<x)==0 || (z<y)==0) return z;
    z.znak = x.znak*y.znak;
    for(int i=0; i<y.d; i++){
        int val_y = y.t[i];
        for(int j=0; j<x.d; j++){
            z.t[i+j]+=val_y*x.t[j];
        }
    }
    for(int k=0; k<201; k++){
        r = z.t[k]%10;
        w = z.t[k]/10;
        z.t[k]=r;
        z.t[k+1]+=w;
        if(z.t[k]!=0){
            last_digit=k+1;
        }
    }
    if(z.t[201]!=0) z.d=202;
    else z.d = last_digit;
    return z;
}

int operator<(const number& A, const number& B){
    int sgn_a = A.znak, sgn_b = B.znak, d_a = A.d, d_b = B.d;
    int flag=-1;
    if(sgn_a>sgn_b){
        return 1;
    }
    else if(sgn_a<sgn_b){
        return -1;
    }
    else{
        flag=0;
        if(d_a>d_b) flag=1;
        else if (d_a==d_b){
            for(int i=d_a-1; i>=0; i--){
                if(A.t[i]>B.t[i]){
                    flag=1;
                    break;
                } 
                else if(A.t[i]<B.t[i]){
                    flag=-1;
                    break;
                }
            }
            if(flag==0) return 0;
        }
        else flag=-1;
    }
    return flag*sgn_a;
}


std::ostream& operator<<(std::ostream &stream, const number &A){
    std::string s="";
    if(A.znak==-1)s+="-";
    for(int i=A.d-1; i>=0; i--){
        s+= std::to_string(A.t[i]);
    }
    stream << s;
    return stream;
}

std::istream& operator>>(std::istream &stream, number &A){
    
    std::string s;
    stream >> s;
    A = number(s);
    return stream;
}