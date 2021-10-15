//
// Created by donov on 4/17/2021.
//

#include "../../include/visualizer/game_engine.h"

using skydiving::visualizer::GameEngine;
using ci::app::KeyEvent;

GameEngine::GameEngine() {
  // initialize number and boolean variables
  frame_rate_ = 0;
  feet_per_frame_ = 0;
  round_ = 0;
  start_falling_ = false;
  is_win_ = false;

  // initialize the target corners
  tar_left_corner_ = {(kBottomRightCorner_.x + kTopLeftCorner_.x) / 2 - (kTargetLW_.x / 2), kBottomRightCorner_.y - kTargetLW_.y};
  tar_right_corner_ = {(kBottomRightCorner_.x + kTopLeftCorner_.x) / 2 + (kTargetLW_.x / 2), kBottomRightCorner_.y};

  // initialize the wind areas and velocities
  float quarter_border = (kBottomRightCorner_.y - kTopLeftCorner_.y) / 4;
  wind_boxes_top_left_ = {vec2(kTopLeftCorner_.x, kTopLeftCorner_.y + quarter_border), vec2(kTopLeftCorner_.x, kTopLeftCorner_.y + 3 * quarter_border)};
  wind_boxes_bot_right_ = {vec2(kBottomRightCorner_.x - 1, kTopLeftCorner_.y + 2 * quarter_border), vec2(kBottomRightCorner_.x, kBottomRightCorner_.y)};

  float velo1 = GenerateFloatInRange(-feet_per_frame_,feet_per_frame_);
  float velo2 = GenerateFloatInRange(-feet_per_frame_,feet_per_frame_);
  wind_velocity_ = {vec2(velo1, velo1 / 2), vec2(velo2, velo2 / 2)};

  // initialize the leaderboard object
  leaderboard_ = Leaderboard(kTopLeftCorner_, kBottomRightCorner_);

  // initialize the birds
  birds_.GenerateBirds(kTopLeftCorner_, kBottomRightCorner_);
  max_num_birds_ = birds_.all_birds_.size();

  // initialize a rain object
  rain_ = Rain(1.f, kTopLeftCorner_, kBottomRightCorner_);
}

void GameEngine::Display() const{
  // draw border of game
  ci::gl::color(ci::Color(kColorRect_));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeftCorner_, kBottomRightCorner_));

  // checks for wins
  if (!is_win_) {
    // draw current round
    DrawCurrentRound();

    // draw wind areas
    for (size_t i = 0; i < wind_boxes_top_left_.size(); i++) {
      ci::gl::color(kColorWind_);
      ci::gl::drawSolidRect(ci::Rectf(wind_boxes_top_left_.at(i), wind_boxes_bot_right_.at(i)));
    }

    // draw person falling
    ci::gl::color(ci::Color(person_falling_.color_person_));
    ci::gl::drawSolidCircle(person_falling_.position_, person_falling_.radius_);

    // draw birds
    birds_.DrawBirds();

    // draw rain
    rain_.DrawRain();

    // draw target on ground
    ci::gl::color(ci::Color(kColorTarget_));
    ci::gl::drawSolidRect(ci::Rectf(tar_left_corner_, tar_right_corner_));

    // draw leaderboard
    leaderboard_.DrawLeaderboard();
  } else {
    DrawWinTitle();
  }
}

void GameEngine::AdvanceOneFrame() {
  if (!is_win_) {
    bool is_bird_collision = false;
    // take care of collisions with border
    HandleCollisionWithBorder();

    // starts increasing y velocity downwards
    if (start_falling_) {
      vec2 vel_y = person_falling_.velocity_;
      birds_.HandleCollisionWithBirds(person_falling_.position_, person_falling_.velocity_, person_falling_.radius_);
      if (vel_y == person_falling_.velocity_) {
        person_falling_.velocity_.y += feet_per_frame_;
      } else {
        is_bird_collision = true;
      }

      // handle rain
      if (!is_bird_collision)
        rain_.HandleRain(person_falling_.velocity_, person_falling_.position_, feet_per_frame_);
    }

    // check for person in wind areas
    HandleWindVariations();

    person_falling_.position_ += person_falling_.velocity_;

    // increase bird positions
    birds_.IncreasePositionFromVelocity();

    // figures the current score
    CalculateScore(is_bird_collision);
  }
}

void GameEngine::ProcessKey(ci::app::KeyEvent& event) {
  switch (event.getCode()) {
    // person begins falling when these keys are pressed
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_SPACE:
      // check if objects y velocity is zero then changes it to go down
      if (person_falling_.velocity_.y == 0) {
        person_falling_.velocity_.y = feet_per_frame_;
        start_falling_ = true;
      }
      break;

    // person moves to the right
    case KeyEvent::KEY_RIGHT:
      person_falling_.velocity_.x += 0.5f;
      break;

    // person moves to the left
    case KeyEvent::KEY_LEFT:
      person_falling_.velocity_.x -= 0.5f;
      break;

    // resets the game
    case KeyEvent::KEY_BACKSPACE:
      ResetGame();
      break;
  }
}

