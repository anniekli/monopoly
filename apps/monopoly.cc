// Copyright (c) 2020 Annie Li. All rights reserved.

#include "monopoly.h"
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <property.h>
#include <utility.h>


namespace monopoly {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::Rectf;
using cinder::TextBox;


#if defined(CINDER_COCOA_TOUCH)
  const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
  const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
  const char kNormalFont[] = "Arial";
  const char kBoldFont[] = "Arial Bold";
  const char kDifferentFont[] = "Papyrus";
#endif

DECLARE_uint32(speed);
DECLARE_string(name);
DECLARE_string(file);
DECLARE_bool(collect_go);
DECLARE_uint32(num_cpu);

Monopoly::Monopoly()
  : board_{FLAGS_file},
    state_{GameState::kStart}
{}

void Monopoly::setup() {

}

void Monopoly::update() {
  if (player_.GetMoney() == 0) {
    state_ = GameState::kGameOver;
  
  }
}

void Monopoly::draw() {
  cinder::gl::clear(background_color);
  DrawBoard();
  
}

template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);
  
  auto box = TextBox()
          .alignment(TextBox::CENTER)
          .font(cinder::Font(kNormalFont, 15))
          .size(size)
          .color(color)
          .text(text);
  
  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}


void Monopoly::DrawBoard() {
  const float width = getWindowWidth();
  const float height = getWindowHeight();
  
  for (auto& tile : board_.GetTiles()) {
    
    Rectf rectf;
    cinder::ivec2 size;
  
    float position = tile->GetPosition();
    
    // draw tile outlines
    if (position > 0 && position < 10) {
      
      rectf = Rectf(width - (tile_size_ * (position + 2)),
              height - (tile_size_ * 2),
              width - ((position + 1) * tile_size_),
              height);
      
      size = {tile_size_, 2 * tile_size_};
      
    } else if (position > 10 && position < 20) {
      
      float new_pos = position - 10;
      rectf = Rectf(0, tile_size_ * (new_pos + 2),
                    tile_size_ * 2, tile_size_ * (new_pos + 1));
  
      size = {2 * tile_size_, tile_size_};
  
  
    } else if (position > 20 && position < 30) {
  
      float new_pos = position - 20;
      rectf = Rectf(tile_size_ * (new_pos + 1), 0,
                    tile_size_ * (new_pos + 2), tile_size_ * 2);
  
      size = {tile_size_, 2 * tile_size_};
  
    } else if (position > 30) {
      float new_pos = position - 30;
      rectf = Rectf(width - (tile_size_ * 2),
                    tile_size_ * (new_pos + 1),
                    width, tile_size_ * (new_pos + 2));
  
      size = {2 * tile_size_, tile_size_};
  
    }
  
    cinder::gl::color(Color::black());
    cinder::gl::drawStrokedRect(rectf);
    std::stringstream ss;
    ss << tile->GetName() << std::endl;
    if (tile->GetGroup() != "Special") {
      ss << "\n" << "$" << tile->GetPrice();
    }
    PrintText(ss.str(), Color::black(), size, rectf.getCenter());
    
    if (tile->GetGroup() != "Special"
        && tile->GetGroup() != "Utility"
        && tile->GetGroup() != "Railroad") {
      Property *property = dynamic_cast<Property*>(tile);
      Rectf color_rectf;
  
      if (position < 10) {
        color_rectf = Rectf(rectf.x1, rectf.y1, rectf.x2, rectf.y1 +
                (tile_size_ / 3));
        
      } else if (position > 10 && position < 20) {
        color_rectf = Rectf(rectf.x2 - (tile_size_ / 3),
                rectf.y1, rectf.x2, rectf.y2);
        
      } else if (position > 20 && position < 30) {
        color_rectf = Rectf(rectf.x1, rectf.y2 - (tile_size_ / 3), rectf.x2,
                rectf.y2);
        
      } else {
        color_rectf = Rectf(rectf.x1, rectf.y1, rectf.x1 + (tile_size_ / 3),
                rectf.y2);
      }
      
      cinder::gl::color(property->GetColor());
      cinder::gl::drawSolidRect(color_rectf);
    }
  
  
  }
}

void Monopoly::keyDown(KeyEvent event) { }

}  // namespace monopoly
