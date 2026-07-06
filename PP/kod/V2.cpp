
#include<iostream>


class monkey{
    private:
        friend class list;
        std::string name;
        int points;
        monkey* previous;
        monkey* next;
        monkey* previous2;
        monkey* next2;
    public:
        monkey(std::string s="", int p=0){name=s; points = p;}
};




class list{
    private:
        monkey* head;
        monkey* tail;
    public:
        list(){
            head = new monkey;
            tail = new monkey;
            head->next = tail;
            tail->previous = head;
            head->next2 = tail;
            tail->previous2 = head;
        }

        void add(const std::string &name, int p){
            monkey* ptr=head->next;
            monkey* newmonke=nullptr;
            monkey* wynik=tail;
            while(ptr!=tail && ptr->name<=name){
                if(ptr->name == name){
                    int newpoints = ptr->points+p;
                    p=newpoints;
                    ptr->previous2->next2 = ptr->next2;
                    ptr->next2->previous2 = ptr->previous2;
                    ptr->points = newpoints;
                    newmonke = ptr;
                    break;
                }
                ptr = ptr->next;
            }
            if(newmonke == nullptr){
                newmonke = new monkey(name,p);
                ptr->previous->next = newmonke;
                newmonke->previous = ptr->previous;
                newmonke->next = ptr;
                ptr->previous = newmonke;
            }
            ptr = head->next2;
            while(ptr != tail){
                if(ptr->points >= p && (ptr->points != p || ptr->name > name)){
                    wynik = ptr;
                    break;
                } 
                ptr = ptr->next2;     
            }
            ptr = wynik;
            ptr->previous2->next2 = newmonke;
            newmonke->previous2 = ptr->previous2;
            newmonke->next2 = ptr;
            ptr->previous2 = newmonke;
        }

        void del(const std::string &name){
            monkey* ptr = head->next;
            while(ptr!=tail && ptr->name <= name){
                if (ptr->name == name){
                    ptr->previous->next = ptr->next;
                    ptr->next->previous = ptr->previous;
                    ptr->previous2->next2 = ptr->next2;
                    ptr->next2->previous2 = ptr->previous2;
                    delete ptr;
                    return;
                }
                ptr = ptr->next;
            }
            std::cout << "ERROR " << name << "\n";
        }

        void find(const std::string &name){
            monkey* ptr = head->next;
            while(ptr!=tail && ptr->name <= name){
                if (ptr->name == name){
                    std::cout << name << " " << ptr->points << "\n";
                    return;
                }
                ptr = ptr->next;
            }
            std::cout << "ERROR " << name << "\n";
        }

        void correct(const std::string &name, int p){
            monkey* ptr = head->next;
            while(ptr!=tail && ptr->name <= name){
                if (ptr->name == name){
                    int newpoints = ptr->points+p;
                    if(newpoints<0) newpoints=0;
                    ptr->previous->next = ptr->next;
                    ptr->next->previous = ptr->previous;
                    ptr->previous2->next2 = ptr->next2;
                    ptr->next2->previous2 = ptr->previous2;
                    delete ptr;
                    add(name, newpoints);
                    return;
                }
                ptr = ptr->next;
            }
            std::cout << "ERROR " << name << "\n";
        }

        void change(const std::string &name, std::string &name2){
            monkey* ptr = head->next;
            bool flag=false;
            while(ptr!=tail && ptr->name <= name){
                if (ptr->name == name){
                    flag = true;
                    break;
                }
                ptr = ptr->next;
            }
            if(!flag){
                std::cout << "ERROR " << name << " " << name2 << "\n";
                return;
            }
            monkey* ptr2 = head->next;
            flag = false;
            while(ptr2!=tail && ptr->name <= name){
                if (ptr2->name == name2){
                    flag = true;
                    break;
                } 
                ptr2 = ptr2->next;
            }
            if(flag){
                std::cout << "ERROR " << name << " " << name2 << "\n";
                return;
            }
            std::string oldname = ptr->name;
            int p = ptr->points;
            ptr->previous->next = ptr->next;
            ptr->next->previous = ptr->previous;
            ptr->previous2->next2 = ptr->next2;
            ptr->next2->previous2 = ptr->previous2;
            delete ptr;
            add(name2, p);
        }

        void print(){
            monkey* ptr = head->next;
            if(ptr == tail) std::cout << "EMPTY\n";
            while(ptr!=tail){
                std::cout << ptr->name << " " << ptr->points << "\n";
                ptr=ptr->next;
            }
        }

        void print_desc(){
            monkey* ptr = tail->previous;
            if(ptr == head) std::cout << "EMPTY\n";
            while(ptr!=head){
                std::cout << ptr->name << " " << ptr->points << "\n";
                ptr=ptr->previous;
            }
        }

        void ranking(){
            monkey* ptr = head->next2;
            if(ptr == tail) std::cout << "EMPTY\n";
            while(ptr!=tail){
                std::cout << ptr->name << " " << ptr->points << "\n";
                ptr=ptr->next2;
            }
        }

        void ranking_desc(){
            monkey* ptr = tail->previous2;
            if(ptr == head) std::cout << "EMPTY\n";
            while(ptr!=head){
                std::cout << ptr->name << " " << ptr->points << "\n";
                ptr=ptr->previous2;
            }
        }

        void clean(){
            monkey* ptr=head->next;
            while(ptr!=tail){
                monkey* todelete = ptr;
                ptr = ptr->next;
                delete todelete;
            }
            head->next = tail;
            tail->previous = head;
            head->next2 = tail;
            tail->previous2 = head;
            std::cout << "CLEAN OK\n";
        }

        ~list(){
            monkey* ptr=head->next;
            while(ptr!=tail){
                monkey* todelete = ptr;
                ptr = ptr->next;
                delete todelete;
            }
            delete head;
            delete tail;
        }



};


#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int z, n, p;
    std::string operation, name, name2;
    std::cin >> z;
    while (z--)
    {
        list L;
        std::cin >> n;
        while (n--)
        {
            std::cin >> operation;
            if (operation == "ADD")
            {
                std::cin >> name >> p; L.add(name, p);
            }
            else if (operation == "DISQ")
            {
                std::cin >> name; L.del(name);
            }
            else if (operation == "FIND")
            {
                std::cin >> name; L.find(name);
            }
            else if (operation == "CORRECT")
            {
                std::cin >> name >> p; L.correct(name, p);
            }
            else if (operation == "CHANGE")
            {
                std::cin >> name >> name2; L.change(name, name2);
            }
            else if (operation == "PRINT") L.print();
            else if (operation == "PRINT_DESC") L.print_desc();
            else if (operation == "CLEAN") L.clean();
            else if (operation == "RANKING") L.ranking();
            else if (operation == "RANKING_DESC") L.ranking_desc();
        }
    }
    return 0;
}




