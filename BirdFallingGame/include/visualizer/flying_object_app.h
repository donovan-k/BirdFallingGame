//
// Created by donov on 4/16/2021.
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_engine.h"

namespace skydiving {

namespace visualizer {

 class FlyingObjectApp : public ci::app::App {
 public:
  FlyingObjectApp();

  void draw() override;

  void update() override;

  void keyDown(ci::app::KeyEvent event) override;

  // So you can see the entire UI on your screen
  const int kWindowSize = 900;
  const int kMargin = 100;
  const float kFrameRate = 40.f;

 private:
   skydiving::visualizer::GameEngine game_engine_;
};

}  // namespace visualizer

}  // namespace skydiving

