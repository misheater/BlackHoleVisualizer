#pragma once

#include <glm/glm.hpp>
#include <cmath>

namespace Math {
    const float PI = glm::pi<float>();
    const float EPSILON = 1e-6f;
    
    // Schwarzschild radius
    inline float schwarzschildRadius(float mass) {
        return 2.0f * mass; // In units where G=c=1
    }
    
    // Convert Kerr to Boyer-Lindquist coordinates
    inline glm::vec3 kerrToCartesian(float r, float theta, float phi) {
        float a = 0.99f; // spin parameter
        float rho = r * glm::sin(theta);
        float z = r * glm::cos(theta);
        
        float x = rho * glm::cos(phi);
        float y = rho * glm::sin(phi);
        
        return glm::vec3(x, y, z);
    }
    
    // Convert Cartesian to Kerr coordinates
    inline glm::vec3 cartesianToKerr(glm::vec3 pos, float a) {
        float x = pos.x;
        float y = pos.y;
        float z = pos.z;
        
        float rho = glm::sqrt(x*x + y*y);
        float r = glm::sqrt(rho*rho + z*z);
        float theta = glm::atan(rho, z);
        float phi = glm::atan(y, x);
        
        return glm::vec3(r, theta, phi);
    }
    
    // Clamp value between min and max
    template<typename T>
    inline T clamp(T value, T minVal, T maxVal) {
        return glm::max(minVal, glm::min(value, maxVal));
    }
    
    // Normalize angle to [0, 2π]
    inline float normalizeAngle(float angle) {
        while (angle < 0.0f) angle += 2.0f * PI;
        while (angle >= 2.0f * PI) angle -= 2.0f * PI;
        return angle;
    }
}
