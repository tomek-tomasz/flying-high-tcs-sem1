#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<fstream>


int isspecial(char* word, char* special_word){
    int length = strlen(word);
    int special_length = strlen(special_word);
    if(abs(special_length - length)>1)return 0;
    int min_length;
    int flag;
    if(special_length==length){
        min_length=special_length;
        flag=0;
    }
    else if(special_length>length){
        min_length = length;
        flag = -1;
    }
    else{
        min_length = special_length;
        flag = 1;
    }
    int difference_flag=0;
    for(int i=0; i<min_length; i++){
        if(difference_flag==0 && word[i]!=special_word[i]){
            difference_flag=1;
            if(flag==0) continue;
        }
        if(difference_flag){
            if(flag==0 && word[i] != special_word[i]) return 0;
            if(flag==-1 && word[i] != special_word[i+1]) return 0;
            if(flag==1 && word[i+1] != special_word[i]) return 0;
        }
    }
    return 1;
}


int main(int argc, char* argv[]){
    char* path_in = argv[1];
    char* path_out = argv[2];
    char* special_word = argv[3];
    for(int i=0; special_word[i]!='\0';i++)special_word[i]=tolower(special_word[i]);
    //printf("%s %s %s\n", path_in, path_out, special_word);
    std::fstream p,out;
    p.open(path_in, std::ios_base::in);
    out.open(path_out, std::ios_base::out);
    int in_comment=0;
    int line_counter=1;
    int word_forget=0;
    char current_word[41];
    int current_letter=0;
    int word_counter=0;
    int special_counter=0;
    int in_word=0;
    while(!p.eof()){
        char c = p.get();
        c=tolower(c);
        //printf("%c",c);
        if(c=='/'){//comment handling
            char pom=p.get();
            if(pom=='*'){
                in_comment++;
                continue;
            }
            else p.putback(pom);
        }
        if(c=='*'){
            char pom=p.get();
            if(pom=='/'){
                in_comment--;
                if(in_comment<0) in_comment=0;
                continue;
            }
            else p.putback(pom);
        }       
        if(in_comment==0){
            if(isalnum(c)){
                if(in_word || (isalpha(c))){
                    in_word=1;
                    if(!word_forget){
                        current_word[current_letter]=c;
                        current_letter++;
                        if(current_letter>40){
                            word_forget=1;
                        }
                    }
                }
            }
            else if(current_letter!=0){
                in_word=0;
                word_forget=0;
                current_word[current_letter]='\0';
                current_letter=0;
                word_counter++;
                if(isspecial(current_word,special_word)){
                    special_counter++;
                    out<<"Linia " << line_counter << ": " << current_word << std::endl;
                }
            }
        }
        if(c=='\n' && !in_comment)line_counter++;
    }
    out << "Wyrazy: " << word_counter << std::endl;
    out << "Wyrazy specjalne: " << special_counter << std::endl;
    p.close();
    out.close();
    return 0;
}