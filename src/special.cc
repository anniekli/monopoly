//
// Created by GWC-CHC-07 on 6/9/2020.
//

#include <cinder/app/AppBase.h>
#include <cinder/Rect.h>
#include "special.h"

namespace monopoly {
  
  cinder::Rectf Special::GetRectf() const {
    const float width = cinder::app::getWindowWidth();
    const float height = cinder::app::getWindowHeight();
    
    cinder::Rectf rectf;
    
    if (position_ > 0 && position_ < 10) {
      
      rectf = cinder::Rectf(width - (tile_size_ * (position_ + 2)),
                    height - (tile_size_ * 2),
                    width - ((position_ + 1) * tile_size_), height);
      
    } else if (position_ > 10 && position_ < 20) {
      
      float new_pos = position_ - 10;
      rectf = cinder::Rectf(0, height - (tile_size_ * (new_pos + 2)),
                    tile_size_ * 2, height - (tile_size_ * (new_pos + 1)));
      
    } else if (position_ > 20 && position_ < 30) {
      
      float new_pos = position_ - 20;
      rectf = cinder::Rectf(tile_size_ * (new_pos + 1), 0,
                    tile_size_ * (new_pos + 2), tile_size_ * 2);
      
    } else if (position_ > 30) {
      
      float new_pos = position_ - 30;
      rectf = cinder::Rectf(width - (tile_size_ * 2),
                    tile_size_ * (new_pos + 1),
                    width, tile_size_ * (new_pos + 2));
      
    } else {
      // corners are squares -- this individually creates corner tiles
      
      if (position_ == 0) {
        rectf = cinder::Rectf(width - (tile_size_ * 2), height - (tile_size_ * 2),
                      width, height);
        
      } else if (position_ == 10) {
        rectf = cinder::Rectf(0, height - (tile_size_ * 2), tile_size_ * 2, height);
        
      } else if (position_ == 20) {
        rectf = cinder::Rectf(0, 0, tile_size_ * 2, tile_size_ * 2);
        
      } else if (position_ == 30) {
        rectf = cinder::Rectf(width - (tile_size_ * 2), 0,
                      width, tile_size_ * 2);
      }
    }
    return rectf;
  }
  
  cinder::ivec2 Special::GetTileVec() const {
    cinder::ivec2 size;
    
    if ((position_ > 0 && position_ < 10) ||
        (position_ > 20 && position_ < 30)) {
      size = {tile_size_, 2 * tile_size_};
      
    } else if ((position_ > 10 && position_ < 20) || (position_ > 30)) {
      size = {2 * tile_size_, tile_size_};
      
    } else {
      size = {2 * tile_size_, 2 * tile_size_};
    }
    
    return size;
  }
}
