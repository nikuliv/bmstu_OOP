#ifndef EXCEPTIONBASE_HPP
#define EXCEPTIONBASE_HPP

#include "exception_base.h"

vector_exception::vector_exception(std::string fileName, std::string className,
                                   int currentLine, const char *errorTime,
                                   std::string information = "Error")
{
    errorInformation = "\nFile: " + fileName + "\nClass: " + className +
                       "\nAt line: " + std::to_string(currentLine) + "\nTime: " + errorTime +
                       "Information about error: " + information;
}

const char *vector_exception::what() const noexcept
{
    return errorInformation.c_str();
}

#endif // EXCEPTIONBASE_HPP
