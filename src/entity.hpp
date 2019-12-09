#include <glm/glm.hpp>
#include <chrono>

template<typename T = std::chrono::high_resolution_clock>
class Entity
{
public:
    Entity()
        : created_{typename T::now()} {};

    auto Created() { return created_; }

private:
    glm::vec3 position_;

    std::chrono::time_point<T> created_;
};
