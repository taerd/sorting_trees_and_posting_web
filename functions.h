//
// Created by taerd on 02.05.2019.
//

#ifndef SORTING_FUNCTIONS_H
#define SORTING_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif
#include <sec_api/stdlib_s.h>
errno_t getenv_s(
        size_t *ret_required_buf_size,
        char *buf,
        size_t buf_size_in_bytes,
        const char *name
);
#ifdef __cplusplus
}
#endif

struct student{
    char name[30];
    char secondname[30];
    float mark=0;
    char group[7];
};
struct tree{
    char name[30];
    int h=0;
    char secondname[30];
    float mark=0;
    tree*left=nullptr;
    tree*right=nullptr;
};
struct group{
    char name[7];
    int h=0;
    tree*koren=nullptr;
    group*left=nullptr;
    group*right=nullptr;
};
void get_form_data(char*&data);
size_t get_content_length();
void get_user_value(char*& out_value, const char* data, const char* key_name);
void create_data_bin();
void sort(int t,group*& root);
#endif //SORTING_FUNCTIONS_H
