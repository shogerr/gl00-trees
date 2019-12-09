#include "cylinder_sketch.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/constants.hpp"
#include <iostream>

CylinderSketch::CylinderSketch() {}

CylinderSketch::~CylinderSketch()
{
    std::cout << "Destroying Test Signal." << std::endl;
}

void CylinderSketch::OnStartGraphics()
{
    std::vector<glm::vec3> triangle = {
        {-1.f,-1.f,0.f},{1.f,-1.f,0.f},{0.f,1.f,0.f}
    };

    auto make_circle = [](){
        std::vector<glm::vec3> v;
        float step = glm::pi<float>() / 5.f;
        float theta = glm::two_pi<float>();
        glm::vec3 p;
        while (theta >= 0.f)
        {
            p.x = glm::cos(theta);
            p.y = glm::sin(theta);
            p.z = 0.f;
            v.push_back(p);
            p.z = 0.5f;
            v.push_back(p);
            theta -= step;
        }

        // Add the last quad.
        p.x = glm::cos(0.f);
        p.y = glm::sin(0.f);
        p.z = 0.f;
        v.push_back(p);
        p.z = 0.5f;
        v.push_back(p);

        return v;
    };

    glm::mat4 model{1.f};

    model = glm::translate(model, glm::vec3(0.f,0.f,-0.35f));
    model = glm::rotate(model, -90.f, glm::vec3(1.f,0.f,0.f));
    model = glm::scale(model, glm::vec3(.5f,.5f,.5f));

    //for (auto p: triangle)
    //   points_.push_back(p);

    for (auto & p: make_circle())
    {
        p = model * glm::vec4(p, 1.f);
        points_.push_back(p);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    //glDepthRange(0., 1.);

    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, points_.size()*sizeof(glm::vec3), &points_[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void CylinderSketch::DoFrame()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_QUAD_STRIP, 0, (GLsizei)points_.size());
    glDisableVertexAttribArray(0);
}
