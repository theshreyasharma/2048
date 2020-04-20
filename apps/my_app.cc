// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Common/b2Draw.h>
#include <Box2D/Dynamics/b2World.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>

namespace myapp {

using cinder::app::KeyEvent;

DECLARE_string(name);

MyApp::MyApp()
    : player_name_{FLAGS_name} {}

void MyApp::setup() {

}

void MyApp::update() { }

void MyApp::draw() {


  cinder::gl::color(1.0f,1.0f,1.0f);
  cinder::gl::drawSolidRect(cinder::Rectf(.5,.5,.7,.7));
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
