#include "physics/KerrBlackHole.h"
#include "utils/Math.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

KerrBlackHole::KerrBlackHole(float mass, float spin)
    : mass(mass), spin(glm::clamp(spin, 0.0f, 0.9999f)), luminosity(1.0f) {
}

float KerrBlackHole::getEventHorizonRadius() const {
    // r+ = M + sqrt(M^2 - a^2)
    float M = mass;
    float a = spin * M;
    return M + glm::sqrt(M * M - a * a);
}

float KerrBlackHole::getInnerHorizonRadius() const {
    // r- = M - sqrt(M^2 - a^2)
    float M = mass;
    float a = spin * M;
    return M - glm::sqrt(M * M - a * a);
}

float KerrBlackHole::getPhotonSphereRadius() const {
    // Approximate photon sphere radius for Kerr black hole
    float M = mass;
    float a = spin * M;
    float a2 = a * a;
    
    // For equatorial plane: r ≈ 2M(1 + cos(2/3 * arccos(-a/M)))
    float ratio = glm::clamp(-a / M, -1.0f, 1.0f);
    return 2.0f * M * (1.0f + glm::cos(2.0f / 3.0f * glm::acos(ratio)));
}

float KerrBlackHole::getISSCO() const {
    // Innermost Stable Circular Orbit
    float M = mass;
    float a = spin * M;
    float Z1 = 1.0f + glm::pow(1.0f - spin * spin, 1.0f / 3.0f) * 
               (glm::pow(1.0f + spin, 1.0f / 3.0f) + glm::pow(1.0f - spin, 1.0f / 3.0f));
    float Z2 = glm::sqrt(3.0f * Z1 * Z1 + 2.0f * a * a / M);
    return M * (Z1 + Z2);
}

glm::mat4 KerrBlackHole::getMetricTensor(glm::vec3 position) const {
    // Boyer-Lindquist coordinates
    float x = position.x;
    float y = position.y;
    float z = position.z;
    
    float rho = glm::sqrt(x*x + y*y);
    float r = glm::sqrt(rho*rho + z*z);
    float a = spin * mass;
    
    float rho2 = rho * rho + z * z;
    float delta = r * r - 2.0f * mass * r + a * a;
    float sigma = rho2 + a * a;
    
    glm::mat4 g(0.0f);
    
    // Metric components
    g[0][0] = -(1.0f - 2.0f * mass * r / sigma);
    g[1][1] = sigma / delta;
    g[2][2] = sigma;
    g[3][3] = (sigma + 2.0f * mass * r * a * a / sigma) * glm::sin(glm::atan(rho, z)) * glm::sin(glm::atan(rho, z));
    g[0][3] = g[3][0] = -2.0f * mass * r * a / sigma;
    
    return g;
}

glm::vec3 KerrBlackHole::calculateLensing(glm::vec3 rayDirection, glm::vec3 position) const {
    // Simple gravitational lensing deflection
    float M = mass;
    float distSq = glm::dot(position, position);
    float dist = glm::sqrt(distSq);
    
    // Deflection angle proportional to M/distance
    float deflection = M / (dist * dist * 0.1f);
    glm::vec3 radial = glm::normalize(position);
    
    return glm::normalize(rayDirection + radial * deflection);
}

float KerrBlackHole::getAccretionDiskInnerRadius() const {
    // Innermost stable circular orbit
    return getISSCO();
}

float KerrBlackHole::getAccretionDiskOuterRadius() const {
    return getISSCO() * 10.0f;
}

float KerrBlackHole::getAccretionDiskTemperature(float radius) const {
    // Temperature ~ 1 / sqrt(r^3)
    float innerR = getAccretionDiskInnerRadius();
    return 10000.0f * glm::pow(innerR / radius, 0.75f) * luminosity;
}

glm::vec3 KerrBlackHole::getAccretionDiskColor(float radius) const {
    float temp = getAccretionDiskTemperature(radius);
    
    // Temperature to color (blackbody radiation)
    glm::vec3 color(0.0f);
    
    if (temp < 3000.0f) {
        color = glm::vec3(1.0f, 0.3f, 0.0f); // Red
    } else if (temp < 5000.0f) {
        color = glm::vec3(1.0f, 0.6f, 0.2f); // Orange
    } else if (temp < 7000.0f) {
        color = glm::vec3(1.0f, 0.9f, 0.5f); // Yellow-white
    } else {
        color = glm::vec3(0.8f, 0.9f, 1.0f); // Blue-white
    }
    
    return color * luminosity;
}

float KerrBlackHole::calculateRho(glm::vec3 position) const {
    return glm::sqrt(position.x * position.x + position.y * position.y);
}

float KerrBlackHole::calculateDelta(glm::vec3 position) const {
    float r = glm::length(position);
    float a = spin * mass;
    return r * r - 2.0f * mass * r + a * a;
}

float KerrBlackHole::calculateSignmaLower(glm::vec3 position) const {
    float r = glm::length(position);
    float rho = calculateRho(position);
    float a = spin * mass;
    return rho * rho + r * r + a * a;
}
