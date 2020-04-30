// Copyright (c) 2020 [Your Name]. All rights reserved.

#pragma once

#include "my_app.h"

#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <mylibrary/database.h>
#include <mylibrary/gameboard.h>

namespace myapp {

using namespace mylibrary;
using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;

DECLARE_string(name);

MyApp::MyApp():
    player_name_{FLAGS_name},
    leaderboard{cinder::app::getAssetPath("twentyfourtyeight.db").string()},
    gameboard{},
    color_mode_{0},
    state_{} {}

void MyApp::setup() {
  gameboard.SetBoardSize();
  state_ = GameState::kPlaying;
  timer.start();
  // Game begins with two blocks on the board
  gameboard.AddRandomBlock();
  gameboard.AddRandomBlock();
}

void MyApp::update() {
  if (state_ == GameState::kWinner || state_ == GameState::kLoser) {
    timer.stop();
    state_ = GameState::kShowLeaderboard;
    if (high_scores_.empty()) {
      const size_t player_score_ = gameboard.score;
      leaderboard.AddScore({player_name_, player_score_});
      high_scores_ = leaderboard.RetrieveHighScores(3);
    }
  }
}

void MyApp::draw() {
  if (gameboard.Contains2048Tile()) {
    state_ = GameState::kWinner;
  }

  if (state_ == GameState::kShowLeaderboard) {
    cinder::gl::clear(Color(0,0,1));
    DrawGameOver();
    return;
  }

  cinder::gl::clear();
  DrawBackground();
  DrawGameboardOutline();
  DrawBlocks();
}


void MyApp::keyDown(KeyEvent event) {
  Gameboard copy_ = gameboard;
  if (event.getCode() == KeyEvent::KEY_UP) {
    gameboard.MoveUp();
    // If board is still full after move is made and before
    // tile is added, game is over
    if (gameboard.GetRandomEmptyPosition().empty()
          && !gameboard.Contains2048Tile()) {
      state_ = GameState::kLoser;
    } else if (!(gameboard == copy_)) {
      // Don't add block if copy of board is the same
      gameboard.AddRandomBlock();
    }
  } else if (event.getCode() == KeyEvent::KEY_DOWN) {
    gameboard.MoveDown();
    if (gameboard.GetRandomEmptyPosition().empty()
        && !gameboard.Contains2048Tile()) {
      state_ = GameState::kLoser;
    } else if (!(gameboard == copy_)) {
      gameboard.AddRandomBlock();
    }
  } else if (event.getCode() == KeyEvent::KEY_RIGHT) {
    gameboard.MoveRight();
    if (gameboard.GetRandomEmptyPosition().empty()
        && !gameboard.Contains2048Tile()) {
      state_ = GameState::kLoser;
    } else if (!(gameboard == copy_)) {
      gameboard.AddRandomBlock();
    }
  } else if (event.getCode() == KeyEvent::KEY_LEFT) {
    gameboard.MoveLeft();
    if (gameboard.GetRandomEmptyPosition().empty()
        && !gameboard.Contains2048Tile()) {
      state_ = GameState::kLoser;
    } else if (!(gameboard == copy_)) {
      gameboard.AddRandomBlock();
    }
  } else if (event.getCode() == KeyEvent::KEY_m) {
    if (color_mode_ == 0) {
      color_mode_ = 1;
    } else {
      color_mode_ = 0;
    }
  } else if (event.getCode() == KeyEvent::KEY_q) {
    state_ = GameState::kLoser;
  }

}

void MyApp::DrawBackground() const {

  cinder::gl::clear(Color(0.811, 0.847, 0.843));
  ci::vec2 size(500, 50);
  ci::vec2 location(150, 70);
  PrintText("Player: " + player_name_, size, location);
  PrintText("Time " + std::to_string(timer.getSeconds()), size, {location.x + 250, location.y});
  PrintText("Score: " + std::to_string(gameboard.score), size, {location.x + 500, location.y});
  PrintText("Welcome to 2048! Use the arrow keys to play!", {700, 50}, {400, 750});

}

void MyApp::PrintText(const std::string& text, const cinder::ivec2& size,
                      const cinder::vec2& loc) {

  Color color(0.42f,0.48f,0.55f);
  cinder::gl::color(color);
  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font("Arial", 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);

}

void MyApp::DrawGameboardOutline() const {

  //y = 100 to y = 700
  //x = 100 to x = 700
  cinder::gl::color(0.42f,0.48f,0.55f);
  cinder::gl::drawStrokedRect(cinder::Rectf(ci::vec2{100,100}, ci::vec2{700,700}));
  // Horizontal lines
  cinder::gl::drawLine(ci::vec2{100, 250}, ci::vec2{700, 250});
  cinder::gl::drawLine(ci::vec2{100, 400}, ci::vec2{700, 400});
  cinder::gl::drawLine(ci::vec2{100, 550}, ci::vec2{700, 550});
  // Vertical lines
  cinder::gl::drawLine(ci::vec2{250, 100}, ci::vec2{250, 700});
  cinder::gl::drawLine(ci::vec2{400, 100}, ci::vec2{400, 700});
  cinder::gl::drawLine(ci::vec2{550, 100}, ci::vec2{550, 700});

}
void MyApp::DrawBlocks() {

  for (int row = 0; row < gameboard.kBoardSize; row++) {
    for (int col = 0; col < gameboard.kBoardSize; col++) {

      if (gameboard.board[row][col].value != 0) {

        std::vector<int> x_points = gameboard.GetRowPixelVal(row);
        std::vector<int> y_points = gameboard.GetColumnPixelVal(col);

        cinder::gl::color(gameboard.board[row][col].GetColor(color_mode_));
        cinder::gl::drawSolidRect(Rectf(x_points[0], y_points[0], x_points[1], y_points[1]));
        ci::vec2 size(150, 150);
        PrintText(std::to_string(gameboard.board[row][col].value), size, {x_points[0] + 70, y_points[1] - 20});

      }
    }
  }

}
void MyApp::DrawGameOver() {

  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  size_t row = 0;

  PrintText("Game Over", size, center);
  for (const Player& player : high_scores_) {
    std::stringstream ss;
    ss << player.name << " - " << player.score;
    PrintText(ss.str(), size, {center.x, center.y + (++row) * 50});
  }

  row += 2;

  if (gameboard.Contains2048Tile()) {
    PrintText("You won!", size, {center.x, center.y + (++row) * 50});
    PrintText("You: " + player_name_ + " - " + std::to_string(gameboard.score), size, {center.x, center.y + (++row) * 50});
  } else {
    PrintText("You lost!", size, {center.x, center.y + (++row) * 50});
    PrintText("Your stats: " + player_name_ + " - " + std::to_string(gameboard.score)
    + " - " + std::to_string(timer.getSeconds()) + " s", size, {center.x, center.y + (++row) * 50});
  }

}

}  // namespace myapp
