//
// Created by donov on 5/4/2021.
//

#pragma once

#include "cinder/gl/gl.h"
#include <random>

namespace skydiving {

using glm::vec2;

/**
 * Generates a random float number in between min_size and max_size
 *
 * @param min_size is the minimum float that can be made
 * @param max_size is the maximum float that can be made
 * @return a random float number
 */
float GenerateFloatInRange(float min_size, float max_size);

/**
 * Calculates new velocities for the two sent in because they collided
 *
 * @param pos1 is the position of the object 1
 * @param pos2 is the position of the object 2
 * @param velo1 is the velocity of the object 1
 * @param velo2 is the velocity of the object 2
 */
void CalculateNewVelocities(const vec2& pos1, const vec2& pos2, vec2& velo1, vec2& velo2);

} // namespace skydiving
