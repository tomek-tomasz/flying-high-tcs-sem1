
#include<iostream>


class monkey{
    private:
        friend class list;
        std::string name;
        monkey* next;
    public:
        monkey(std::string s=""){name=s;}
};




class list{
    private:
        monkey head;
        monkey* last;
    public:
        list(){
            head.next = nullptr;
            last = &head;
        }

        void front(std::string name){
            monkey* newmonke = new monkey(name);
            newmonke->next = head.next;
            head.next = newmonke;
            if (last == &head) {
                last = newmonke;
            }
        }

        void back(std::string name){
            monkey* newmonke = new monkey(name);
            newmonke->next = nullptr;
            monkey* ptr = newmonke;
            last->next = ptr;
            last = ptr;
        }

        void add(std::string name , int i){
            monkey* newmonke = new monkey(name);
            monkey* ptr = &head;
            for(int j=0; j<i-1; j++){ 
                ptr = ptr->next;
                if(ptr == nullptr){
                    newmonke->next = nullptr;
                    last->next = newmonke;
                    last = newmonke;
                    return;
                }
            }
            newmonke->next = ptr->next;
            ptr->next = newmonke;
            if (newmonke->next == nullptr) {
                last = newmonke;
            }
        }

        void del(std::string name){
            monkey* ptr = &head;
            while(ptr->next!=nullptr){
                if (ptr->next->name == name){
                    monkey* todelete = ptr->next;
                    ptr->next = ptr->next->next;
                    if(todelete == last){
                        last = ptr;
                    }
                    delete todelete;
                    return;
                }
                ptr = ptr->next;
            }
            std::cout << "BLAD " << name << std::endl;
        }

        void change(int i, int j){
            monkey* ptr = &head;
            if(head.next==nullptr){
                std::cout<<"BLAD "<< i << std::endl;
                return;
            }
            for(int k=0; k<i-1; k++){
                ptr = ptr->next;
                if(ptr->next == nullptr){
                    std::cout<<"BLAD "<< i << std::endl;
                    return;
                }
            }
            std::string name = ptr->next->name;
            monkey* todelete = ptr->next; 
            if (todelete == last) {
                last = ptr;
            }
            ptr->next = ptr->next->next;
            delete todelete;
            add(name, j);
        }

        void print(){
            monkey* ptr = head.next;
            if(head.next == nullptr)std::cout << "PUSTY";
            while(ptr!=nullptr){
                std::cout << ptr->name << ' ';
                ptr=ptr->next;
            }
            std::cout << std::endl;
        }

        void reverse(){
            monkey* ptr1 = head.next;
            if(ptr1 == nullptr) return;
            monkey* ptr2 = ptr1->next;
            monkey* pom;
            while(ptr2 != nullptr){
                pom = ptr2->next;
                ptr2->next = ptr1;
                ptr1 = ptr2;
                ptr2 = pom;
            }
            monkey* lastpom = head.next;
            head.next->next=nullptr;
            head.next = last;
            last = lastpom;
        }

        void clean(){
            monkey* ptr=head.next;
            while(ptr!=nullptr){
                monkey* todelete = ptr;
                ptr = ptr->next;
                delete todelete;
            }
            head.next = nullptr;
            last = &head;
        }

        ~list(){clean();}



};






