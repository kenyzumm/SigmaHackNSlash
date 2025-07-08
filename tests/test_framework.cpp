#include "test_framework.h"
#include <algorithm>

// Implementation of TestFramework methods
namespace {
    // Helper function to find test suite
    auto findTestSuite(std::vector<TestFramework::TestSuite>& suites, const std::string& name) {
        return std::find_if(suites.begin(), suites.end(), 
            [&name](const TestFramework::TestSuite& suite) { return suite.name == name; });
    }
}

// The framework is mostly header-only, but we can add any additional implementation here if needed 