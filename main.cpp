#include <iostream>
#include <fstream>
#include <cstring>
#include "functions.h"
#include "trees.h"
using namespace std;
void comment(){
    cout<<"<form action='sorting.cgi' method='post'>";
    cout<<"<p><select size='1' required  name='sort'>"
          "<option selected disabled>Выберите метод сортировки данных</option>"
          "<option value='1'>Сортировка по баллам</option>"
          "<option value='2'>Сортировка по алфавиту</option>"
          "</select></p>"
          "<p><input type='submit' value='Выбрать'></p>"
          "</form>";
}
void show_tree(tree*first){
    if(!first) return;
    int h=first->h;
    int col=(1<<h)-1;//побайтовый сдвиг
    elem* q=nullptr;
    create_queue(q,first);
    elem*qfirst=q;
    int lvl=0;
    while(q){
        lvl++;
        int cells=0;
        int empt_c=(1<<(h-lvl))-1;
    }

}
void show_tree_in_tree(group*&first){
    if (first){
        show_tree_in_tree(first->left);
        show_tree_in_tree(first->right);
        cout<<"Для группы номер: "<<first->name<<"<br>";
        show_tree(first->koren);
    }
}
int main() {
    cout << "Content-type: text/html; "
            "charset=utf-8\n\n";
    char*p;
    get_form_data(p);
    if(strlen(p)>0){
        ifstream f;
        f.open("page.html");
        if(f.is_open()){
            char*buf=new char[1000];
            while(!f.eof()){
                f.getline(buf,1000);
                group*first=nullptr;
                if(strcmp(buf,"<!--comment-->")==0){
                    char*out;
                    get_user_value(out,p,"sort");
                    int t;
                    sscanf_s(out,"%X",&t);
                    sort(t,first);
                    show_tree_in_tree(first);
                    delete []out;
                }
                cout<<buf;
            }
            delete[]buf;
            f.close();
        }else cout<<"Cant open page.html";
    }else{
        ifstream f;
        f.open("page.html");
        if(f.is_open()){
            char*buf=new char[1000];
            while(!f.eof()){
                f.getline(buf,1000);
                if(strcmp(buf,"<!--comment-->")==0){
                    comment();
                }
                cout<<buf;
            }
            delete []buf;
            f.close();
        }else cout<<"Cant open page2.html";
        create_data_bin();
    }
    delete []p;
    return 0;
}