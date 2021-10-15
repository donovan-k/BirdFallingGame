//
// Created by donov on 4/20/2021.
//

#include "visualizer/leaderboard.h"

using skydiving::visualizer::Leaderboard;

Leaderboard::Leaderboard() {

}

Leaderboard::Leaderboard(const glm::vec2& top_left_corner, const glm::vec2& bottom_right_corner) {
  color_border_ = "white";
  name_ = "player_";
  max_scores_ = 10;
  num_of_scores_ = 0;
  top_left_corner_ = {bottom_right_corner.x + 50, top_left_corner.y};
  bottom_right_corner_ = {top_left_corner_.x + 200, bottom_right_corner.y};
  player_names_.reserve(max_scores_);
  scores_.reserve(max_scores_);
}

void Leaderboard::AddScore(int score) {
  if (num_of_scores_ >= max_scores_) {
    num_of_scores_ = 0;
    player_names_.clear();
    scores_.clear();
  }

  std::ostringstream oss;
  oss << num_of_scores_;
  std::string num = oss.str();
  player_names_.push_back(name_ + num);
  scores_.push_back(score);
  num_of_scores_++;
}

void Leaderboard::DrawLeaderboard() const {
  ci::gl::color(ci::Color(color_border_.c_str()));
  ci::gl::drawStrokedRect(ci::Rectf(top_left_corner_, bottom_right_corner_));
  const float kFontSize = 20.f;

  for (size_t i = 0; i < num_of_scores_; i++) {
    std::ostringstream oss;
    oss << scores_.at(i);
    std::string score_to_print = oss.str();
    string string_to_print = player_names_.at(i) + ' ' + score_to_print;
    ci::Font font("Arial", kFontSize);
    ci::gl::drawString(string_to_print, vec2{top_left_corner_.x, top_left_corner_.y + kFontSize * i}, color_border_.c_str(), font);
  }
}