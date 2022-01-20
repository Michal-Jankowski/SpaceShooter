

#ifndef SPACESHOOTER_RANDOMGENERATOR_H
#define SPACESHOOTER_RANDOMGENERATOR_H

#include <random>
#include <glm/vec3.hpp>

class RandomGenerator {
public:
    static RandomGenerator & getInstance();
    float fromZeroToOne();
    glm::vec3 onSurfaceOfUnitSphere();
private:
    RandomGenerator();
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist;

};


#endif //SPACESHOOTER_RANDOMGENERATOR_H
