#include <glm/glm.hpp>
#include "Object3D.h"
#include "Animation.h"

class PauseAnimation : public Animation {
private:
    void applyAnimation(float_t dt) override {
        // Do nothing during pause
    }

public:
    PauseAnimation(Object3D& object, float_t duration) : Animation(object, duration) {}
};


