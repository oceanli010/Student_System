#pragma once
#include <string>

typedef enum {Class1, Class2, Class3} ClassType;

typedef struct {
    std::string stu_name;
    std::string stu_id;
    int stu_age;
    double stu_score;
    ClassType stu_class;
} Student;

//These are sort strategy func
inline bool cmp_Up_as_Name(const Student &a, const Student &b) {
    return a.stu_name > b.stu_name;
}

inline bool cmp_Down_as_Name(const Student &a, const Student &b) {
    return a.stu_name < b.stu_name;
}

inline bool cmp_Up_as_ID(const Student &a, const Student &b) {
    return a.stu_id > b.stu_id;
}

inline bool cmp_Down_as_ID(const Student &a, const Student &b) {
    return a.stu_id < b.stu_id;
}