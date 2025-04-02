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
using namespace cpplog::sinks;
using namespace cpplog::common;

TEST(LoggerTest, DebugLogged) {
	// Arrange
	auto sink = unique_ptr<MockSink>();
	LoggerConfigurator configurator;
	configurator.set_ignore_level(DEBUG).add_sink(std::move(sink)).configure();

	// Act
	CppLog::debug("Debug logged");

	// Assert
	ASSERT_TRUE(sink->get_logs()[0].get_level() == DEBUG);
}

//TEST(LoggerTest, DebugAndLowerNotLogged) {
//	// Arrange
//	auto sink = unique_ptr<MocksSink>();
//	LoggerConfigurator configurator;
//	configurator.set_ignore_level(INFO)
//		.add_sink(std::move(sink))
//		.configure();
//
//	// Act
//	CppLog::debug("debug logged");
//	auto expected_initial = MocksSink::get_last();
//	CppLog::info("info logged");
//
//	// Assert
//	ASSERT_TRUE(expected_initial.get_message() == MocksSink::InitialMessage);
//	ASSERT_TRUE(MocksSink::get_last().get_level() == INFO);
//}
//
//TEST(LoggerTest, InfoAndLowerNotLogged) {
//	// Arrange
//	auto sink = unique_ptr<MocksSink>();
//	LoggerConfigurator configurator;
//	configurator.set_ignore_level(WARNING)
//		.add_sink(std::move(sink))
//		.configure();
//
//	// Act
//	CppLog::info("info logged");
//	auto expected_initial = MocksSink::get_last();
//	CppLog::warning("info logged");
//
//	// Assert
//	ASSERT_TRUE(expected_initial.get_message() == MocksSink::InitialMessage);
//	ASSERT_TRUE(MocksSink::get_last().get_level() == WARNING);
//}
//
//TEST(LoggerTest, WarningAndLowerNotLogged) {
//	// Arrange
//	auto sink = unique_ptr<MocksSink>();
//	LoggerConfigurator configurator;
//	configurator.set_ignore_level(ERROR)
//		.add_sink(std::move(sink))
//		.configure();
//
//	// Act
//	CppLog::warning("info logged");
//	auto expected_initial = MocksSink::get_last();
//	CppLog::error("info logged");
//
//	// Assert
//	ASSERT_TRUE(expected_initial.get_message() == MocksSink::InitialMessage);
//	ASSERT_TRUE(MocksSink::get_last().get_level() == ERROR);
//}
//
//TEST(LoggerTest, CriticalLogged) {
//	// Arrange
//	auto sink = unique_ptr<MocksSink>();
//	LoggerConfigurator configurator;
//	configurator.set_ignore_level(CRITICAL)
//		.add_sink(std::move(sink))
//		.configure();
//
//	// Act
//	CppLog::error("info logged");
//	auto expected_initial = MocksSink::get_last();
//	CppLog::critical("info logged");
//
//	// Assert
//	ASSERT_TRUE(expected_initial.get_message() == MocksSink::InitialMessage);
//	ASSERT_TRUE(MocksSink::get_last().get_level() == CRITICAL);
//}