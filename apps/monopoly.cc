// Copyright (c) 2020 Annie Li. All rights reserved.

#include "monopoly.h"
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <Tile/property.h>
#include <random>
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
DECLARE_string(piece);
DECLARE_bool(collect_go);
DECLARE_uint32(num_cpu);

Monopoly::Monopoly()
  : board_{FLAGS_file},
    state_{GameState::kStart},
    num_cpu_{FLAGS_num_cpu}
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
  
  // set piece for all players
  dog_img = cinder::gl::Texture2d::create(loadImage(loadAsset("dog.png"))),
  iron_img = cinder::gl::Texture2d::create(loadImage(loadAsset("iron.png"))),
  boat_img = cinder::gl::Texture2d::create(loadImage(loadAsset("boat.png"))),
  wheelbarrow_img = cinder::gl::Texture2d::create(loadImage(loadAsset("wheelbarrow.png")));
  
  if (FLAGS_piece == "dog") {
    player_ = Player(FLAGS_name, dog_img);
  } else if (FLAGS_piece == "iron") {
    player_ = Player(FLAGS_name, iron_img);
  } else if (FLAGS_piece == "boat") {
    player_ = Player(FLAGS_name, boat_img);
  } else {
    player_ = Player(FLAGS_name, wheelbarrow_img);
  }
  
  // set all player positions to 0
  player_.SetPosition(0);
  
}

void Monopoly::update() {
  if (player_.GetMoney() == 0) {
    state_ = GameState::kGameOver;
  }
  if (state_ == GameState::kPlayerTurn) {
    // if user rolls dice
    if (is_roll_btn_clicked_) {
      RollDice();
      size_t dice = die_one + die_two;
      player_.UpdatePosition(dice);
      is_roll_btn_clicked_ = false;
      
    } else if (is_player_position_updated_) {
      
      // if both player position member variable and onscreen position have
      // been updated, check if tile is a property
      if (board_.GetTileAtPos(player_.GetPosition())->GetGroup() != g_special) {
        Property *property = dynamic_cast<Property*> (board_.GetTileAtPos
                (player_.GetPosition()));
        
        if (property->GetOwner() == -1) {
          // if player lands on property that isn't owned, allow buying option
//          BuyProperty();
        
        } else if (property->GetOwner() != 0 && !is_rent_paid_) {
//          player_.AddMoney(-(property->GetRent()));
          is_rent_paid_ = true;
        }
        
      } else {
        // if tile is not a property, continue accordingly
        
        if (board_.GetTileAtPos(player_.GetPosition())->GetName() ==
        g_go_to_jail) {
          player_.SetPosition(board_.GetJailPosition());
        
        } else if (board_.GetTileAtPos(player_.GetPosition())->GetName() ==
        g_chance && !is_card_drawn_) {
//          board_.GetChanceCard();
//          DrawCard();
          
          is_card_drawn_ = true;
        
        } else if (board_.GetTileAtPos(player_.GetPosition())->GetName() ==
                g_chest && !is_card_drawn_) {
//          board_.GetChestCard();
//          DrawCard();
  
          is_card_drawn_ = true;
        }
      }
    }
  }
}

void Monopoly::draw() {
  DrawBoard();
  
  switch (state_) {
    case GameState::kPlayerStart :
//      DrawDice();
    
    case GameState::kPlayerTurn :
      if (!is_player_position_updated_) {
      
      } else if (is_player_position_updated_) {
        if (board_.GetTileAtPos(player_.GetPosition())->GetGroup() != g_special) {
          Property *property = dynamic_cast<Property*> (board_.GetTileAtPos
                  (player_.GetPosition()));
          if (property->GetOwner() == -1) {
//            DrawBuyProperty();
          
          } else if (property->GetOwner() != 0) {
//            DrawPayRent();
          }
        }
      }
  }
  
}

void Monopoly::RollDice() {
  std::random_device rand_dev;
  std::mt19937 rng(rand_dev());
  std::uniform_int_distribution<std::mt19937::result_type> one(1,6);
  std::uniform_int_distribution<std::mt19937::result_type> two(1,6);
  
  die_one = one(rng);
  die_two = two(rng);
}

void Monopoly::BuyProperty() {

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
  
  for (auto& tile : board_.GetTiles()) {
    Rectf rectf = tile->GetRectf();
    float position = tile->GetPosition();
    cinder::ivec2 size = tile->GetTileVec();
    
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
    
    // draw image on g_railroad, utility, and special tiles
    // only g_railroad and utility have prices
    if (tile->GetGroup() == g_railroad || tile->GetGroup() == g_utility) {
      if (tile->GetGroup() == g_railroad) {
        cinder::gl::draw(railroad_img, image_coord);
        
      } else if (tile->GetName() == g_electricity) {
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
      
    } else if (tile->GetGroup() == g_special) {
      if (tile->GetName() == g_chance) {
        cinder::gl::draw(chance_img, image_coord);
      
      } else if (tile->GetName() == g_chest) {
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

void Monopoly::DrawPlayerPieces() {

}

void Monopoly::DrawUpdateCurrentPlayerPosition() {

}

void Monopoly::DrawCard() {

}

void Monopoly::DrawBuyProperty() {

}

void Monopoly::DrawPayRent() {

}

void Monopoly::DrawDice() {

}

void Monopoly::DrawRollButton() {
}

void Monopoly::keyDown(KeyEvent event) { }

void Monopoly::mouseDown(cinder::app::MouseEvent event) {

}



}  // namespace monopoly
