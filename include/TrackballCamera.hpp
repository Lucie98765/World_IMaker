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

    //Tourner latéralement autour du centre
    void rotateLeft(float degrees);

    //Tourner verticalement autour du centre
    void rotateUp(float degrees);


    glm::mat4 getViewMatrix() const;
};