#!/usr/bin/env python3
import yaml

# Read the tests.yaml file
with open('../tests.yaml', 'r') as f:
    tests = yaml.safe_load(f)

# Generate C++ test code
test_code = ''
test_code += '#include "whenwords.h"\n'
test_code += '#include <iostream>\n'
test_code += '#include <cassert>\n\n'
test_code += 'int main() {\n'
test_code += '    std::cout << "Running whenwords tests..." << std::endl;\n'
test_code += '    int passed = 0;\n'
test_code += '    int total = 0;\n\n'
test_code += '    auto run_test = [&](const std::string& name, auto test_func) {\n'
test_code += '        total++;\n'
test_code += '        try {\n'
test_code += '            test_func();\n'
test_code += '            passed++;\n'
test_code += '            std::cout << "✓ " << name << std::endl;\n'
test_code += '        } catch (const whenwords::ParseError& e) {\n'
test_code += '            std::cout << "✗ " << name << " - ParseError: " << e.what() << std::endl;\n'
test_code += '        } catch (const std::exception& e) {\n'
test_code += '            std::cout << "✗ " << name << " - Exception: " << e.what() << std::endl;\n'
test_code += '        } catch (...) {\n'
test_code += '            std::cout << "✗ " << name << " - Unknown error" << std::endl;\n'
test_code += '        }\n'
test_code += '    };\n\n'

# Generate timeago tests
test_code += '    // Test timeago\n'
test_code += '    std::cout << "\\n=== Testing timeago ===" << std::endl;\n'
for test in tests.get('timeago', []):
    name = test['name']
    input_data = test['input']
    output = test['output']
    
    test_code += '    run_test("' + name + '", []() {\n'
    test_code += '        auto result = whenwords::timeago(static_cast<int64_t>(' + str(input_data['timestamp']) + '), static_cast<int64_t>(' + str(input_data['reference']) + '));\n'
    test_code += '        if (result != "' + output + '") {\n'
    test_code += '            std::cerr << "Expected: " << "' + output + '" << ", Got: " << result << std::endl;\n'
    test_code += '            assert(false);\n'
    test_code += '        }\n'
    test_code += '    });\n'

# Generate duration tests
test_code += '\n    // Test duration\n'
test_code += '    std::cout << "\\n=== Testing duration ===" << std::endl;\n'
for test in tests.get('duration', []):
    name = test['name']
    input_data = test['input']
    
    if 'error' in test:
        # Error test
        test_code += '    run_test("' + name + '", []() {\n'
        test_code += '        try {\n'
        test_code += '            whenwords::duration(' + str(input_data['seconds']) + ');\n'
        test_code += '            assert(false && "Expected ParseError");\n'
        test_code += '        } catch (const whenwords::ParseError& e) {\n'
        test_code += '            // Expected error\n'
        test_code += '        }\n'
        test_code += '    });\n'
    else:
        # Normal test
        output = test['output']
        options = input_data.get('options', {})
        
        test_code += '    run_test("' + name + '", []() {\n'
        if options:
            compact = options.get('compact', False)
            max_units = options.get('max_units', 2)
            test_code += '        whenwords::DurationOptions opts;\n'
            test_code += '        opts.compact = ' + str(compact).lower() + ';\n'
            test_code += '        opts.max_units = ' + str(max_units) + ';\n'
            test_code += '        auto result = whenwords::duration(' + str(input_data['seconds']) + ', opts);\n'
        else:
            test_code += '        auto result = whenwords::duration(' + str(input_data['seconds']) + ');\n'
        test_code += '        if (result != "' + output + '") {\n'
        test_code += '            std::cerr << "Expected: " << "' + output + '" << ", Got: " << result << std::endl;\n'
        test_code += '            assert(false);\n'
        test_code += '        }\n'
        test_code += '    });\n'

# Generate parse_duration tests
test_code += '\n    // Test parse_duration\n'
test_code += '    std::cout << "\\n=== Testing parse_duration ===" << std::endl;\n'
for test in tests.get('parse_duration', []):
    name = test['name']
    input_data = test['input']
    
    if 'error' in test:
        # Error test
        test_code += '    run_test("' + name + '", []() {\n'
        test_code += '        try {\n'
        test_code += '            whenwords::parse_duration("' + input_data + '");\n'
        test_code += '            assert(false && "Expected ParseError");\n'
        test_code += '        } catch (const whenwords::ParseError& e) {\n'
        test_code += '            // Expected error\n'
        test_code += '        }\n'
        test_code += '    });\n'
    else:
        # Normal test
        output = test['output']
        test_code += '    run_test("' + name + '", []() {\n'
        test_code += '        auto result = whenwords::parse_duration("' + input_data + '");\n'
        test_code += '        if (result != ' + str(output) + ') {\n'
        test_code += '            std::cerr << "Expected: " << ' + str(output) + ' << ", Got: " << result << std::endl;\n'
        test_code += '            assert(false);\n'
        test_code += '        }\n'
        test_code += '    });\n'

# Generate human_date tests
test_code += '\n    // Test human_date\n'
test_code += '    std::cout << "\\n=== Testing human_date ===" << std::endl;\n'
for test in tests.get('human_date', []):
    name = test['name']
    input_data = test['input']
    output = test['output']
    
    test_code += '    run_test("' + name + '", []() {\n'
    test_code += '        auto result = whenwords::human_date(static_cast<int64_t>(' + str(input_data['timestamp']) + '), static_cast<int64_t>(' + str(input_data['reference']) + '));\n'
    test_code += '        if (result != "' + output + '") {\n'
    test_code += '            std::cerr << "Expected: " << "' + output + '" << ", Got: " << result << std::endl;\n'
    test_code += '            assert(false);\n'
    test_code += '        }\n'
    test_code += '    });\n'

# Generate date_range tests
test_code += '\n    // Test date_range\n'
test_code += '    std::cout << "\\n=== Testing date_range ===" << std::endl;\n'
for test in tests.get('date_range', []):
    name = test['name']
    input_data = test['input']
    output = test['output']
    
    test_code += '    run_test("' + name + '", []() {\n'
    test_code += '        auto result = whenwords::date_range(static_cast<int64_t>(' + str(input_data['start']) + '), static_cast<int64_t>(' + str(input_data['end']) + '));\n'
    test_code += '        if (result != "' + output + '") {\n'
    test_code += '            std::cerr << "Expected: " << "' + output + '" << ", Got: " << result << std::endl;\n'
    test_code += '            assert(false);\n'
    test_code += '        }\n'
    test_code += '    });\n'

# Add test summary
test_code += '\n    std::cout << "\\n=== Test Summary ===" << std::endl;\n'
test_code += '    std::cout << "Passed: " << passed << "/" << total << std::endl;\n\n'
test_code += '    if (passed == total) {\n'
test_code += '        std::cout << "All tests passed! 🎉" << std::endl;\n'
test_code += '        return 0;\n'
test_code += '    } else {\n'
test_code += '        std::cout << "Some tests failed! 💥" << std::endl;\n'
test_code += '        return 1;\n'
test_code += '    }\n'
test_code += '}\n'

# Write the test file
with open('src/test_whenwords.cpp', 'w') as f:
    f.write(test_code)

print("Generated test file: c++/src/test_whenwords.cpp")
