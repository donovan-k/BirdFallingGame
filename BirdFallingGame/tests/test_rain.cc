//
// Created by donov on 5/7/2021.
//
#include <catch2/catch.hpp>
#include "cinder/gl/gl.h"
#include "core/rain.h"

using skydiving::Rain;
using glm::vec2;

TEST_CASE("Test handle rain") {
  Rain rain(0, vec2{100,100}, vec2{400,400});
  vec2 person_velo = {0.1, 0.1};
  vec2 person_pos = {150,150};
  rain.HandleRain(person_velo, person_pos, 0.5);
  REQUIRE(person_velo.y == 5.1f);
}