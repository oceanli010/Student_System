#pragma once
#include <cstring>

#define MAX_NAME_LEN 50
#define MAX_ID_LEN 20

typedef enum {Class1, Class2, Class3} ClassType;

typedef struct {
    char stu_name[MAX_NAME_LEN];
    char stu_id[MAX_ID_LEN];
    int stu_age;
    double stu_score;
    ClassType stu_class;
} Student;

//These are sort strategy func
inline bool cmp_Up_as_Name(const Student &a, const Student &b) {
    return strcmp(a.stu_name, b.stu_name) > 0;
}

inline bool cmp_Down_as_Name(const Student &a, const Student &b) {
    return strcmp(a.stu_name, b.stu_name) < 0;
}

inline bool cmp_Up_as_ID(const Student &a, const Student &b) {
    return strcmp(a.stu_id, b.stu_id) > 0;
}

inline bool cmp_Down_as_ID(const Student &a, const Student &b) {
    return strcmp(a.stu_id, b.stu_id) < 0;
}