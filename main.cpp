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
          "Введите балл <input type='number' name='mark' step='0.01'>"
          "<p><input type='submit' value='Выбрать'></p>"
          "</form>";
}
void find_std_with_mark(char*mar){
    float mark;
    sscanf_s(mar,"%f",&mark);
    ifstream f;
    f.open("data(bin)",ios_base::binary);
    if(f.is_open()){
        student person;
        while(f.read((char*)&person,sizeof(student))){
            if(person.mark>=mark){
                cout<<person.group<<" "<<person.secondname<<" "<<person.name<<" "<<person.mark<<"<br>";
            }
        }
        f.close();
    }else cout<<"Cant open data(bin)";
}
void show_tree(tree*first){
    if(!first) return;
    int h = first->h;
    int col = (1 << h) - 1;
    elem* q = nullptr;
    create_queue(q, first);
    elem* qfirst = q;
    int lvl=0;
    while (q){
        lvl++;
        int cells = 0;
        int empt_c = (1 << (h-lvl))-1;
        cout << "<tr>\n";
        while (cells<col) {
            if (cells) {
                cout << "<td>&nbsp;</td>\n";
                cells++;
            }
            for (int j = 0; j < empt_c; j++) {
                cells++;
                cout << "<td>&nbsp;</td>\n";
            }
            cells++;
            cout << "<td style='border:1px solid black;'>";
            if (q->uzel) cout << q->uzel->secondname<<" "<<q->uzel->name<<" "<<q->uzel->mark;
            else cout << "-";
            cout << "</td>";
            q = q->next;
            for (int j = 0; j < empt_c; j++) {
                cells++;
                cout << "<td>&nbsp;</td>\n";
            }
        }
        cout << "</tr>\n";
    }
    delete_queue(qfirst);
    /*cout<<first->h<<"   "<<first->mark<<"   "<<first->name<<"    "<<first->secondname<<" <br>   ";
    show_tree(first->left);
    show_tree(first->right);*/
}
void show_tree_in_tree(group*&first){
    if (first){
        show_tree_in_tree(first->left);
        show_tree_in_tree(first->right);
        cout<<"Для группы номер: "<<first->name<<"     "<<first->h<<"<br>";
        cout << "<table style='border: 1px solid black;'>";
        show_tree(first->koren);
        cout << "</table>";
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
                    char* mar;
                    get_user_value(mar,p,"mark");
                    if (strlen(mar)>0) {
                        find_std_with_mark(mar);
                    }
                    delete []out;
                    delete []mar;
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