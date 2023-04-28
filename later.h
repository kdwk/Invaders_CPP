#ifndef LATER
#define LATER

#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include <thread>

class Later {
    public:
        template <class callable, class... arguments> Later(int after, bool async, callable&& f, arguments&&... args);
};

#endif