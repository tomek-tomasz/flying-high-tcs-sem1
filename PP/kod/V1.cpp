
#include<iostream>


class monkey{
    private:
        friend class list;
        std::string name;
        int points;
        monkey* previous;
        monkey* next;
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
            head->previous = nullptr;
            head->next = tail;
            tail->previous = head;
            tail->next = nullptr;
        }

        void add(std::string name, int p){
            monkey* newmonke = new monkey(name,p);
            monkey* ptr=head->next;
            while(ptr!=tail && ptr->name<=name){
                if(ptr->name == name){
                    ptr->points+=p;
                    return;
                }
                ptr = ptr->next;
            }
            ptr->previous->next = newmonke;
            newmonke->previous = ptr->previous;
            newmonke->next = ptr;
            ptr->previous = newmonke;
        }

        void del(std::string name){
            monkey* ptr = head->next;
            while(ptr!=tail){
                if (ptr->name == name){
                    ptr->previous->next = ptr->next;
                    ptr->next->previous = ptr->previous;
                    delete ptr;
                    return;
                }
                ptr = ptr->next;
            }
            std::cout << "ERROR " << name << std::endl;
        }

        void find(std::string name){
            monkey* ptr = head->next;
            while(ptr!=tail){
                if (ptr->name == name){
                    std::cout << name << " " << ptr->points << std::endl;
                    return;
                }
                ptr = ptr->next;
            }
            std::cout << "ERROR " << name << std::endl;
        }

        void correct(std::string name, int p){
            monkey* ptr = head->next;
            while(ptr!=tail){
                if (ptr->name == name){
                    int newpoints = ptr->points + p;
                    if(newpoints<0) newpoints=0;
                    ptr->points = newpoints;
                    return;
                }
                ptr = ptr->next;
            }
            std::cout << "ERROR " << name << std::endl;
        }

        void change(std::string name, std::string name2){
            monkey* ptr = head->next;
            while(ptr!=tail){
                if (ptr->name == name) break;
                ptr = ptr->next;
            }
            if(ptr == tail){
                std::cout << "ERROR " << name << " " << name2 << std::endl;
                return;
            }
            monkey* ptr2 = head->next;
            while(ptr2!=tail){
                if (ptr2->name == name2) break;
                ptr2 = ptr2->next;
            }
            if(ptr2 != tail){
                std::cout << "ERROR " << name << " " << name2 << std::endl;
                return;
            }
            std::string oldname = ptr->name;
            int p = ptr->points;
            del(oldname);
            add(name2, p);
        }


        void print(){
            monkey* ptr = head->next;
            if(ptr == tail) std::cout << "EMPTY" << std::endl;
            while(ptr!=tail){
                std::cout << ptr->name << " " << ptr->points << std::endl;
                ptr=ptr->next;
            }
        }

        void print_desc(){
            monkey* ptr = tail->previous;
            if(ptr == head) std::cout << "EMPTY" << std::endl;
            while(ptr!=head){
                std::cout << ptr->name << " " << ptr->points << std::endl;
                ptr=ptr->previous;
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
            std::cout << "CLEAN OK" << std::endl;
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
      }
   }
   return 0;
}




