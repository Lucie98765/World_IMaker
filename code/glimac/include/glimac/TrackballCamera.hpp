#pragma once

#include "common.hpp"

namespace glimac {
 class TrackballCamera {
    
public:
    TrackballCamera():m_fDistance(0.f),m_fAngleX(0.f),m_fAngleY(0.f)
    {}

    void moveFront(float delta){
        m_fDistance += delta;
    }

    void rotateLeft(float degrees){
        m_fAngleY += degrees;
    }

    void rotateUp(float degrees){
        m_fAngleX += degrees;
    }

    glm::mat4 getViewMatrix()const{
        glm::mat4 matrix = glm::translate(glm::mat4(1.f), glm::vec3(0,0,-m_fDistance));
        matrix = glm::rotate(matrix, -m_fAngleX, glm::vec3(1.f, 0, 0));
        matrix = glm::rotate(matrix, -m_fAngleY, glm::vec3(0, 1.f, 0));

        return matrix;
    }

private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
};
    
}
