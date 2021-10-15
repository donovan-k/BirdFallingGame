//
// Created by donov on 5/4/2021.
//

#include "core/rain.h"

using skydiving::Rain;
using glm::vec2;

Rain::Rain(float decider, const vec2& top_left_corner, const vec2& bottom_right_corner) {
  top_left_border_ = top_left_corner;
  bottom_right_border_ = bottom_right_corner;
  chance_of_rain_ = GenerateFloatInRange(0.5f,1.f);
  decider_ = decider;
  is_rain_ = (chance_of_rain_ > decider_);
  rain_length_ = (1.f - decider) * 20.f;
  amount_of_rain_ = static_cast<size_t>(rain_length_ * 10);
  rain_color_ = "gray";
}


void Rain::DrawRain() const {
  if (is_rain_) {
    ci::gl::color(ci::Color(rain_color_.c_str()));

    // draws lines for rain
    for (size_t i = 0; i < amount_of_rain_; i++) {
      vec2 rain_pos_a = {GenerateFloatInRange(top_left_border_.x, bottom_right_border_.x),
                     GenerateFloatInRange(top_left_border_.y, bottom_right_border_.y - rain_length_)};
      vec2 rain_pos_b = {rain_pos_a.x, rain_pos_a.y + rain_length_};

      ci::gl::drawLine(rain_pos_a, rain_pos_b);
    }
  }
}

void Rain::HandleRain(vec2& person_velocity, const vec2& person_position, const float feet_per_frame) {
  if (is_rain_) {
    float rain_incr = rain_length_ * feet_per_frame * feet_per_frame;
    // make sure person will still be in border
    if (person_position.y + person_velocity.y + rain_incr < bottom_right_border_.y)
      person_velocity.y += rain_incr;
  }
}

bool skydiving::Rain::IsRain() const {
  return is_rain_;
}

float skydiving::Rain::GetChanceOfRain() const {
  return chance_of_rain_;
}

float skydiving::Rain::GetDecider() const {
  return decider_;
}

float skydiving::Rain::GetRainLength() const {
  return rain_length_;
}

Rain::Rain() = default;
