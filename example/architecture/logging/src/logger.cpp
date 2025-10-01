#include "logging/logger.h"

namespace {
class null_ostream : private std::streambuf, public std::ostream {
public:
    static null_ostream& Inst()
    {
        static null_ostream inst;
        return inst;
    }

protected:
    virtual int overflow(int c)
    {
        setp(buf_, buf_ + sizeof(buf_));
        return (c == eof() ? '\0' : c);
    }

private:
    null_ostream() : std::ostream{this} {}
    char buf_[128];
};

std::ostream& init_os(char const* filename, std::ofstream& ofs)
{
    if (filename == nullptr) {
        return std::cout;
    }
    else {
        if (std::string{filename}.size() == 0) {
            return null_ostream::Inst();
        }
        else {
            ofs.open(filename);
            return ofs;
        }
    }
}
}  // namespace

namespace Logging {
Logger::Logger(char const* filename) : os_{init_os(filename, ofs_)} {}

Logger& Logger::Inst(char const* filename)
{
    static auto inst = Logger{filename};

    return inst;
}

void Logger::Close()
{
    if (&std::cout != &os_) {
        ofs_.close();
    }
}
}  // namespace Logging
