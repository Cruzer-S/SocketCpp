#include "Error.hpp"

#include <Windows.h>

thread_local char Error::error_message_[ERROR_MESSAGE_SIZE];

Error::Error(int code)
{
    code_ = code;
}

int Error::Code(void) const
{
    return code_;
}

bool Error::Ok(void) const
{
    return code_ == 0;
}

std::string Error::Reason(void) const
{
#if defined(_WIN32)
    FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, code_,
        0,
        (LPSTR)&error_message_, ERROR_MESSAGE_SIZE,
        NULL
    ); // ignore error; even don't care

    return std::string(error_message_);
#else
    return std::string(strerror(code_));
#endif
}       // ignore exception; if std::string cause exception, you are **fucked** up.