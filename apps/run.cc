// Copyright (c) 2020 Annie Li. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "monopoly.h"


using cinder::app::App;
using cinder::app::RendererGl;


namespace monopoly {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("Monopoly");
}

}  // namespace monopoly


// This is a macro that runs the application.
CINDER_APP(monopoly::Monopoly,
           RendererGl(RendererGl::Options().msaa(monopoly::kSamples)),
           monopoly::SetUp)
