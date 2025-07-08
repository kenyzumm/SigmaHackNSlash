#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <chrono>
#include <iomanip>

// Simple test framework without external dependencies
class TestFramework {
public:
    struct TestCase {
        std::string name;
        std::function<void()> test;
        bool passed = false;
        std::string error_message;
    };

    struct TestSuite {
        std::string name;
        std::vector<TestCase> tests;
    };

    static TestFramework& getInstance() {
        static TestFramework instance;
        return instance;
    }

    void addTest(const std::string& suite_name, const std::string& test_name, std::function<void()> test_func) {
        // Find or create test suite
        auto it = std::find_if(suites.begin(), suites.end(), 
            [&suite_name](const TestSuite& suite) { return suite.name == suite_name; });
        
        if (it == suites.end()) {
            suites.push_back({suite_name, {}});
            it = suites.end() - 1;
        }

        it->tests.push_back({test_name, test_func});
    }

    int runAllTests() {
        std::cout << "\n🧪 Running Tests...\n" << std::string(50, '=') << "\n";
        
        int total_tests = 0;
        int passed_tests = 0;
        int failed_tests = 0;

        for (auto& suite : suites) {
            std::cout << "\n📋 Test Suite: " << suite.name << "\n" << std::string(30, '-') << "\n";
            
            for (auto& test : suite.tests) {
                total_tests++;
                std::cout << "  Running: " << test.name << " ... ";
                
                try {
                    auto start = std::chrono::high_resolution_clock::now();
                    test.test();
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    
                    test.passed = true;
                    passed_tests++;
                    std::cout << "✅ PASSED (" << duration.count() << " μs)\n";
                }
                catch (const std::exception& e) {
                    test.passed = false;
                    test.error_message = e.what();
                    failed_tests++;
                    std::cout << "❌ FAILED: " << e.what() << "\n";
                }
                catch (...) {
                    test.passed = false;
                    test.error_message = "Unknown error";
                    failed_tests++;
                    std::cout << "❌ FAILED: Unknown error\n";
                }
            }
        }

        // Print summary
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "📊 Test Summary:\n";
        std::cout << "  Total Tests: " << total_tests << "\n";
        std::cout << "  Passed: " << passed_tests << " ✅\n";
        std::cout << "  Failed: " << failed_tests << " ❌\n";
        std::cout << "  Success Rate: " << std::fixed << std::setprecision(1) 
                  << (total_tests > 0 ? (passed_tests * 100.0 / total_tests) : 0.0) << "%\n";
        std::cout << std::string(50, '=') << "\n\n";

        return failed_tests;
    }

    void clear() {
        suites.clear();
    }

private:
    std::vector<TestSuite> suites;
};

// Test assertion macros
#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        throw std::runtime_error("Assertion failed: " #condition " is not true"); \
    }

#define ASSERT_FALSE(condition) \
    if ((condition)) { \
        throw std::runtime_error("Assertion failed: " #condition " is not false"); \
    }

#define ASSERT_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        throw std::runtime_error("Assertion failed: expected " + std::to_string(expected) + \
                                ", got " + std::to_string(actual)); \
    }

#define ASSERT_FLOAT_EQ(expected, actual) \
    if (std::abs((expected) - (actual)) > 0.001f) { \
        throw std::runtime_error("Assertion failed: expected " + std::to_string(expected) + \
                                ", got " + std::to_string(actual)); \
    }

#define ASSERT_GT(value1, value2) \
    if (!((value1) > (value2))) { \
        throw std::runtime_error("Assertion failed: " #value1 " is not greater than " #value2); \
    }

#define ASSERT_LT(value1, value2) \
    if (!((value1) < (value2))) { \
        throw std::runtime_error("Assertion failed: " #value1 " is not less than " #value2); \
    }

#define ASSERT_LE(value1, value2) \
    if (!((value1) <= (value2))) { \
        throw std::runtime_error("Assertion failed: " #value1 " is not less than or equal to " #value2); \
    }

#define ASSERT_GE(value1, value2) \
    if (!((value1) >= (value2))) { \
        throw std::runtime_error("Assertion failed: " #value1 " is not greater than or equal to " #value2); \
    }

#define ASSERT_NO_THROW(expression) \
    try { \
        expression; \
    } catch (...) { \
        throw std::runtime_error("Assertion failed: " #expression " threw an exception"); \
    }

#define ASSERT_THROW(expression, exception_type) \
    try { \
        expression; \
        throw std::runtime_error("Assertion failed: " #expression " did not throw " #exception_type); \
    } catch (const exception_type&) { \
        /* Expected exception */ \
    } catch (...) { \
        throw std::runtime_error("Assertion failed: " #expression " threw different exception than " #exception_type); \
    }

// Test registration macro
#define TEST(suite_name, test_name) \
    void test_##suite_name##_##test_name(); \
    static int test_##suite_name##_##test_name##_registered = \
        (TestFramework::getInstance().addTest(#suite_name, #test_name, test_##suite_name##_##test_name), 0); \
    void test_##suite_name##_##test_name()

// Test fixture base class
class TestFixture {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
    
public:
    void run() {
        SetUp();
        try {
            runTest();
        } catch (...) {
            TearDown();
            throw;
        }
        TearDown();
    }
    
protected:
    virtual void runTest() = 0;
};

#define TEST_F(fixture_name, test_name) \
    class fixture_name##_##test_name##_Test : public fixture_name { \
    protected: \
        void runTest() override; \
    }; \
    static int fixture_name##_##test_name##_registered = \
        (TestFramework::getInstance().addTest(#fixture_name, #test_name, \
            []() { fixture_name##_##test_name##_Test().run(); }), 0); \
    void fixture_name##_##test_name##_Test::runTest() 