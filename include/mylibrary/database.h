// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <sqlite_modern_cpp.h>

#include <string>

namespace mylibrary {

  class Leaderboard {
   public:
    explicit Leaderboard(const std::string& database_path);

    void AddScore(const std::string& player_name_, int player_score_);
   private:
    sqlite::database database;
  };
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
