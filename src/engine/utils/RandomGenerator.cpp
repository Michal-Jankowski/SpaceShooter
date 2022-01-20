


#include "RandomGenerator.h"
#include "MathUtils.h"

RandomGenerator &RandomGenerator::getInstance() {
    static RandomGenerator random;
    return random;
}

RandomGenerator::RandomGenerator() {
    std::random_device dev;
    rng = std::mt19937(dev());
    dist = std::uniform_int_distribution<std::mt19937::result_type>(0,100);
}

glm::vec3 RandomGenerator::onSurfaceOfUnitSphere() {
    float theta = PI * fromZeroToOne();
    float phi = TWO_PI * fromZeroToOne();
    return MathUtils::sphericalToCartesianRadians(1.0f,phi,theta);
}

float RandomGenerator::fromZeroToOne() {
    return (float)dist(rng)/100.0f;
}
