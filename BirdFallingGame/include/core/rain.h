//
// Created by donov on 5/4/2021.
//

#pragma once

#include "core/static_functions.h"
#include "cinder/gl/gl.h"
#include <string>

namespace skydiving {

using std::string;
using glm::vec2;

class Rain {
 public:
  /**
   * Empty Constructor
   */
  Rain();

  /**
   * Constructor to create a rain object
   *
   * @param decider is the number to decide if it is going to rain
   * @param top_left_corner is the top left corner of the game border
   * @param bottom_right_corner is the bottom right corner of the game border
   */
  Rain(float decider, const vec2& top_left_corner, const vec2& bottom_right_corner);

  /**
   * Function takes care of drawing the rain in the game
   */
  void DrawRain() const;

  /**
   * Handles the impact the rain has on the person falling
   *
   * @param person_velocity is the person's velocity
   * @param person_position is the person's position
   * @param feet_per_frame is the feet per frame of the game
   */
  void HandleRain(vec2& person_velocity, const vec2& person_position, float feet_per_frame);

  /**
   * Getter Methods
   */

  bool IsRain() const;

  float GetChanceOfRain() const;

  float GetDecider() const;

  float GetRainLength() const;

 private:
  string rain_color_;
  bool is_rain_{};
  float chance_of_rain_{};
  float decider_{};
  float rain_length_{};
  size_t amount_of_rain_{};
  vec2 top_left_border_;
  vec2 bottom_right_border_;

};

} // namespace skydiving
