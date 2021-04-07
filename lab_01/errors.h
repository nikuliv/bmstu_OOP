#ifndef ERRORS_H
#define ERRORS_H

enum errors
{
    OK,
    EMPTY_FILE_NAME_FIELD,
    FILE_NOT_FOUND,
    FILE_FORMAT_ERR,
    FILE_CONTENT_ERR,
    PTR_ALL_ERR,
    NO_DOTS,
    NO_LINKS,
    UNKNOWN_COMMAND
};

void error_handling(const errors err);

#endif // ERRORS_H