void skydiving::visualizer::GameEngine::ResetGame() {
  // draw leaderboard
  leaderboard_.AddScore(person_falling_.score_);

  // determine passing round
  if (person_falling_.score_ >= ScoreValues::kScoreForTarget_) {
    round_++;
    rain_ = Rain(1.f - round_ / 10.f, kTopLeftCorner_, kBottomRightCorner_);

    // check for game win
    if (round_ >= kMaxRounds_) {
      round_ = 0;
      rain_ = Rain(1.f, kTopLeftCorner_, kBottomRightCorner_);
      is_win_ = true;
    } else {
      birds_.all_birds_.pop_back();
    }
  }

  // reinitialize variables
  person_falling_.position_ = {110, 200};
  person_falling_.velocity_ = {1, 0};
  person_falling_.score_ = 0;
  start_falling_ = false;

  // set wind to a new velocity
  float velo1 = GenerateFloatInRange(-feet_per_frame_,feet_per_frame_);
  float velo2 = GenerateFloatInRange(-feet_per_frame_,feet_per_frame_);
  wind_velocity_ = {vec2(velo1, velo1 / 2), vec2(velo2, velo2 / 2)};
}

GameEngine::PersonFalling::PersonFalling() {
  position_ = {110.f, 200.f};
  velocity_ = {1.f, 0.f};
  color_person_ = "green";
  radius_ = 5.f;
  score_ = 0;
}

void GameEngine::SetRatesForCalculations(float frame_rate) {
  frame_rate_ = frame_rate;
  feet_per_frame_ = kGravityConst / frame_rate;
}

void GameEngine::CalculateScore(bool is_bird_collision) {
  // checks player hitting target
  if (person_falling_.position_.x < tar_right_corner_.x && person_falling_.position_.x > tar_left_corner_.x &&
      person_falling_.position_.y > tar_left_corner_.y) {
    person_falling_.score_ += ScoreValues::kScoreForTarget_;
  }

  // checks for a collision with bird
  if (is_bird_collision) {
    person_falling_.score_ += ScoreValues::kScoreForBird_;
  }
}

void GameEngine::HandleCollisionWithBorder() {
  // checks for collision with right wall
  if (person_falling_.position_.x + person_falling_.radius_ >= kBottomRightCorner_.x)
    if (person_falling_.velocity_.x > 0)
      person_falling_.velocity_.x = -person_falling_.velocity_.x;

  // checks for collision with left wall
  if (person_falling_.position_.x - person_falling_.radius_ <= kTopLeftCorner_.x)
    if (person_falling_.velocity_.x < 0)
      person_falling_.velocity_.x = -person_falling_.velocity_.x;

  // checks for collision with top wall
  if (person_falling_.position_.y - person_falling_.radius_ <= kTopLeftCorner_.y)
    if (person_falling_.velocity_.y < 0)
      person_falling_.velocity_.y = -person_falling_.velocity_.y;

  // checks for collision with bottom
  if (person_falling_.position_.y + person_falling_.radius_ >= kBottomRightCorner_.y)
    ResetGame();
}

void GameEngine::HandleWindVariations() {
  // checks for person in wind area
  for (size_t i = 0; i < wind_boxes_top_left_.size(); i++) {
    if (person_falling_.position_.y > wind_boxes_top_left_.at(i).y &&
        person_falling_.position_.y < wind_boxes_bot_right_.at(i).y) {
      if ((person_falling_.position_.x += person_falling_.velocity_.x) > kTopLeftCorner_.x &&
          (person_falling_.position_.x += person_falling_.velocity_.x) < kBottomRightCorner_.x)
        person_falling_.velocity_ += wind_velocity_.at(i);
    }
  }
}

void GameEngine::DrawCurrentRound() const {
  float kFontSize = 30;

  ci::Font font("Arial", kFontSize);
  std::ostringstream oss;
  oss << round_;
  std::string round_string = oss.str();
  string string_to_print = "Round " + round_string;
  ci::gl::drawString(string_to_print, vec2{kTopLeftCorner_.x, kTopLeftCorner_.y - kFontSize}, kColorRect_, font);
}

void GameEngine::DrawWinTitle() const {
  float kFontSize = 100;
  ci::Font font("Arial", kFontSize);
  ci::gl::drawStringCentered("You Win!", vec2{(kBottomRightCorner_.x + kTopLeftCorner_.x) / 2,
                                           (kBottomRightCorner_.y + kTopLeftCorner_.y) / 2}, kColorRect_, font);
}

const GameEngine::PersonFalling &skydiving::visualizer::GameEngine::GetPersonFalling() const {
  return person_falling_;
}
