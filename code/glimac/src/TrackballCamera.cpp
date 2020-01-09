#include "../include/glimac/TrackballCamera.hpp"


//Constructeur
TrackballCamera::TrackballCamera() {
    m_fDistance = -10.0;
    m_fAngleX = 0.0;
    m_fAngleY = 0.0;
}


glm::mat4 TrackballCamera::getViewMatrix() const{
    glm::mat4 viewMatrix(1);
    viewMatrix = glm::translate(viewMatrix,glm::vec3(0.f,0.f,m_fDistance));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0, 1, 0));

    return  viewMatrix;
}