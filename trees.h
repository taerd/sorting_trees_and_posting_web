//
// Created by taerd on 02.05.2019.
//

#ifndef SORTING_TREES_H
#define SORTING_TREES_H
#include "functions.h"
void add(group*&first,student per,int t);
void add(group*& root, group* elem,int t,student person);
void add_tree(tree*&koren,int t,student person);
void add_tree(tree*&koren,int t,tree*new_st);
void balance(group*& root);
int get_height(group* root);
void small_left_rotate(group*& root);
void big_left_rotate(group*& root);
void small_right_rotate(group*& root);
void big_right_rotate(group*& root);
void balance(tree*& root);
int get_height(tree* root);
void small_left_rotate(tree*& root);
void big_left_rotate(tree*& root);
void small_right_rotate(tree*& root);
void big_right_rotate(tree*& root);
#endif //SORTING_TREES_H
