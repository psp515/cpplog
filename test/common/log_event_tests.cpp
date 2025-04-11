//
// Created by kolbe on 10.04.2025.
//

#include <gtest/gtest.h>
#include <chrono>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_level.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>

using namespace cpplog::common;

// Test case
TEST(EventHasSource, CreatesDataInFile) {

}

class Generator {

private:

    int Aktualny;

public: Generator(int i = 10) : Aktualny(i) { }

    int operator ()()

{

    Aktualny += 10;

    return Aktualny;

}

};

int main(int argc, char* argv[])

{

    Generator g(10);

    do {

        std::cout << '.';

    } while (g() < 101);

}