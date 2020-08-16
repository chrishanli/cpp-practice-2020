// exceptions.h
// the exceptions

#ifndef exceptions_h
#define exceptions_h

class SoundNotFoundExeception: public std::runtime_error {
public:
    SoundNotFoundExeception(std::string const& msg)
    : std::runtime_error(msg) { }
};

#endif /* exceptions_h */
