// Copyright (c) 2020 [Your Name]. All rights reserved.

#pragma once

#include <mylibrary/database.h>

namespace mylibrary {

  Leaderboard::Leaderboard(const std::string& database_path) : database{database_path}{
    database << "CREATE TABLE if not exists twentyfourtyeight (\n"
           "  name  TEXT NOT NULL,\n"
           "  score INTEGER NOT NULL\n"
           ");";
  }

  void Leaderboard::AddScore(const Player& player) {
    database << "INSERT INTO twentyfourtyeight (name, score) VALUES (?,?);"
             << player.name
             << player.score;
  }

  std::vector<Player> GetPlayers(sqlite::database_binder* rows) {
    std::vector<Player> players;

    for (auto&& row : *rows) {
      std::string name;
      size_t score;
      row >> name >> score;
      Player player = {name, score};
      players.push_back(player);
    }

    return players;
  }

  std::vector<Player> Leaderboard::RetrieveHighScores(size_t limit) {
    auto rows = database << "SELECT name, score "
                       "FROM twentyfourtyeight "
                       "ORDER BY score DESC "
                       "LIMIT ?;"
                    << limit;

    return GetPlayers(&rows);
  }

}  // namespace mylibrary
