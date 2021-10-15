//
// Created by donov on 4/20/2021.
//

#pragma once

#include <string>
#include <vector>
#include "cinder/gl/gl.h"

namespace skydiving {

namespace visualizer {

using std::string;
using std::vector;
using glm::vec2;

class Leaderboard {
 public:
  /**
   * Empty constructor
   */
  Leaderboard();

  /**
   * Constructor for setting the corners and initializes variables
   *
   * @param top_left_corner is the top left corner of the game border
   * @param bottom_left_corner is the bottom right corner of the game border
   */
  Leaderboard(const vec2& top_left_corner, const vec2& bottom_right_corner);

  /**
   * Adds a score to the leaderboard
   *
   * @param score to add
   */
  void AddScore(int score);

  void DrawLeaderboard() const;

 private:
  string color_border_;
  string name_ = "player_";
  size_t max_scores_ = 10;

  vector<string> player_names_;
  vector<int> scores_;
  vec2 top_left_corner_;
  vec2 bottom_right_corner_;
  size_t num_of_scores_;
};

} // namespace visualizer

} // namespace skydiving
