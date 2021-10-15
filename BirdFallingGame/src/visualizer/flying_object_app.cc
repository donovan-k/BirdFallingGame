//
// Created by donov on 4/16/2021.
//

#include "../../include/visualizer/flying_object_app.h"

using skydiving::visualizer::FlyingObjectApp;

FlyingObjectApp::FlyingObjectApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  ci::app::setFrameRate(kFrameRate);

  game_engine_.SetRatesForCalculations(kFrameRate);
}

void FlyingObjectApp::draw() {
  ci::Color background_color(0.70f, 0.9f, 1.f);
  ci::gl::clear(background_color);

  game_engine_.Display();
}

void FlyingObjectApp::update() {
  game_engine_.AdvanceOneFrame();
}

void FlyingObjectApp::keyDown(ci::app::KeyEvent event) {
  game_engine_.ProcessKey(event);
}
