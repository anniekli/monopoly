// Copyright (c) 2020 Annie Li. All rights reserved.

#include "monopoly.h"
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>



namespace monopoly {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::Rectf;

DECLARE_uint32(speed);
DECLARE_string(name);
DECLARE_string(file);
DECLARE_bool(collect_go);
DECLARE_uint32(num_cpu);

Monopoly::Monopoly()
  : board_{FLAGS_file}
  {}

void Monopoly::setup() {

}

void Monopoly::update() { }

void Monopoly::draw() {
  cinder::gl::clear(background_color);
  DrawBoard();
  
}

void Monopoly::DrawBoard() {
  cinder::gl::color(Color::black());
  int width = getWindowWidth();
  int height = getWindowHeight();
  
  for (auto& tile : board_.GetTiles()) {
    
    Rectf rectf;
    int position = tile.GetPosition();
    std::cout << position << std::endl;
    
    if (position >= 0 && position <= 10) {
      rectf = Rectf(width - (tile_size * (position + 1)),
              height - (tile_size * 2),
              width - (position * tile_size),
              height);
    }
    cinder::gl::drawStrokedRect(rectf);
  
  }
}

void Monopoly::keyDown(KeyEvent event) { }

}  // namespace monopoly
