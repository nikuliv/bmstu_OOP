#ifndef EXCEPTIONBASE_H
#define EXCEPTIONBASE_H

#include <exception>
#include <iostream>


class vector_exception: public std::exception
{
public:
   vector_exception(std::string fileName, std::string className,
                  int currentLine, const char *errorTime,
                  std::string information);
    virtual const char *what() const noexcept override;

    virtual ~vector_exception() { }

protected:
    std::string errorInformation;
};


#include "exception_base.hpp"

#endif // EXCEPTIONBASE_H
