// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/database.h>
#include <mylibrary/gameboard.h>
#include <cinder/audio/Voice.h>


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

  static const int kLightMode = 0;
  static const int kDarkMode = 1;

 private:
  const std::string player_name_;
  mylibrary::Leaderboard leaderboard;
  Gameboard gameboard;
  /**
   * 0 indicates light mode, 1 indicated dark mode
   */
  int color_mode_;
  GameState state_;
  std::vector<Player> high_scores_;
  cinder::Timer timer;
  ci::audio::VoiceRef music_;
  ci::audio::VoiceRef move_music_;
  /**
   * Print text function FROM SNAKE ASSIGNMENT
   * @param text - string with desired text to be printed
   * @param size - size of textbox
   * @param loc - location of textbox
   */
  static void PrintText(const std::string& text, const cinder::ivec2& size,
                        const cinder::vec2& loc, const int mode_);
  /**
   * Draws background that displays score and player name while also setting background color
   */
  void DrawBackground() const;
  /**
   * Draws the gameboard outline, which is a 600x600 pixel square split into 4x4
   */
  void DrawGameboardOutline() const;
  /**
   * Draws all the blocks that don't have value of 0
   */
  void DrawBlocks();
  /**
   * Draws leaderboard after game is over or 'q' is clicked
   */
  void DrawGameOver();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
