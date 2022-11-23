#pragma once

#include <stdint.h>

#define error(str) do { fprintf(stderr, "error %s at %s:%d\n", str, __func__, __LINE__); exit(1); } while (0)

#define check_sum(a, b, sum) (UINT32_MAX - (uint32_t)(a) >= (uint32_t)(b) && (uint32_t)(a)+(uint32_t)(b) <= (uint32_t)(sum))

enum mof_qualifier_type {
    MOF_QUALIFIER_UNKNOWN,
    MOF_QUALIFIER_BOOLEAN,
    MOF_QUALIFIER_SINT32,
    MOF_QUALIFIER_STRING,
};

enum mof_variable_type {
    MOF_VARIABLE_UNKNOWN,
    MOF_VARIABLE_BASIC,
    MOF_VARIABLE_OBJECT,
    MOF_VARIABLE_BASIC_ARRAY,
    MOF_VARIABLE_OBJECT_ARRAY,
};

enum mof_basic_type {
    MOF_BASIC_TYPE_UNKNOWN,
    MOF_BASIC_TYPE_STRING,
    MOF_BASIC_TYPE_REAL64,
    MOF_BASIC_TYPE_REAL32,
    MOF_BASIC_TYPE_SINT32,
    MOF_BASIC_TYPE_UINT32,
    MOF_BASIC_TYPE_SINT16,
    MOF_BASIC_TYPE_UINT16,
    MOF_BASIC_TYPE_SINT64,
    MOF_BASIC_TYPE_UINT64,
    MOF_BASIC_TYPE_SINT8,
    MOF_BASIC_TYPE_UINT8,
    MOF_BASIC_TYPE_DATETIME,
    MOF_BASIC_TYPE_CHAR16,
    MOF_BASIC_TYPE_BOOLEAN,
};

enum mof_parameter_direction {
    MOF_PARAMETER_UNKNOWN,
    MOF_PARAMETER_IN,
    MOF_PARAMETER_OUT,
    MOF_PARAMETER_IN_OUT,
};

struct mof_qualifier {
    enum mof_qualifier_type type;
    char* name;
    uint8_t toinstance : 1;
    uint8_t tosubclass : 1;
    uint8_t disableoverride : 1;
    uint8_t amended : 1;
    union {
        uint8_t boolean;
        int32_t sint32;
        char* string;
    } value;
};

struct mof_variable {
    uint32_t qualifiers_count;
    struct mof_qualifier* qualifiers;
    char* name;
    enum mof_variable_type variable_type;
    union {
        enum mof_basic_type basic;
        char* object;
    } type;
    int32_t array_max;
    uint8_t has_array_max;
};

struct mof_method {
    uint32_t qualifiers_count;
    struct mof_qualifier* qualifiers;
    char* name;
    uint32_t parameters_count;
    struct mof_variable* parameters;
    enum mof_parameter_direction* parameters_direction;
    struct mof_variable return_value;
};

struct mof_class {
    char* name;
    char* namesp;
    char* superclassname;
    int32_t classflags;
    uint32_t qualifiers_count;
    struct mof_qualifier* qualifiers;
    uint32_t variables_count;
    struct mof_variable* variables;
    uint32_t methods_count;
    struct mof_method* methods;
};

struct mof_classes {
    uint32_t count;
    struct mof_class* classes;
};