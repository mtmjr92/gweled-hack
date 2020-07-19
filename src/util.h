#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <iostream>

class Util {
public:
    static std::string exec(const char *cmd);
    static pid_t getPID();
};

#endif /* UTIL_H_ */
