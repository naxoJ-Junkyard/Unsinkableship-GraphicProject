#include <glm/glm.hpp>
#include "Object3D.h"
#include "Animation.h"


class BezierAnimation : public Animation {
private:
    glm::vec3 m_p0, m_p1, m_p2, m_p3;


public:
    BezierAnimation(Object3D& obj, float_t duration, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
        : Animation(obj, duration), m_p0(p0), m_p1(p1), m_p2(p2), m_p3(p3) {}

    void applyAnimation(float_t dt) override {
        float_t t = currentTime() / duration(); 

        // Compute Bezier curve for x, y, and z
        double Bx = (pow((1 - t), 3) * m_p0.x) + (3 * pow((1 - t), 2) * t * m_p1.x) + (3 * (1 - t) * pow(t, 2) * m_p2.x) + (pow(t, 3) * m_p3.x);
        double By = (pow((1 - t), 3) * m_p0.y) + (3 * pow((1 - t), 2) * t * m_p1.y) + (3 * (1 - t) * pow(t, 2) * m_p2.y) + (pow(t, 3) * m_p3.y);
        double Bz = (pow((1 - t), 3) * m_p0.z) + (3 * pow((1 - t), 2) * t * m_p1.z) + (3 * (1 - t) * pow(t, 2) * m_p2.z) + (pow(t, 3) * m_p3.z);

        object().setPosition(glm::vec3(Bx, By, Bz));
    }
};



