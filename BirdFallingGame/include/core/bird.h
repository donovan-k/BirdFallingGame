//
// Created by donov on 4/19/2021.
//

#pragma once
#include "cinder/gl/gl.h"
#include <vector>
#include <random>
#include <string>
#include "core/static_functions.h"

namespace skydiving {

using glm::vec2;
using std::string;
using std::vector;

class BirdGenerator {

 public:
  /**
   * Empty constructor
   */
  BirdGenerator();

  /**
   * Generates all the positions of the birds
   *
   * @param top_left_border is the top left corner of the border
   * @param bottom_right_border is the bottom right corner of the border
   */
  void GenerateBirds(const vec2& top_left_border, const vec2& bottom_right_border);

  /**
   * Draws a bird at the position with a size specified by the length and width
   *
   * @param length is the length of the bird from left to right
   * @param width is the width of the bird from highest point to lowest
   * @param position is the top left position to begin drawing
   */
  void DrawBirds() const;

  /**
   * Increases the birds' positions based on their velocities
   */
  void IncreasePositionFromVelocity();

  /**
   * Goes through all the birds to see if the person has collided with any of them
   * ps. wouldn't let me send in a PersonFalling object as a whole
   *
   * @param person_position is the person's position
   * @param person_velocity is the person's velocity
   * @param person_radius is the person's radius
   */
  void HandleCollisionWithBirds(vec2& person_position, vec2& person_velocity, float& person_radius);

  /**
   * Struct for bird objects
   */
  struct Bird {
    float length_;
    float width_;
    vec2 position_;
    vec2 velocity_;

    /**
     * Constructor for bird objects
     *
     * @param length is the length of the bird from left to right
     * @param width is the width from highest point to lowest point
     * @param position is the top left corner position of bird
     * @param velocity is the velocity of the bird
     */
    Bird(float length, float width, const vec2 &position, const vec2 &velocity);
  };

  vector<Bird> all_birds_;

  /**
   * Generates one bird instead of creating all of them at once
   *
   * @param bird
   */
  void GenerateBirds(const Bird& bird);

 private:
  vec2 top_left_border_;
  vec2 bottom_left_border_;

  ci::gl::Texture2dRef bird_texture;

  /**
   * Handles any wall collisions with bird
   *
   * @param bird is the bird to check for wall collisions
   */
  void HandleWallCollisions(Bird& bird) const;

  /**
   * Changes velocities of the person and bird after a collision
   *
   * @param bird is the bird colliding with person
   * @param person_position is the person's position
   * @param person_velocity is the person's
   * @param axis_hit is the axis hit ('x' for left or right sides, 'y' for top or bottom)
   */
  void ChangeVelocitiesAfterCollision(Bird& bird, const vec2& person_position, vec2& person_velocity, char axis_hit);
};

} // namespace skydiving
