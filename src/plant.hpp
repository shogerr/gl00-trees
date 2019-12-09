#include "entity.hpp"

class Plant : Entity<>
{
public:
    Plant() : growth_factor_(1) {};
    Plant(int growth_factor) : growth_factor_(growth_factor) {};
private:
    int growth_factor_;
};
