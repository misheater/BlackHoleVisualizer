#include "physics/RayTracer.h"
#include "physics/KerrBlackHole.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>

RayTracer::RayTracer(std::shared_ptr<KerrBlackHole> blackHole)
    : blackHole(blackHole), width(1920), height(1080),
      maxIterations(1024), stepSize(0.1f), epsilon(1e-5f) {
}

void RayTracer::setResolution(int w, int h) {
    width = w;
    height = h;
}

glm::vec4 RayTracer::traceRay(glm::vec3 origin, glm::vec3 direction, float maxDistance) {
    glm::vec3 position = origin;
    glm::vec3 dir = glm::normalize(direction);
    
    float distance = 0.0f;
    float eventHorizonRadius = blackHole->getEventHorizonRadius();
    
    for (int i = 0; i < maxIterations; i++) {
        float r = glm::length(position);
        
        // Check if we hit the event horizon
        if (r < eventHorizonRadius * 1.01f) {
            return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        }
        
        // Check if we're too far
        if (distance > maxDistance) {
            break;
        }
        
        // Check if we hit the accretion disk
        glm::vec4 diskColor;
        if (hitsAccretionDisk(position, dir, diskColor)) {
            return diskColor;
        }
        
        // Simple ray marching step
        position += dir * stepSize;
        distance += stepSize;
        
        // Apply gravitational lensing
        glm::vec3 radial = glm::normalize(position);
        float deflection = blackHole->getMass() / (r * r);
        dir = glm::normalize(dir + radial * deflection * 0.001f);
    }
    
    // Return background starfield color
    return getBackgroundColor(dir);
}

std::vector<glm::vec4> RayTracer::traceScreen(glm::vec3 cameraPos, glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    std::vector<glm::vec4> pixels(width * height);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Normalize screen coordinates
            float u = (2.0f * x - width) / height;
            float v = (2.0f * y - height) / height;
            
            // Construct ray direction
            glm::vec3 rayDir = glm::normalize(glm::vec3(u, v, 1.0f));
            
            // Trace ray
            pixels[y * width + x] = traceRay(cameraPos, rayDir);
        }
    }
    
    return pixels;
}

glm::vec3 RayTracer::integrateGeodesic(glm::vec3 position, glm::vec3 direction, float& distance) {
    // RK4 integration for geodesic equations
    // Placeholder implementation
    return position + direction * stepSize;
}

bool RayTracer::hitsEventHorizon(glm::vec3 position) const {
    return glm::length(position) < blackHole->getEventHorizonRadius();
}

bool RayTracer::hitsAccretionDisk(glm::vec3 position, glm::vec3 direction, glm::vec4& color) {
    float innerR = blackHole->getAccretionDiskInnerRadius();
    float outerR = blackHole->getAccretionDiskOuterRadius();
    
    float rho = glm::sqrt(position.x * position.x + position.z * position.z);
    
    // Check if we're in the disk plane (thin disk approximation)
    if (glm::abs(position.y) < 0.1f && rho > innerR && rho < outerR) {
        float temp = blackHole->getAccretionDiskTemperature(rho);
        glm::vec3 diskColor = blackHole->getAccretionDiskColor(rho);
        color = glm::vec4(diskColor, 1.0f);
        return true;
    }
    
    return false;
}

glm::vec4 RayTracer::getBackgroundColor(glm::vec3 direction) const {
    // Simple procedural starfield
    glm::vec3 starColor = glm::vec3(0.05f) + glm::vec3(0.3f) * glm::sin(direction * 10.0f + 0.5f);
    return glm::vec4(starColor, 1.0f);
}
