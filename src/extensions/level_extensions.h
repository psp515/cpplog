//
// Created by psp515 on 08.03.2025.
//

#ifndef LEVEL_EXTENSIONS_H
#define LEVEL_EXTENSIONS_H

#include <string>
#include <cpplog/common/level.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog::extensions {
  class LevelExtensions {
  public:
    static string level_name(level level);
  };
}

#endif //LEVEL_EXTENSIONS_H
