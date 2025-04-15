//
// Created by psp515 on 15.04.2025.
//

#include <memory>
#include <cpplog/cpplog.h>

using namespace std;
using namespace cpplog;

unique_ptr<Logger> CppLog::instance = make_unique<Logger>();