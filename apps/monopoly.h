// Copyright (c) 2020 Annie Li. All rights reserved.

#ifndef MONOPOLY_MONOPOLY_H_
#define MONOPOLY_MONOPOLY_H_

#include <cinder/app/App.h>
#include <nlohmann/json.hpp>
#include <board.h>

using std::vector;
using std::string;
using json = nlohmann::json;
using cinder::Color;

namespace monopoly {

class Monopoly : public cinder::app::App {
 public:
  Monopoly();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  
private:
  void DrawBoard();
  
  Board board_;
  
  float tile_size = getWindowWidth() / 15;
  Color background_color = Color(191/255.0f, 219/255.0f, 174/255.0f);
};
}  // namespace monopoly

#endif  // MONOPOLY_MONOPOLY_H_
