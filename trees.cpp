//
// Created by taerd on 02.05.2019.
//

#include <iostream>
#include <cstring>
#include "trees.h"
void add(group*& root,student person,int t){
    auto* new_el = new group;
    strcpy(new_el->name,person.group);
    add(root, new_el,t,person);
}
void add(group*& root, group* elem,int t,student person){
    if (!elem) return;
    if (!root) {
        root = elem;
        add_tree(elem->koren,t,person);
    }
    else {
        if(strcmp(root->name,elem->name)==0){
            add_tree(root->koren,t,person);
        }
        else if (strcmp(root->name,elem->name)>0){
            add(root->left, elem,t,person);
        } else {
            add(root->right, elem,t,person);
        }
        balance(root);
        root->h = get_height(root);
    }
}



void add_tree(tree*&koren,int t,student person){
    auto*new_st=new tree;
    strcpy(new_st->name,person.name);
    strcpy(new_st->secondname,person.secondname);
    new_st->mark=person.mark;
    add_tree(koren,t,new_st);
}
void add_tree(tree*&koren,int t,tree*new_st){
    if(!new_st) return;
    if(!koren){
        koren=new_st;
        return;
    }
    /*std::cout<<"Кого сравниваем "<<koren->secondname<<"  "<<koren->name<<"  "<<koren->mark<<"     С     "<<
    new_st->secondname<<"   "<<new_st->name<<"   "<<new_st->mark<<"<br>";*/
    if(t==1){//сортировка по баллам
        if(koren->mark > new_st->mark){
            add_tree(koren->left,t,new_st);
        }
        else if(koren->mark < new_st->mark) {
            add_tree(koren->right, t, new_st);
        }
        else{
            add_tree(koren, 2, new_st);
        }
    }else{
        if(strcmp(koren->secondname,new_st->secondname)>0){
            add_tree(koren->left,t,new_st);
        } else if(strcmp(koren->secondname,new_st->secondname)<0){
            add_tree(koren->right,t,new_st);
        }else if(strcmp(koren->name,new_st->name)>0){
            add_tree(koren->left,t,new_st);
        }else add_tree(koren->right,t,new_st);
    }
    balance(koren);
    koren->h = get_height(koren);
}




void balance(group*& root){
    if (!root) return;
    int lh = get_height(root->left);
    int rh = get_height(root->right);
    if (abs(lh-rh)>=2){
        if (rh>lh){
            if (get_height(root->right->left)> get_height(root->right->right)){
                big_left_rotate(root);
            } else {
                small_left_rotate(root);
            }
        } else {
            if (get_height(root->left->right)> get_height(root->left->left)){
                big_right_rotate(root);
            } else {
                small_right_rotate(root);
            }
        }
    }
}
int get_height(group* root){
    if (!root) return 0;
    int lh = (root->left) ? root->left->h : 0;
    int rh = (root->right) ? root->right->h : 0;
    return 1 + ((lh>rh) ? lh : rh);
}
void small_left_rotate(group*& root){
    if (!root) return;
    group* r = root->right;
    root->right = r->left;
    r->left = root;
    root = r;
    if (root->left) root->left->h = get_height(root->left);
}

void big_left_rotate(group*& root){
    small_right_rotate(root->right);
    small_left_rotate(root);
}

void small_right_rotate(group*& root){
    if (!root) return;
    group* r = root->left;
    root->left = r->right;
    r->right = root;
    root = r;
    if (root->right) root->right->h = get_height(root->right);
}

void big_right_rotate(group*& root){
    small_left_rotate(root->left);
    small_right_rotate(root);
}






void balance(tree*& root){
    if (!root) return;
    int lh = get_height(root->left);
    int rh = get_height(root->right);
    if (abs(lh-rh)>=2){
        if (rh>lh){
            if (get_height(root->right->left)> get_height(root->right->right)){
                big_left_rotate(root);
            } else {
                small_left_rotate(root);
            }
        } else {
            if (get_height(root->left->right)> get_height(root->left->left)){
                big_right_rotate(root);
            } else {
                small_right_rotate(root);
            }
        }
    }
}
int get_height(tree* root){
    if (!root) return 0;
    int lh = (root->left) ? root->left->h : 0;
    int rh = (root->right) ? root->right->h : 0;
    return 1 + ((lh>=rh) ? lh : rh);
}
void small_left_rotate(tree*& root){
    if (!root) return;
    tree* r = root->right;
    root->right = r->left;
    r->left = root;
    root = r;
    if (root->left) root->left->h = get_height(root->left);
}

void big_left_rotate(tree*& root){
    small_right_rotate(root->right);
    small_left_rotate(root);
}

void small_right_rotate(tree*& root){
    if (!root) return;
    tree* r = root->left;
    root->left = r->right;
    r->right = root;
    root = r;
    if (root->right) root->right->h = get_height(root->right);
}

void big_right_rotate(tree*& root){
    small_left_rotate(root->left);
    small_right_rotate(root);
}