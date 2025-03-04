//
// Created by psp515 on 04.03.2025.
//

#ifndef BASE_BUILDER_H
#define BASE_BUILDER_H

#include <cpplog/logger_builder.h>

namespace cpplog {
  namespace builders {
    class BaseBuilder : public LoggerBuilder {
    public:
    BaseBuilder();
     void add_sink(Sink sink) override;

    };
  }
}

#endif //BASE_BUILDER_H
