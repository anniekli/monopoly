// Copyright (c) 2020 Annie Li. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>
#include "monopoly.h"

using cinder::app::App;
using cinder::app::RendererGl;

namespace monopoly {
  
  DEFINE_uint32(speed, 50, "the speed (delay) of the game");
  DEFINE_string(name, "Annie", "the name of the player");
  DEFINE_string(file, "classic-board.json", "the filepath of the json file "
                                      "containing checkpoints");
  DEFINE_bool(collect_go, true, "whether to collect $200 when passing go");
  DEFINE_uint32(num_cpu, 1, "the number of computer players");
  
  
  void ParseArgs(vector<string>* args) {
    gflags::SetUsageMessage(
            "Play a game of Monopoly. Pass --helpshort for options.");
    int argc = static_cast<int>(args->size());
    
    vector<char*> argvs;
    for (string& str : *args) {
      argvs.push_back(&str[0]);
    }
    
    char** argv = argvs.data();
    gflags::ParseCommandLineFlags(&argc, &argv, true);
  }

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  vector<string> args = settings->getCommandLineArgs();
  ParseArgs(&args);
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("Monopoly");
}

}  // namespace monopoly

// This is a macro that runs the application.
CINDER_APP(monopoly::Monopoly,
           RendererGl(RendererGl::Options().msaa(monopoly::kSamples)),
           monopoly::SetUp)
