// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <sqlite_modern_cpp.h>

#include <string>

namespace mylibrary {

  /**
   * All database code and Player struct from SNAKE ASSIGNMENT
   */

  struct Player {
    Player(const std::string& name, size_t score) : name(name), score(score) {}
    std::string name;
    size_t score;
  };

  class Leaderboard {
   public:
    explicit Leaderboard(const std::string& database_path);
    void AddScore(const Player player);
    std::vector<Player> RetrieveHighScores(const size_t limit);

   private:
    sqlite::database database;
  };
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
