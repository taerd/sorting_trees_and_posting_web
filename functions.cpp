//
// Created by taerd on 02.05.2019.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include "functions.h"
#include "trees.h"
#include <math.h>
using namespace std;
void get_form_data(char*&data){
    size_t buf_size = get_content_length()+1;
    data = new char[buf_size];
    fread(data, sizeof(char), buf_size, stdin);
    data[buf_size-1] = 0;
}
size_t get_content_length(){
    size_t realsize;
    char* value = new char[20];
    getenv_s(&realsize, value, 20, "CONTENT_LENGTH");
    size_t size = 0;
    if (realsize) {
        sscanf_s(value, "%d", &size);
    }
    delete[] value;
    return size;
}
void get_user_value(char*& out_value, const char* data, const char* key_name){
    out_value = nullptr;
    if (data==nullptr || strlen(data)==0) return;
    char* d = strdup(data);
    char* tmp = d;
    char* cnt;
    while (char* part = strtok_s(tmp, "&", &cnt)){
        tmp = nullptr;
        char* val;
        char* key = strtok_s(part, "=", &val);
        if (strcmp(key, key_name)==0){
            out_value = strdup(val);
            delete [] d;
            delete []tmp;
            delete []cnt;
            return;
        }
    }
}
void create_data_bin(){
    fstream f;
    f.open("data");
    if(f.is_open()){
        char*buf=new char[1000];
        ofstream f2;
        f2.open("data(bin)",ios_base::binary);
        if(f2.is_open()){
            while(!f.eof()){
                f.getline(buf,1000);
                char*d=strdup(buf);
                char*cnt;
                char*part=strtok_s(d," ",&cnt);
                student person;
                strcpy(person.secondname,part);
                part=strtok_s(cnt," ",&d);
                strcpy(person.name,part);
                part=strtok_s(d," ",&cnt);
                strcpy(person.group,part);
                part=strtok_s(cnt," ",&d);
                float mar;
                sscanf_s(part,"%f",&mar);
                person.mark=mar;
                f2.write((char*)&person,sizeof(student));
                delete []d;
                delete []cnt;
                delete []part;
            }
            f2.close();
        }else cout<<"Cant open data(bin)";
        delete[]buf;
        f.close();
    }else cout<<"Cant open data";
}
void sort(int t,group*&first){
    ifstream f;
    f.open("data(bin)",ios_base::binary);
    if(f.is_open()){
        student person;
        while(f.read((char*)&person,sizeof(student))){
            //cout<<person.group<<" "<<person.secondname<<" "<<person.name<<" "<<person.mark<<"<br> ";
            add(first,person,t);
        }
        cout<<"<br><br>";
        f.close();
    }else cout<<"Cant open data(bin)";
}

void create_queue(elem*& q,tree*first){
    if(!first) return;
    add(q,nullptr,first);
    int cnt=(1 << first->h)-1;
    elem*curr=q;
    elem*last=q;
    int curr_cnt=1;
    while(curr_cnt<cnt){
        last=add(curr,last,(curr->uzel)?curr->uzel->left:nullptr);
        last=add(curr,last,(curr->uzel)?curr->uzel->right:nullptr);
        curr=curr->next;
        curr_cnt+=2;
    }
}
elem* add(elem*&head,elem* qlast,tree*root){
    elem* new_el = new elem;
    new_el->uzel = root;
    if(!head){
        head=new_el;
        return head;
    }else {
        if (qlast) qlast->next=new_el;
        return new_el;
    }
}
void delete_queue(elem*& q){
    auto* c = q;
    while (c){
        elem* old = c;
        c = c->next;
        delete old;
    }
    q = nullptr;
}
