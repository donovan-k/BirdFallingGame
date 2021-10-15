//
// Created by donov on 4/16/2021.
//

#include "visualizer\flying_object_app.h"

using skydiving::visualizer::FlyingObjectApp;

void prepareSettings(FlyingObjectApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(FlyingObjectApp, ci::app::RendererGl, prepareSettings);
