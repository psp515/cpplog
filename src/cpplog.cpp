//
// Created by psp515 on 23.03.2025.
//

#include <memory>
#include <cpplog/cpplog.h>
#include <cpplog/logger.h>

using namespace cpplog;

#include <cpplog/cpplog.h>

std::unique_ptr<Logger> CppLog::instance = std::make_unique<Logger>(DEBUG);
