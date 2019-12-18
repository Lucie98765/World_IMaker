#include "../include/glimac/FreeFlyCamera.hpp"
#include <cmath>


//Methode privée
void FreeFlyCamera::computeDirectionVectors(){
    m_FrontVector = glm::vec3(
    glm::cos(m_fTheta)*glm::sin(m_fPhi),
    glm::sin(m_fTheta),
    glm::cos(m_fTheta)*glm::cos(m_fPhi)
    );

    m_LeftVector = glm::vec3(
        glm::sin(m_fPhi+M_PI_2),
        0,
        glm::cos(m_fPhi+M_PI_2)
    );

    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);

}

//Constructeur
FreeFlyCamera::FreeFlyCamera() {
    m_position = glm::vec3(0.f, 0.f, 0.f);
    m_fPhi = M_PI;
    m_fTheta = 0;
    computeDirectionVectors();
}

//Methodes publiques

void FreeFlyCamera::moveLeft(float t){
    m_position += t*m_LeftVector;
    m_UpVector = glm::cross(m_FrontVector,m_LeftVector);
}

void FreeFlyCamera::moveFront(float t){
    m_position += t*m_FrontVector;
    m_UpVector = glm::cross(m_FrontVector,m_LeftVector);
}

void FreeFlyCamera::rotateLeft(float degrees){
    m_fPhi+= glm::radians(degrees);
    m_FrontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi),
                             std::sin(m_fTheta),
                             std::cos(m_fTheta) * std::cos(m_fPhi));

    m_LeftVector = glm::vec3(glm::sin(m_fPhi+M_PI_2),
                             0,
                             glm::cos(m_fPhi+M_PI_2));
}

void FreeFlyCamera::rotateUp(float degrees){
    m_fTheta+= glm::radians(degrees);
    m_FrontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi),
                             std::sin(m_fTheta),
                             std::cos(m_fTheta) * std::cos(m_fPhi));

    m_LeftVector = glm::vec3(std::sin(m_fPhi + M_PI_2),
                            0,
                            std::cos(m_fPhi + M_PI_2));
}

glm::mat4 FreeFlyCamera::getViewMatrix() const{
    return glm::lookAt(m_position, m_position+m_FrontVector, m_UpVector);
}

glm::vec3 FreeFlyCamera::getPosition() const{
    return m_position;
}
