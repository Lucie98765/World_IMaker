#pragma once

#include <glm/glm.hpp>
#include  "glimac/common.hpp"


class TrackballCamera
{
private:
    float m_fDistance; //Distance par rapport au centre de la scene
    float m_fAngleX; //Angle cam par rapport à l'axe x du centre de la scene = rotation haut bas
    float m_fAngleY; //Par rapport à l'axe y = rotation droite gauche


public:
    //Constructeur
    TrackballCamera();

    //Avancer et reculer la caméra
    void moveFront(float delta);

<<<<<<< HEAD
    //Tourner latéralement autour du centre
    void rotateLeft(float degrees);
=======
    glm::mat4 getViewMatrix()const{
        glm::mat4 matrix = glm::translate(glm::mat4(1.f), glm::vec3(0,0,m_fDistance));
        matrix = glm::rotate(matrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(m_fAngleY), glm::vec3(0, 1.f, 0));
>>>>>>> cube_data_display

    //Tourner verticalement autour du centre
    void rotateUp(float degrees);


    glm::mat4 getViewMatrix() const;
};