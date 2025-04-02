//
// Created by psp515 on 23.03.2025.
//

#include <cpplog/common/level.h>
#include <cpplog/cpplog.h>
#include <cpplog/logger_configurator.h>
#include <gtest/gtest.h>

#include "mocks/mock_sink.h"

using namespace std;
using namespace cpplog;
using namespace cpplog::mocks;
using namespace cpplog::common;

TEST(LoggerTest, DebugLoggedNoConifgure) {
	// Arrange
	auto sink = make_unique<MockSink>();
	const auto logs = sink->get_logs();
	LoggerConfigurator configurator;
	const auto logger = configurator.set_ignore_level(DEBUG)
		.add_sink(std::move(sink))
		.build();

	// Act
	logger->debug("Debug logged");

	// Assert
	ASSERT_TRUE(logs->at(0).get_level() == DEBUG);
}

TEST(LoggerTest, DebugLogged) {
	// Arrange
	auto sink = make_unique<MockSink>();
	const auto logs = sink->get_logs();
	LoggerConfigurator configurator;
	configurator.set_ignore_level(DEBUG)
		.add_sink(std::move(sink))
		.configure();

	// Act
	CppLog::debug("Debug logged");

	// Assert
	ASSERT_TRUE(logs->at(0).get_level() == DEBUG);
}

TEST(LoggerTest, InfoLoggedLowerNot) {
	// Arrange
	auto sink = make_unique<MockSink>();
	const auto logs = sink->get_logs();
	LoggerConfigurator configurator;
	configurator.set_ignore_level(INFO)
		.add_sink(std::move(sink))
		.configure();

	// Act
	CppLog::debug("Debug logged");
	CppLog::info("Info logged");

	// Assert
	ASSERT_TRUE(logs->at(0).get_level() == INFO);
}

TEST(LoggerTest, WarningLoggedLowerNot) {
	// Arrange
	auto sink = make_unique<MockSink>();
	const auto logs = sink->get_logs();
	LoggerConfigurator configurator;
	configurator.set_ignore_level(WARNING)
		.add_sink(std::move(sink))
		.configure();

	// Act
	CppLog::debug("Debug logged");
	CppLog::info("Info logged");
	CppLog::warning("Warning logged");

	// Assert
	ASSERT_TRUE(logs->at(0).get_level() == WARNING);
}

TEST(LoggerTest, ErrorLoggedLowerNot) {
	// Arrange
	auto sink = make_unique<MockSink>();
	const auto logs = sink->get_logs();
	LoggerConfigurator configurator;
	configurator.set_ignore_level(ERROR)
		.add_sink(std::move(sink))
		.configure();

	// Act
	CppLog::debug("Debug logged");
	CppLog::info("Info logged");
	CppLog::warning("Warning logged");
	CppLog::error("Error logged");

	// Assert
	ASSERT_TRUE(logs->at(0).get_level() == ERROR);
}

TEST(LoggerTest, CriticalLoggedLowerNot) {
	// Arrange
	auto sink = make_unique<MockSink>();
	const auto logs = sink->get_logs();
	LoggerConfigurator configurator;
	configurator.set_ignore_level(CRITICAL)
		.add_sink(std::move(sink))
		.configure();

	// Act
	CppLog::debug("Debug logged");
	CppLog::info("Info logged");
	CppLog::warning("Warning logged");
	CppLog::error("Error logged");
	CppLog::critical("Critical logged");

	// Assert
	ASSERT_TRUE(logs->at(0).get_level() == CRITICAL);
}