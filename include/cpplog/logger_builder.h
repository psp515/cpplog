//
// Created by psp515 on 04.03.2025.
//

#ifndef ILOGGERBUILDER_H
#define ILOGGERBUILDER_H

#include <cpplog/ISink.h>
#include <cpplog/ILogger.h>
#include <cpplog/common/LogLevel.h>

using namespace std;

namespace cpplog {
    class LoggerBuilder {
          public:
void add_sink(ISink sink);
                void set_target(LogLevel level);
                ILogger& build();
    };
}

#endif //ILOGGERBUILDER_H
