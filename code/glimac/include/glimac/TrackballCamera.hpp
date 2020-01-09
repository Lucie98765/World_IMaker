#pragma once

#include <glm/glm.hpp>
#include  "glimac/common.hpp"


class TrackballCamera
{
private:
    float m_fDistance; 
    float m_fAngleX; 
    float m_fAngleY; 


public:
    TrackballCamera();

    void moveFront(float delta){m_fDistance += delta;};

    void rotateLeft(float degrees){m_fAngleX += degrees;};

    void rotateUp(float degrees){m_fAngleY += degrees;};


    glm::mat4 getViewMatrix() const;
};