//
// Created by donov on 4/19/2021.
//

#include "core/bird.h"

using skydiving::BirdGenerator;
using glm::vec2;
using std::string;

BirdGenerator::BirdGenerator() = default;

void BirdGenerator::GenerateBirds(const vec2& top_left_border, const vec2& bottom_right_border) {
  auto img = ci::loadImage(R"(D:\JetBrains\~Cinder\my-projects\final-project-donovan-k\resources\birdforgame.png)");
  bird_texture = ci::gl::Texture::create(img);
  top_left_border_ = top_left_border;
  bottom_left_border_ = bottom_right_border;
  const float divider = 2;
  const float ten_divider = 5;
  const vec2 kMaxBirdSize = {(bottom_right_border.x - top_left_border.x) / ten_divider, (bottom_right_border.y - top_left_border.y) / (divider * ten_divider)};
  const vec2 kMinBirdSize = {kMaxBirdSize.x - divider * glm::sqrt(kMaxBirdSize.x), kMaxBirdSize.y - divider * glm::sqrt(kMaxBirdSize.y)};

  // generates aspects of birds
  vec2 position = {(bottom_right_border.x - top_left_border.x) / divider, (bottom_right_border.y - top_left_border.y) / (divider*divider)};
  while (position.y < bottom_right_border.y - kMaxBirdSize.y) {
    vec2 velocity = {GenerateFloatInRange(-divider, divider), GenerateFloatInRange(-divider, divider)};
    Bird bird(GenerateFloatInRange(kMinBirdSize.x,kMaxBirdSize.x), GenerateFloatInRange(kMinBirdSize.y,kMaxBirdSize.y), position, velocity);
    all_birds_.push_back(bird);

    position.y += bird.width_ + 1;
  }
}

void BirdGenerator::DrawBirds() const {
  // draws on the birds within border
  ci::gl::color(ci::Color("white"));
  for (const Bird& bird : all_birds_) {
    // draws body
    vec2 top_left_of_bird_rect = bird.position_;
    vec2 bot_right_of_bird_rect = {bird.position_.x + bird.length_, bird.position_.y + bird.width_ / 2};
    ci::gl::draw(bird_texture, ci::Rectf(top_left_of_bird_rect, bot_right_of_bird_rect));

    // draws wing
    float quarter_of_length = bird.length_ / 4;
    float tri_width = bird.width_ - (bot_right_of_bird_rect.y - top_left_of_bird_rect.y);
    vec2 point1 = {top_left_of_bird_rect.x + quarter_of_length, bot_right_of_bird_rect.y};
    vec2 point2 = {bot_right_of_bird_rect.x - quarter_of_length, bot_right_of_bird_rect.y};
    vec2 point3 = {(point1.x + point2.x) / 2, bot_right_of_bird_rect.y + tri_width};
    ci::gl::drawSolidTriangle(point1, point2, point3);
  }
}

void BirdGenerator::IncreasePositionFromVelocity() {
  // max speed for birds
  const float kMaxXSpeed = 4.f;
  const float kMaxYSpeed = 4.f;

  // checks for collisions and changes birds position based on velocity
  for (Bird& bird : all_birds_) {
    HandleWallCollisions(bird);

    // check for too fast birds
    if (bird.velocity_.x > kMaxXSpeed)
      bird.velocity_.x = kMaxXSpeed;
    if (bird.velocity_.y > kMaxYSpeed)
      bird.velocity_.y = kMaxYSpeed;

    bird.position_ += bird.velocity_;
  }
}

void BirdGenerator::HandleWallCollisions(Bird& bird) const {
  // checks for collision with left border
  if (bird.position_.x <= top_left_border_.x) {
    if (bird.velocity_.x < 0)
      bird.velocity_.x = -bird.velocity_.x;
  }

  // checks for collision with right border
  if (bird.position_.x + bird.length_ >= bottom_left_border_.x) {
    if (bird.velocity_.x > 0)
      bird.velocity_.x = -bird.velocity_.x;
  }

  // checks for collision with top or bottom border
  if (bird.position_.y <= top_left_border_.y) {
    if (bird.velocity_.y < 0)
      bird.velocity_.y = -bird.velocity_.y;
  }

  if (bird.position_.y + bird.width_ >= bottom_left_border_.y) {
    if (bird.velocity_.y > 0)
      bird.velocity_.y = -bird.velocity_.y;
  }
}

