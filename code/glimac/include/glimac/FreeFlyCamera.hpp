#pragma once

#include <glm/glm.hpp>
#include  "glimac/common.hpp"


class FreeFlyCamera
{
private:
    glm::vec3 m_position; //position de la camera
    float m_fPhi; //coordonnées spheriques du vecteur F
    float m_fTheta; //coordonnées spheriques du vecteur F
    glm::vec3 m_FrontVector; //vecteur F
    glm::vec3 m_LeftVector; //vecteur L
    glm::vec3 m_UpVector; //vecteur U


    void computeDirectionVectors();

public:
    //Constructeur
    FreeFlyCamera();
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;



};