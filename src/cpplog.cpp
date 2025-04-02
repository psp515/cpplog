//
// Created by psp515 on 23.03.2025.
//

#include <cpplog/cpplog.h>
#include <cpplog/logger.h>
#include <memory>

using namespace cpplog;

#include <cpplog/cpplog.h>

std::unique_ptr<Logger> CppLog::instance = std::make_unique<Logger>(DEBUG);
