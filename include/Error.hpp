#ifndef ERROR_HPP__
#define ERROR_HPP__

#include <string>

#define ERROR_MESSAGE_SIZE  4096

class Error {
public:
    Error(int code);

public:
    int Code(void) const;
    virtual bool Ok(void) const;
    virtual std::string Reason(void) const;

protected:
    static thread_local char error_message_[ERROR_MESSAGE_SIZE];
    int code_;
};

#endif