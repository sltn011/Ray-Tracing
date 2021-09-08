#ifndef RT_EXCEPTION
#define RT_EXCEPTION

#include <exception>
#include <string>

class Exception : public std::exception {

    std::string m_info;

public:

    explicit Exception(
        std::string const &info
    );

    explicit Exception(
        std::string &&info
    );

    const char *what(
    ) const noexcept override;
};

#endif // RT_EXCEPTION