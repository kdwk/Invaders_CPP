// Retrieved from https://stackoverflow.com/questions/14650885/how-to-create-timer-events-using-c-11#14665230

#include "later.h"
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include <thread>

template <class callable, class... arguments>
Later::Later(int after, bool async, callable&& f, arguments&&... args)
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        if (async)
        {
            std::thread([after, task]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(after));
                task();
            }).detach();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }
    }

// void test1(void)
// {
//     return;
// }

// void test2(int a)
// {
//     printf("%i\n", a);
//     return;
// }

// int main()
// {
//     Later later_test1(1000, false, &test1);
//     Later later_test2(1000, false, &test2, 101);

//     return 0;
// }