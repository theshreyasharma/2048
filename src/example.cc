// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Common/b2Draw.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <mylibrary/example.h>

namespace mylibrary {

  void ShowBoxLibrary() {
    b2Vec2 gravity(0.0f, 0.0f);

    b2World world(gravity);

    b2BodyDef body_def_;
    body_def_.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&body_def_);
    b2PolygonShape box;
    box.SetAsBox(50.0f, 10.0f);

  }

}  // namespace mylibrary
