#include "test_framework.h"
#include <SFML/Graphics.hpp>

// Global test setup
class TestEnvironment {
public:
    static void SetUp() {
        // Initialize SFML context for tests if needed
        // This is needed for SFML objects to work in tests
    }
    
    static void TearDown() {
        // Cleanup if needed
    }
};

int main(int argc, char **argv) {
    // Setup test environment
    TestEnvironment::SetUp();
    
    // Run all tests
    int failed_tests = TestFramework::getInstance().runAllTests();
    
    // Cleanup
    TestEnvironment::TearDown();
    
    // Return number of failed tests as exit code
    return failed_tests;
} 