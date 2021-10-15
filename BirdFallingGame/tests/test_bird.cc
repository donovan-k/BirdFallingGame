//
// Created by donov on 4/29/2021.
//

#include <catch2/catch.hpp>
#include <vector>

#include "core/bird.h"
#include "cinder/gl/gl.h"

using skydiving::BirdGenerator;
using glm::vec2;
using std::vector;

TEST_CASE("Test collision handling") {
  SECTION("Test birds not touching person") {
    SECTION("Test obviously not touching person") {
      BirdGenerator bird_generator;
      BirdGenerator::Bird bird(5, 3, vec2(15,15), vec2(0.1f, 0.3f));
      vec2 person_position = {100,100};
      vec2 person_velocity = {0.2f, -0.1f};
      float person_radius = 3.f;

      bird_generator.GenerateBirds(bird);
      const vec2 kPersonVelo = person_velocity;
      const vec2 kBirdVelo = bird.velocity_;
      bird_generator.HandleCollisionWithBirds(person_position, person_velocity, person_radius);

      REQUIRE(person_velocity == kPersonVelo);
      REQUIRE(bird.velocity_ == kBirdVelo);
    }

    SECTION("Birds not touching off by one") {
      BirdGenerator bird_generator;
      BirdGenerator::Bird bird(6, 4, vec2(10,10), vec2(0.1f, 0.3f));
      vec2 person_position = {21,19};
      vec2 person_velocity = {0.2f, -0.1f};
      float person_radius = 4.f;

      bird_generator.GenerateBirds(bird);
      const vec2 kPersonVelo = person_velocity;
      const vec2 kBirdVelo = bird.velocity_;
      bird_generator.HandleCollisionWithBirds(person_position, person_velocity, person_radius);

      REQUIRE(person_velocity == kPersonVelo);
      REQUIRE(bird.velocity_ == kBirdVelo);
    }
  } // end section test birds not touching person

  SECTION("Test birds touching person") {
    SECTION("Birds touching in 2 dimensions") {
      BirdGenerator bird_generator;
      BirdGenerator::Bird bird(6, 4, vec2(10.f, 10.f), vec2(-0.2f, -0.1f));
      vec2 person_position = {9.f, 9.f};
      vec2 person_velocity = {0.2f, 0.1f};
      float person_radius = 6.f;

      bird_generator.GenerateBirds(bird);
      bird_generator.HandleCollisionWithBirds(person_position, person_velocity, person_radius);
      REQUIRE(person_velocity == vec2{-0.2f, 0.1f});
      REQUIRE(bird_generator.all_birds_.at(0).velocity_ == vec2{0.2f, -0.1f});
    }

    SECTION("Birds touching x direction") {
      BirdGenerator bird_generator;
      BirdGenerator::Bird bird(6, 4, vec2(11.f, 6.f), vec2(-0.5f, 0.f));
      vec2 person_position = {11.f, 3.f};
      vec2 person_velocity = {0.5f, 0.f};
      float person_radius = 6.f;

      bird_generator.GenerateBirds(bird);
      bird_generator.HandleCollisionWithBirds(person_position, person_velocity, person_radius);
      REQUIRE(person_velocity == vec2{-0.5, 0});
      REQUIRE(bird_generator.all_birds_.at(0).velocity_ == vec2{0.5, 0});
    }

    SECTION("Birds touching y direction") {
      BirdGenerator bird_generator;
      BirdGenerator::Bird bird(6, 4, vec2(11.f, 6.f), vec2(0.f, 3.f));
      vec2 person_position = {1.f, 12.f};
      vec2 person_velocity = {0.f, -3.f};
      float person_radius = 6.f;

      bird_generator.GenerateBirds(bird);
      bird_generator.HandleCollisionWithBirds(person_position, person_velocity, person_radius);
      REQUIRE(person_velocity == vec2{0, -3});
      REQUIRE(bird_generator.all_birds_.at(0).velocity_ == vec2{0, 3});
    }
  }
} // end test case (Test collision handling)
