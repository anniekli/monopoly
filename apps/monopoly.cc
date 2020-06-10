// Copyright (c) 2020 Annie Li. All rights reserved.

#include "monopoly.h"
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <property.h>
#include "cinder/app/MouseEvent.h"


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
  
  // create tile images
  railroad_img = cinder::gl::Texture2d::create
          (loadImage(loadAsset("railroad.png")));
  electric_img = cinder::gl::Texture2d::create
          (loadImage(loadAsset("electric.png")));
  water_img = cinder::gl::Texture2d::create
          (loadImage(loadAsset("water.png")));
  chance_img = cinder::gl::Texture2d::create
          (loadImage(loadAsset("chance.png")));
  chest_img = cinder::gl::Texture2d::create
          (loadImage(loadAsset("community-chest.png")));
}

void Monopoly::update() {
  if (player_.GetMoney() == 0) {
    state_ = GameState::kGameOver;
  
  }
}

void Monopoly::draw() {
  DrawBoard();
  
}

template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);
  
  auto box = TextBox()
          .alignment(TextBox::CENTER)
          .font(cinder::Font(kNormalFont, 18))
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
  cinder::gl::clear(background_color);
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
  cinder::gl::enableAlphaBlending();
  
  const float width = getWindowWidth();
  const float height = getWindowHeight();
  
  for (auto& tile : board_.GetTiles()) {
    
    Rectf rectf;
    cinder::ivec2 size;
  
    float position = tile->GetPosition();
    
    // draw tile outlines for each side of board
    if (position > 0 && position < 10) {
      
      rectf = Rectf(width - (tile_size_ * (position + 2)),
              height - (tile_size_ * 2),
              width - ((position + 1) * tile_size_), height);
      size = {tile_size_, 2 * tile_size_};
      
    } else if (position > 10 && position < 20) {
      
      float new_pos = position - 10;
      rectf = Rectf(0, height - (tile_size_ * (new_pos + 2)),
                    tile_size_ * 2, height - (tile_size_ * (new_pos + 1)));
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
    
    } else {
      // corners are squares -- this individually creates corner tiles
      size = {2 * tile_size_, 2 * tile_size_};
  
      if (position == 0) {
        rectf = Rectf(width - (tile_size_ * 2), height - (tile_size_ * 2),
                width, height);
        
      } else if (position == 10) {
        rectf = Rectf(0, height - (tile_size_ * 2),tile_size_ * 2, height);
        
      } else if (position == 20) {
        rectf = Rectf(0, 0, tile_size_ * 2, tile_size_ * 2);
        
      } else if (position == 30) {
        rectf = Rectf(width - (tile_size_ * 2), 0,
                      width, tile_size_ * 2);
      }
    }
    cinder::gl::color(Color::black());
    cinder::gl::drawStrokedRect(rectf);
    
    // get name and price for corresponding tiles
    std::stringstream ss;
    ss << tile->GetName() << std::endl;
  
    std::stringstream price_ss;
    price_ss << "$" << tile->GetPrice();
  
    Rectf image_coord = {rectf.getCenter().x - (tile_size_ / 4),
                         rectf.getCenter().y - (tile_size_ / 4),
                         rectf.getCenter().x + (tile_size_ / 4),
                         rectf.getCenter().y + (tile_size_ / 4)};
    
    // draw image on railroad, utility, and special tiles
    // only railroad and utility have prices
    if (tile->GetGroup() == railroad || tile->GetGroup() == utility) {
      if (tile->GetGroup() == railroad) {
        cinder::gl::draw(railroad_img, image_coord);
        
      } else if (tile->GetName() == electricity) {
        cinder::gl::draw(electric_img, image_coord);
        
      } else {
        // this is water works
        cinder::gl::draw(water_img, image_coord);
      }
      
      //print name and price around the image
      if ((position > 10 && position < 20) || (position > 30)) {
        PrintText(ss.str(), Color::black(), size,
                {rectf.getCenter().x,rectf.getCenter().y - (tile_size_ / 3)});
        PrintText(price_ss.str(), Color::black(), size,
                {rectf.getCenter().x,rectf.getCenter().y + (tile_size_ / 3)});
      } else {
        PrintText(ss.str(), Color::black(), size,
                {rectf.getCenter().x, rectf.getCenter().y - (tile_size_ / 2)});
        PrintText(price_ss.str(), Color::black(), size,
                {rectf.getCenter().x, rectf.getCenter().y + (tile_size_ / 2)});
      }
      
    } else if (tile->GetGroup() == special) {
      if (tile->GetName() == chance) {
        cinder::gl::draw(chance_img, image_coord);
      
      } else if (tile->GetName() == chest) {
        cinder::gl::draw(chest_img, image_coord);
      }
  
      // if special tile, there is no price, so only print the name
      if ((position > 10 && position < 20) || (position > 30)) {
        PrintText(ss.str(), Color::black(), size,
                {rectf.getCenter().x, rectf.getCenter().y - (tile_size_ / 3)});
      } else {
        PrintText(ss.str(), Color::black(), size,
                  {rectf.getCenter().x, rectf.getCenter().y - (tile_size_ / 2)});
      }
  
    } else {
      // if this statement executes, the tile is a street and doesn't have
      // an image, but it does have colors
  
      // print colors on tiles
      Property *property = dynamic_cast<Property*>(tile);
      Rectf color_rectf;
  
      if (position < 10) {
        color_rectf = Rectf(rectf.x1, rectf.y1, rectf.x2,
                rectf.y1 + (tile_size_ / 3));
    
      } else if (position > 10 && position < 20) {
        color_rectf = Rectf(rectf.x2 - (tile_size_ / 3),
                            rectf.y1, rectf.x2, rectf.y2);
    
      } else if (position > 20 && position < 30) {
        color_rectf = Rectf(rectf.x1, rectf.y2 - (tile_size_ / 3),
                rectf.x2, rectf.y2);
    
      } else {
        color_rectf = Rectf(rectf.x1, rectf.y1,
                rectf.x1 + (tile_size_ / 3), rectf.y2);
      }
      
      cinder::gl::color(property->GetColor());
      cinder::gl::drawSolidRect(color_rectf);
      cinder::gl::color(Color::black());
      cinder::gl::drawStrokedRect(color_rectf);
      
      // print name and price normally
      ss << "\n" << price_ss.str();
      PrintText(ss.str(), Color::black(), size, rectf.getCenter());
    }
  }
}

void Monopoly::keyDown(KeyEvent event) { }

void Monopoly::mouseDown(cinder::app::MouseEvent event) {

}

}  // namespace monopoly
