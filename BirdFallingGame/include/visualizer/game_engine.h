//
// Created by donov on 4/17/2021.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "leaderboard.h"
#include "core/bird.h"
#include "core/rain.h"

namespace skydiving {

namespace visualizer {

using cinder::ColorT;
using glm::vec2;

class GameEngine {
 public:
  /**
   * Empty Constructor
   */
  GameEngine();

  /**
   * Displays the game container and position of objects in the game
   */
  void Display() const;

  /**
   * Updates the objects in the game's velocities and positions
   */
  void AdvanceOneFrame();

  /**
   * Processes key presses during the game
   *
   * @param event
   */
  void ProcessKey(ci::app::KeyEvent& event);

  /**
   * Struct to define a person falling
   */
  struct PersonFalling {
    vec2 position_;
    vec2 velocity_;
    ColorT<float> color_person_;
    float radius_;
    int score_;

    /**
     * Empty constructor to create a person
     */
    PersonFalling();
  };

 private:
  const ColorT<float> kColorRect_ = "white";
  const ColorT<float> kColorTarget_ = "red";
  const ci::Color kColorWind_ = ci::Color(0.72f, 0.92f, 1.f);

  const vec2 kTopLeftCorner_ = {100, 100};
  const vec2 kBottomRightCorner_ = {600, 600};
  const vec2 kTargetLW_ = {50.f, 10.f};

  const float kGravityConst = 5.f;
  const size_t kMaxRounds_ = 10;
  vec2 tar_left_corner_;
  vec2 tar_right_corner_;

  /**
   * Struct for defining score values
   */
  struct ScoreValues {
    static const int kScoreForTarget_ = 100;
    static const int kScoreForBird_ = 10;
  };

  PersonFalling person_falling_;
  BirdGenerator birds_;
  Leaderboard leaderboard_;
  Rain rain_;

  vector<vec2> wind_boxes_top_left_;
  vector<vec2> wind_boxes_bot_right_;
  vector<vec2> wind_velocity_;

  float frame_rate_;
  float feet_per_frame_;
  bool start_falling_;
  bool is_win_;
  size_t round_;
  size_t max_num_birds_;

  /**
   * Resets the current game to send player back to top
   */
  void ResetGame();

  /**
   * Handles any collisions with the border
   */
  void HandleCollisionWithBorder();

  /**
   * Handles wind forces on the person
   */
  void HandleWindVariations();

  /**
   * Draws the current round above the border
   */
  void DrawCurrentRound() const;

  /**
   * Draws "You Win!" in the middle of the screen when there is a win
   */
  void DrawWinTitle() const;

 public:
  /**
   * Sets the falling rate based on the gravity and the frame rate
   * @param frame_rate is how many frames are made every second
   */
  void SetRatesForCalculations(float frame_rate);

  /**
   * Calculates score whether person has hit target or hit a bird
   * @param is_bird_collision is whether the person has hit a bird
   */
  void CalculateScore(bool is_bird_collision);

  /**
   * Get methods
   */
  const PersonFalling &GetPersonFalling() const;
};

} // namespace visualizer

} // namespace skydiving


