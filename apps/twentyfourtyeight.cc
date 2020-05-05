// Copyright (c) 2020 [Your Name]. All rights reserved.

#pragma once

#include "twentyfourtyeight.h"

#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <mylibrary/database.h>
#include <mylibrary/gameboard.h>
#include <cinder/audio/Voice.h>

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
    color_mode_{kLightMode},
    state_{} {}

void MyApp::setup() {
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load( cinder::app::loadAsset( "background.wav" ) );
  music_ = cinder::audio::Voice::create( sourceFile );
  music_->start();
  // Sets board to empty board
  gameboard.SetInitialBoard();
  state_ = GameState::kPlaying;
  timer.start();
  // Game begins with two blocks on the board
  gameboard.AddRandomBlock();
  gameboard.AddRandomBlock();
}

void MyApp::update() {
  // If game is over, add stats to leaderboard
  if (state_ == GameState::kWinner || state_ == GameState::kLoser) {
    timer.stop();
    state_ = GameState::kShowLeaderboard;
    if (high_scores_.empty()) {
      const size_t player_score_ = gameboard.score;
      leaderboard.AddScore({player_name_, player_score_});
      high_scores_ = leaderboard.RetrieveHighScores(3);
    }
  }

  // Loop the music
  if (!music_->isPlaying()) {
    music_->start();
  }
}

void MyApp::draw() {
  // Check for game over
  if (gameboard.Contains2048Tile()) {
    state_ = GameState::kWinner;
  }

  if (state_ == GameState::kShowLeaderboard) {
    DrawGameOver();
    return;
  }

  // If game is not over, show current board
  DrawBackground();
  DrawGameboardOutline();
  DrawBlocks();
}


void MyApp::keyDown(KeyEvent event) {

  // Copy of gameboard to check whether a move was made
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
    if (color_mode_ == kLightMode) {
      // Set to dark mode
      color_mode_ = kDarkMode;
    } else {
      // Set to light mode
      color_mode_ = kLightMode;
    }
  } else if (event.getCode() == KeyEvent::KEY_q) {
    state_ = GameState::kLoser;
  }

  if (!(copy_ == gameboard)) {
    ci::audio::SourceFileRef moveSource = ci::audio::load(ci::app::loadAsset("blip.wav"));
    move_music_ = ci::audio::Voice::create(moveSource);
    move_music_->start();
  }

}

void MyApp::DrawBackground() const {

  if (color_mode_ == kLightMode) {
    cinder::gl::clear(Color(0.831, 0.619, 0.780));
  } else if (color_mode_ == kDarkMode) {
    cinder::gl::clear(Color(0.20784f, 0.22353f, 0.25490f));
  }
  ci::vec2 size(500, 50);
  ci::vec2 location(150, 70);
  PrintText("Player: " + player_name_, size, location, color_mode_);
  PrintText("Time: " + std::to_string(timer.getSeconds()).substr(0,6) + " s",
      size, {location.x + 250, location.y}, color_mode_);
  PrintText("Score: " + std::to_string(gameboard.score), size, {location.x + 500, location.y}, color_mode_);
  PrintText("Welcome to 2048! Use the arrow keys to play!", {700, 50}, {400, 750}, color_mode_);

}

void MyApp::PrintText(const std::string& text, const cinder::ivec2& size,
                      const cinder::vec2& loc, const int mode_) {

  Color color;
  if (mode_ == kLightMode) {
    Color light{0.42f, 0.48f, 0.55f};
    color = light;
  } else if (mode_ == kDarkMode) {
    Color dark{.999,.999,.999};
    color = dark;
  }

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
  cinder::gl::color(0.992, 0.925, 0.937);
  cinder::gl::drawSolidRect(cinder::Rectf(ci::vec2{95,95}, ci::vec2{705,705}));
  //y = 100 to y = 700
  //x = 100 to x = 700
  cinder::gl::color(0.42f,0.48f,0.55f);
  cinder::gl::drawStrokedRect(cinder::Rectf(ci::vec2{100,100}, ci::vec2{700,700}));
  // Horizontal lines
  cinder::gl::drawLine(ci::vec2{kStartPixel, kStartPixel + kBlockSizePixel},
      ci::vec2{kEndPixel, kStartPixel + kBlockSizePixel});
  cinder::gl::drawLine(ci::vec2{kStartPixel, 400}, ci::vec2{kEndPixel, 400});
  cinder::gl::drawLine(ci::vec2{kStartPixel, 550}, ci::vec2{kEndPixel, 550});
  // Vertical lines
  cinder::gl::drawLine(ci::vec2{250, kStartPixel}, ci::vec2{250, kEndPixel});
  cinder::gl::drawLine(ci::vec2{400, kStartPixel}, ci::vec2{400, kEndPixel});
  cinder::gl::drawLine(ci::vec2{550, kStartPixel}, ci::vec2{550, kEndPixel});

}
void MyApp::DrawBlocks() {

  for (int row = 0; row < gameboard.kBoardSize; row++) {
    for (int col = 0; col < gameboard.kBoardSize; col++) {

      // Prints all non-0 blocks
      if (gameboard.board[row][col].value != 0) {

        std::vector<int> x_points = gameboard.GetRowPixelVal(row);
        std::vector<int> y_points = gameboard.GetColumnPixelVal(col);

        cinder::gl::color(gameboard.board[row][col].GetColor(color_mode_));
        cinder::gl::drawSolidRect(Rectf(x_points[0], y_points[0], x_points[1], y_points[1]));
        ci::vec2 size(150, 150);
        PrintText(std::to_string(gameboard.board[row][col].value), size, {x_points[0] + 70, y_points[1] - 20}, color_mode_);

      }
    }
  }

}
void MyApp::DrawGameOver() {
  cinder::gl::clear(Color(0.694, 0.305, 0.270));
  const cinder::vec2 start = {getWindowCenter().x, getWindowCenter().y - 300};
  const cinder::ivec2 size = {700, 50};
  size_t row = 0;

  PrintText("Game Over!", size, start, color_mode_);
  for (const Player& player : high_scores_) {
    std::stringstream ss;
    ss << player.name << " - " << player.score;
    PrintText(ss.str(), size, {start.x, start.y + (++row) * 50}, color_mode_);
  }

  row += 2;

  if (gameboard.Contains2048Tile()) {
    PrintText("You won!", size, {start.x, start.y + (++row) * 50}, color_mode_);
    PrintText("You: " + player_name_ + " - " + std::to_string(gameboard.score)
        + " - " + std::to_string(timer.getSeconds()).substr(0,6), size, {start.x, start.y + (++row) * 50}, color_mode_);
  } else {
    PrintText("You lost!", size, {start.x, start.y + (++row) * 50}, color_mode_);
    PrintText("Your stats: " + player_name_ + " - " + std::to_string(gameboard.score)
    + " - " + std::to_string(timer.getSeconds()).substr(0,6) + " s", size, {start.x, start.y + (++row) * 50}, color_mode_);
  }

}

}  // namespace myapp
