#pragma once

#include <gl00/scene.hpp>
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

class CylinderSketch : public gl00::Scene
{
public:
    CylinderSketch();
    ~CylinderSketch();

    void OnStartGraphics();
    void DoFrame();
private:
    std::vector<glm::vec3> points_;
    GLuint vao_;
    GLuint vbo_;
};
