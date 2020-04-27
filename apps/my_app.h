// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/database.h>
#include <mylibrary/gameboard.h>


namespace myapp {

using namespace mylibrary;

enum class GameState {
  kPlaying,
  kWinner,
  kLoser,
  kShowLeaderboard
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;


 private:
  const std::string player_name_;
  mylibrary::Leaderboard leaderboard;
  Gameboard gameboard;
  int color_mode_;
  GameState state_;
  /**
   * Print text function FROM SNAKE ASSIGNMENT
   * @param text - string with desired text to be printed
   * @param size - size of textbox
   * @param loc - location of textbox
   */
  static void PrintText(const std::string& text, const cinder::ivec2& size,
                        const cinder::vec2& loc);
  void DrawBackground() const;
  void DrawGameboardOutline() const;
  void DrawBlocks();
  void DrawGameOver();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