void BirdGenerator::HandleCollisionWithBirds(vec2& person_position, vec2& person_velocity, float& person_radius) {
  for (Bird& bird : all_birds_) {
    vec2 top_left_of_bird_rect = bird.position_;
    vec2 bot_right_of_bird_rect = {bird.position_.x + bird.length_, bird.position_.y + bird.width_ / 2};
    vec2 center_of_bird = {(bot_right_of_bird_rect - top_left_of_bird_rect) / 2.f};

    // check for y in between bird's y axis border
    bool y_in_between = person_position.y + person_radius >= top_left_of_bird_rect.y &&
        person_position.y - person_radius <= bot_right_of_bird_rect.y;

    // check for person hitting left side of bird
    if (person_position.x + person_radius >= top_left_of_bird_rect.x &&
        person_position.x + person_radius <= bot_right_of_bird_rect.x && y_in_between) {
      if (glm::dot((person_velocity - bird.velocity_), (person_position - center_of_bird)) > 0) {
        ChangeVelocitiesAfterCollision(bird, person_position, person_velocity, 'x');
      }
    }

    // check for person hitting right side of bird
    if (person_position.x - person_radius <= bot_right_of_bird_rect.x &&
        person_position.x - person_radius >= top_left_of_bird_rect.x && y_in_between) {
      if (glm::dot((person_velocity - bird.velocity_), (person_position - center_of_bird)) < 0) {
        ChangeVelocitiesAfterCollision(bird, person_position, person_velocity, 'x');
      }
    }

    // check for x in between bird's x axis border
    bool x_in_between = person_position.x + person_radius >= top_left_of_bird_rect.x &&
        person_position.x - person_radius <= bot_right_of_bird_rect.x;

    // check for person hitting top side of bird
    if (person_position.y + person_radius >= top_left_of_bird_rect.y &&
        person_position.y + person_radius <= bot_right_of_bird_rect.y && x_in_between) {
      if (glm::dot((person_velocity - bird.velocity_), (person_position - center_of_bird)) > 0) {
        ChangeVelocitiesAfterCollision(bird, person_position, person_velocity, 'y');
      }
    }

    // check for person hitting bottom side of bird
    if (person_position.y - person_radius <= bot_right_of_bird_rect.y &&
        person_position.y - person_radius >= top_left_of_bird_rect.y && x_in_between) {
      if (glm::dot((person_velocity - bird.velocity_), (person_position - center_of_bird)) < 0) {
        ChangeVelocitiesAfterCollision(bird, person_position, person_velocity, 'y');
      }
    }

  }
}

void BirdGenerator::ChangeVelocitiesAfterCollision(BirdGenerator::Bird& bird, const vec2& person_position, vec2& person_velocity, const char axis_hit) {
  vec2 top_left_of_bird_rect = bird.position_;
  vec2 bot_right_of_bird_rect = {bird.position_.x + bird.length_, bird.position_.y + bird.width_ / 2};
  vec2 center_of_bird;

  // checks which axis was hit
  if (axis_hit == 'y')
    center_of_bird = {person_position.x, (bot_right_of_bird_rect.y + top_left_of_bird_rect.y) * 0.5f};
  if (axis_hit == 'x')
    center_of_bird = {(bot_right_of_bird_rect.x + top_left_of_bird_rect.x) * 0.5f, person_position.y};

  CalculateNewVelocities(person_position, center_of_bird, person_velocity, bird.velocity_);
}

void BirdGenerator::GenerateBirds(const BirdGenerator::Bird &bird) {
  all_birds_.push_back(bird);
}

BirdGenerator::Bird::Bird(float length, float width, const glm::vec2 &position, const glm::vec2 &velocity)
    : length_(length), width_(width), position_(position), velocity_(velocity) {}
