#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "exception_base.h"

class memory_exception: public vector_exception
{
public:
    memory_exception(std::string file_name, std::string class_name,
                    int current_line, const char *error_time,
                    std::string information = "Memory Error"):
        vector_exception(file_name, class_name, current_line, error_time, information)
    {
    };
    virtual const char *what() const noexcept
    {
        return errorInformation.c_str();
    }
};


class deleted_object_exception: public vector_exception
{
public:
    deleted_object_exception(std::string file_name, std::string class_name,
                           int current_line, const char *error_time,
                           std::string information = "Object doesn't exsist"):
        vector_exception(file_name, class_name, current_line, error_time, information)
    {
    };
};


class empty_vector_exception: public vector_exception
{
public:
    empty_vector_exception(std::string file_name, std::string class_name,
                         int current_line, const char *error_time,
                         std::string information = "Work with empty vector"):
        vector_exception(file_name, class_name, current_line, error_time, information)
    {
    };
};

class out_of_range_exception: public vector_exception
{
public:
    out_of_range_exception(std::string file_name, std::string class_name,
                          int current_line, const char *error_time,
                          std::string information = "Index is out of range"):
        vector_exception(file_name, class_name, current_line, error_time, information)
    {
    };
};

class zero_division_exception: public vector_exception
{
public:
    zero_division_exception(std::string file_name, std::string class_name,
                          int current_line, const char *error_time,
                          std::string information = "Zero division error"):
        vector_exception(file_name, class_name, current_line, error_time, information)
    {
    };
};

class invalid_copy_array_pointer: public vector_exception
{
public:
    invalid_copy_array_pointer(std::string file_name, std::string class_name,
                            int current_line, const char *error_time,
                            std::string information = "Zero division error"):
        vector_exception(file_name, class_name, current_line, error_time, information)
    {
    };
};

class invalid_vectors_sizes: public vector_exception
{
public:
    invalid_vectors_sizes(std::string file_name, std::string class_name,
                            int current_line, const char *error_time,
                            std::string information = "Vectors sizes equality error"):
        vector_exception(file_name, class_name, current_line, error_time, information)
    {
    };
};

class invalid_iterator: public vector_exception
{
public:
    invalid_iterator(std::string file_name, std::string class_name,
                    int current_line, const char *error_time,
                    std::string information = "*Iterator is invalid"):
        vector_exception(file_name, class_name, current_line, error_time, information)
    {
    };
};

#endif // EXCEPTIONS_H
