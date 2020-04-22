// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/database.h>

namespace mylibrary {

  Leaderboard::Leaderboard(const std::string& database_path) : database{database_path}{
    database << "CREATE TABLE if not exists twentyfourtyeight (\n"
           "  name  TEXT NOT NULL,\n"
           "  score INTEGER NOT NULL\n"
           ");";
  }

  void Leaderboard::AddScore(const std::string& player_name_, int player_score_) {
    database << "INSERT INTO twentyfourtyeight (name, score) VALUES (?,?);"
             << player_name_
             << player_score_;
  }

}  // namespace mylibrary
