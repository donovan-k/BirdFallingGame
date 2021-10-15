//
// Created by donov on 5/4/2021.
//

#include "cinder/gl/gl.h"
#include <random>
#include "core/static_functions.h"

using glm::vec2;

float skydiving::GenerateFloatInRange(const float min_size, const float max_size) {
  // got idea from https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_real_distribution<float> distr(min_size, max_size); // define the range
  float rand_num = distr(gen);

  return rand_num;
}

void skydiving::CalculateNewVelocities(const vec2& pos1, const vec2& pos2, vec2& velo1, vec2& velo2) {
  // finds necessary displacements for formula
  vec2 dis_p1_p2 = pos1 - pos2;
  vec2 dis_p2_p1 = pos2 - pos1;

  vec2 dis_v1_v2 = velo1 - velo2;
  vec2 dis_v2_v1 = velo2 - velo1;

  // using formula for finding new velocity1
  velo1 = velo1 - (glm::dot(dis_v1_v2, dis_p1_p2) /
      pow(glm::length(dis_p1_p2),2)) *
      dis_p1_p2;

  // using formula for finding new velocity2
  velo2 = velo2 - (glm::dot(dis_v2_v1, dis_p2_p1) /
      pow(glm::length(dis_p2_p1),2)) *
      dis_p2_p1;
}


