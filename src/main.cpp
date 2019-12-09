#include <chrono>
#include <ctime>
#include <functional>
#include <glm/glm.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <time.h>
#include <vector>

#include "entity.hpp"

struct Ground
{
    std::vector<glm::vec3> points;
};

template <typename T>
Ground ground_generator(T generator)
{
    Ground g;
    g.points = std::vector<glm::vec3>{{1.,1.,1.}};
    return Ground{};
}

struct World
{
    std::ratio<1,24> day_duration;
    Ground ground = ground_generator([](glm::vec3 v) -> int {return v.x*v.x + v.y*v.y;});
};

template <typename Clock>
void clock_info()
{
    std::chrono::nanoseconds ns = typename Clock::duration(1);
    std::cout << ns.count() << " ns\n";
    std::cout << (double)Clock::period::num / Clock::period::den << std::endl;
}

void test_clock()
{
    clock_info<std::chrono::high_resolution_clock>();
    clock_info<std::chrono::system_clock>();
}

void CreateFlora()
{
    Entity<> e;
}

int main()
{
    using namespace std::chrono_literals;

    auto format_time = [](auto t) {
        std::stringstream ss;
        std::tm bt {};
        localtime_s(&bt, &t);
        ss << std::put_time(&bt, "%Y %m %d %X");
        return ss.str();
    };

    World world;

    Entity<std::chrono::high_resolution_clock> entity;

    std::chrono::milliseconds runfor{5000};

    auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - entity.Created() < runfor)
    {
        //std::cout << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << std::endl;
        std::cout << format_time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) << std::endl;
        std::this_thread::sleep_for(500ms);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
    //CreateFlora();
    return 0;
}
