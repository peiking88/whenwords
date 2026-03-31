#include "whenwords.h"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "Running whenwords tests..." << std::endl;
    int passed = 0;
    int total = 0;

    auto run_test = [&](const std::string& name, auto test_func) {
        total++;
        try {
            test_func();
            passed++;
            std::cout << "✓ " << name << std::endl;
        } catch (const whenwords::ParseError& e) {
            std::cout << "✗ " << name << " - ParseError: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✗ " << name << " - Exception: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "✗ " << name << " - Unknown error" << std::endl;
        }
    };

    // Test timeago
    std::cout << "\n=== Testing timeago ===" << std::endl;
    run_test("just now - identical timestamps", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067200), static_cast<int64_t>(1704067200));
        if (result != "just now") {
            std::cerr << "Expected: " << "just now" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("just now - 30 seconds ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067170), static_cast<int64_t>(1704067200));
        if (result != "just now") {
            std::cerr << "Expected: " << "just now" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("just now - 44 seconds ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067156), static_cast<int64_t>(1704067200));
        if (result != "just now") {
            std::cerr << "Expected: " << "just now" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 minute ago - 45 seconds", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067155), static_cast<int64_t>(1704067200));
        if (result != "1 minute ago") {
            std::cerr << "Expected: " << "1 minute ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 minute ago - 89 seconds", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067111), static_cast<int64_t>(1704067200));
        if (result != "1 minute ago") {
            std::cerr << "Expected: " << "1 minute ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("2 minutes ago - 90 seconds", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067110), static_cast<int64_t>(1704067200));
        if (result != "2 minutes ago") {
            std::cerr << "Expected: " << "2 minutes ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("30 minutes ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704065400), static_cast<int64_t>(1704067200));
        if (result != "30 minutes ago") {
            std::cerr << "Expected: " << "30 minutes ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("44 minutes ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704064560), static_cast<int64_t>(1704067200));
        if (result != "44 minutes ago") {
            std::cerr << "Expected: " << "44 minutes ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 hour ago - 45 minutes", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704064500), static_cast<int64_t>(1704067200));
        if (result != "1 hour ago") {
            std::cerr << "Expected: " << "1 hour ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 hour ago - 89 minutes", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704061860), static_cast<int64_t>(1704067200));
        if (result != "1 hour ago") {
            std::cerr << "Expected: " << "1 hour ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("2 hours ago - 90 minutes", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704061800), static_cast<int64_t>(1704067200));
        if (result != "2 hours ago") {
            std::cerr << "Expected: " << "2 hours ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("5 hours ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704049200), static_cast<int64_t>(1704067200));
        if (result != "5 hours ago") {
            std::cerr << "Expected: " << "5 hours ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("21 hours ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1703991600), static_cast<int64_t>(1704067200));
        if (result != "21 hours ago") {
            std::cerr << "Expected: " << "21 hours ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 day ago - 22 hours", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1703988000), static_cast<int64_t>(1704067200));
        if (result != "1 day ago") {
            std::cerr << "Expected: " << "1 day ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 day ago - 35 hours", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1703941200), static_cast<int64_t>(1704067200));
        if (result != "1 day ago") {
            std::cerr << "Expected: " << "1 day ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("2 days ago - 36 hours", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1703937600), static_cast<int64_t>(1704067200));
        if (result != "2 days ago") {
            std::cerr << "Expected: " << "2 days ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("7 days ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1703462400), static_cast<int64_t>(1704067200));
        if (result != "7 days ago") {
            std::cerr << "Expected: " << "7 days ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("25 days ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1701907200), static_cast<int64_t>(1704067200));
        if (result != "25 days ago") {
            std::cerr << "Expected: " << "25 days ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 month ago - 26 days", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1701820800), static_cast<int64_t>(1704067200));
        if (result != "1 month ago") {
            std::cerr << "Expected: " << "1 month ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 month ago - 45 days", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1700179200), static_cast<int64_t>(1704067200));
        if (result != "1 month ago") {
            std::cerr << "Expected: " << "1 month ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("2 months ago - 46 days", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1700092800), static_cast<int64_t>(1704067200));
        if (result != "2 months ago") {
            std::cerr << "Expected: " << "2 months ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("6 months ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1688169600), static_cast<int64_t>(1704067200));
        if (result != "6 months ago") {
            std::cerr << "Expected: " << "6 months ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("11 months ago - 319 days", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1676505600), static_cast<int64_t>(1704067200));
        if (result != "11 months ago") {
            std::cerr << "Expected: " << "11 months ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 year ago - 320 days", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1676419200), static_cast<int64_t>(1704067200));
        if (result != "1 year ago") {
            std::cerr << "Expected: " << "1 year ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 year ago - 547 days", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1656806400), static_cast<int64_t>(1704067200));
        if (result != "1 year ago") {
            std::cerr << "Expected: " << "1 year ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("2 years ago - 548 days", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1656720000), static_cast<int64_t>(1704067200));
        if (result != "2 years ago") {
            std::cerr << "Expected: " << "2 years ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("5 years ago", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1546300800), static_cast<int64_t>(1704067200));
        if (result != "5 years ago") {
            std::cerr << "Expected: " << "5 years ago" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in just now (30 seconds)", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067230), static_cast<int64_t>(1704067200));
        if (result != "just now") {
            std::cerr << "Expected: " << "just now" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in 1 minute", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067260), static_cast<int64_t>(1704067200));
        if (result != "in 1 minute") {
            std::cerr << "Expected: " << "in 1 minute" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in 5 minutes", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704067500), static_cast<int64_t>(1704067200));
        if (result != "in 5 minutes") {
            std::cerr << "Expected: " << "in 5 minutes" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in 1 hour", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704070200), static_cast<int64_t>(1704067200));
        if (result != "in 1 hour") {
            std::cerr << "Expected: " << "in 1 hour" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in 3 hours", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704078000), static_cast<int64_t>(1704067200));
        if (result != "in 3 hours") {
            std::cerr << "Expected: " << "in 3 hours" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in 1 day", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704150000), static_cast<int64_t>(1704067200));
        if (result != "in 1 day") {
            std::cerr << "Expected: " << "in 1 day" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in 2 days", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1704240000), static_cast<int64_t>(1704067200));
        if (result != "in 2 days") {
            std::cerr << "Expected: " << "in 2 days" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in 1 month", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1706745600), static_cast<int64_t>(1704067200));
        if (result != "in 1 month") {
            std::cerr << "Expected: " << "in 1 month" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("future - in 1 year", []() {
        auto result = whenwords::timeago(static_cast<int64_t>(1735689600), static_cast<int64_t>(1704067200));
        if (result != "in 1 year") {
            std::cerr << "Expected: " << "in 1 year" << ", Got: " << result << std::endl;
            assert(false);
        }
    });

    // Test duration
    std::cout << "\n=== Testing duration ===" << std::endl;
    run_test("zero seconds", []() {
        auto result = whenwords::duration(0);
        if (result != "0 seconds") {
            std::cerr << "Expected: " << "0 seconds" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 second", []() {
        auto result = whenwords::duration(1);
        if (result != "1 second") {
            std::cerr << "Expected: " << "1 second" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("45 seconds", []() {
        auto result = whenwords::duration(45);
        if (result != "45 seconds") {
            std::cerr << "Expected: " << "45 seconds" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 minute", []() {
        auto result = whenwords::duration(60);
        if (result != "1 minute") {
            std::cerr << "Expected: " << "1 minute" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 minute 30 seconds", []() {
        auto result = whenwords::duration(90);
        if (result != "1 minute, 30 seconds") {
            std::cerr << "Expected: " << "1 minute, 30 seconds" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("2 minutes", []() {
        auto result = whenwords::duration(120);
        if (result != "2 minutes") {
            std::cerr << "Expected: " << "2 minutes" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 hour", []() {
        auto result = whenwords::duration(3600);
        if (result != "1 hour") {
            std::cerr << "Expected: " << "1 hour" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 hour 1 minute", []() {
        auto result = whenwords::duration(3661);
        if (result != "1 hour, 1 minute") {
            std::cerr << "Expected: " << "1 hour, 1 minute" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 hour 30 minutes", []() {
        auto result = whenwords::duration(5400);
        if (result != "1 hour, 30 minutes") {
            std::cerr << "Expected: " << "1 hour, 30 minutes" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("2 hours 30 minutes", []() {
        auto result = whenwords::duration(9000);
        if (result != "2 hours, 30 minutes") {
            std::cerr << "Expected: " << "2 hours, 30 minutes" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 day", []() {
        auto result = whenwords::duration(86400);
        if (result != "1 day") {
            std::cerr << "Expected: " << "1 day" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 day 2 hours", []() {
        auto result = whenwords::duration(93600);
        if (result != "1 day, 2 hours") {
            std::cerr << "Expected: " << "1 day, 2 hours" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("7 days", []() {
        auto result = whenwords::duration(604800);
        if (result != "7 days") {
            std::cerr << "Expected: " << "7 days" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 month (30 days)", []() {
        auto result = whenwords::duration(2592000);
        if (result != "1 month") {
            std::cerr << "Expected: " << "1 month" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 year (365 days)", []() {
        auto result = whenwords::duration(31536000);
        if (result != "1 year") {
            std::cerr << "Expected: " << "1 year" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("1 year 2 months", []() {
        auto result = whenwords::duration(36720000);
        if (result != "1 year, 2 months") {
            std::cerr << "Expected: " << "1 year, 2 months" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("compact - 1h 1m", []() {
        whenwords::DurationOptions opts;
        opts.compact = true;
        opts.max_units = 2;
        auto result = whenwords::duration(3661, opts);
        if (result != "1h 1m") {
            std::cerr << "Expected: " << "1h 1m" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("compact - 2h 30m", []() {
        whenwords::DurationOptions opts;
        opts.compact = true;
        opts.max_units = 2;
        auto result = whenwords::duration(9000, opts);
        if (result != "2h 30m") {
            std::cerr << "Expected: " << "2h 30m" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("compact - 1d 2h", []() {
        whenwords::DurationOptions opts;
        opts.compact = true;
        opts.max_units = 2;
        auto result = whenwords::duration(93600, opts);
        if (result != "1d 2h") {
            std::cerr << "Expected: " << "1d 2h" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("compact - 45s", []() {
        whenwords::DurationOptions opts;
        opts.compact = true;
        opts.max_units = 2;
        auto result = whenwords::duration(45, opts);
        if (result != "45s") {
            std::cerr << "Expected: " << "45s" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("compact - 0s", []() {
        whenwords::DurationOptions opts;
        opts.compact = true;
        opts.max_units = 2;
        auto result = whenwords::duration(0, opts);
        if (result != "0s") {
            std::cerr << "Expected: " << "0s" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("max_units 1 - hours only", []() {
        whenwords::DurationOptions opts;
        opts.compact = false;
        opts.max_units = 1;
        auto result = whenwords::duration(3661, opts);
        if (result != "1 hour") {
            std::cerr << "Expected: " << "1 hour" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("max_units 1 - days only", []() {
        whenwords::DurationOptions opts;
        opts.compact = false;
        opts.max_units = 1;
        auto result = whenwords::duration(93600, opts);
        if (result != "1 day") {
            std::cerr << "Expected: " << "1 day" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("max_units 3", []() {
        whenwords::DurationOptions opts;
        opts.compact = false;
        opts.max_units = 3;
        auto result = whenwords::duration(93661, opts);
        if (result != "1 day, 2 hours, 1 minute") {
            std::cerr << "Expected: " << "1 day, 2 hours, 1 minute" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("compact max_units 1", []() {
        whenwords::DurationOptions opts;
        opts.compact = true;
        opts.max_units = 1;
        auto result = whenwords::duration(9000, opts);
        if (result != "3h") {
            std::cerr << "Expected: " << "3h" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("error - negative seconds", []() {
        try {
            whenwords::duration(-100);
            assert(false && "Expected ParseError");
        } catch (const whenwords::ParseError& e) {
            // Expected error
        }
    });

    // Test parse_duration
    std::cout << "\n=== Testing parse_duration ===" << std::endl;
    run_test("compact hours minutes", []() {
        auto result = whenwords::parse_duration("2h30m");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("compact with space", []() {
        auto result = whenwords::parse_duration("2h 30m");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("compact with comma", []() {
        auto result = whenwords::parse_duration("2h, 30m");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("verbose", []() {
        auto result = whenwords::parse_duration("2 hours 30 minutes");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("verbose with and", []() {
        auto result = whenwords::parse_duration("2 hours and 30 minutes");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("verbose with comma and", []() {
        auto result = whenwords::parse_duration("2 hours, and 30 minutes");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("decimal hours", []() {
        auto result = whenwords::parse_duration("2.5 hours");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("decimal compact", []() {
        auto result = whenwords::parse_duration("1.5h");
        if (result != 5400) {
            std::cerr << "Expected: " << 5400 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("single unit minutes verbose", []() {
        auto result = whenwords::parse_duration("90 minutes");
        if (result != 5400) {
            std::cerr << "Expected: " << 5400 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("single unit minutes compact", []() {
        auto result = whenwords::parse_duration("90m");
        if (result != 5400) {
            std::cerr << "Expected: " << 5400 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("single unit min", []() {
        auto result = whenwords::parse_duration("90min");
        if (result != 5400) {
            std::cerr << "Expected: " << 5400 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("colon notation h:mm", []() {
        auto result = whenwords::parse_duration("2:30");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("colon notation h:mm:ss", []() {
        auto result = whenwords::parse_duration("1:30:00");
        if (result != 5400) {
            std::cerr << "Expected: " << 5400 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("colon notation with seconds", []() {
        auto result = whenwords::parse_duration("0:05:30");
        if (result != 330) {
            std::cerr << "Expected: " << 330 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("days verbose", []() {
        auto result = whenwords::parse_duration("2 days");
        if (result != 172800) {
            std::cerr << "Expected: " << 172800 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("days compact", []() {
        auto result = whenwords::parse_duration("2d");
        if (result != 172800) {
            std::cerr << "Expected: " << 172800 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("weeks verbose", []() {
        auto result = whenwords::parse_duration("1 week");
        if (result != 604800) {
            std::cerr << "Expected: " << 604800 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("weeks compact", []() {
        auto result = whenwords::parse_duration("1w");
        if (result != 604800) {
            std::cerr << "Expected: " << 604800 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("mixed verbose", []() {
        auto result = whenwords::parse_duration("1 day, 2 hours, and 30 minutes");
        if (result != 95400) {
            std::cerr << "Expected: " << 95400 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("mixed compact", []() {
        auto result = whenwords::parse_duration("1d 2h 30m");
        if (result != 95400) {
            std::cerr << "Expected: " << 95400 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("seconds only verbose", []() {
        auto result = whenwords::parse_duration("45 seconds");
        if (result != 45) {
            std::cerr << "Expected: " << 45 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("seconds compact s", []() {
        auto result = whenwords::parse_duration("45s");
        if (result != 45) {
            std::cerr << "Expected: " << 45 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("seconds compact sec", []() {
        auto result = whenwords::parse_duration("45sec");
        if (result != 45) {
            std::cerr << "Expected: " << 45 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("hours hr", []() {
        auto result = whenwords::parse_duration("2hr");
        if (result != 7200) {
            std::cerr << "Expected: " << 7200 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("hours hrs", []() {
        auto result = whenwords::parse_duration("2hrs");
        if (result != 7200) {
            std::cerr << "Expected: " << 7200 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("minutes mins", []() {
        auto result = whenwords::parse_duration("30mins");
        if (result != 1800) {
            std::cerr << "Expected: " << 1800 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("case insensitive", []() {
        auto result = whenwords::parse_duration("2H 30M");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("whitespace tolerance", []() {
        auto result = whenwords::parse_duration("  2 hours   30 minutes  ");
        if (result != 9000) {
            std::cerr << "Expected: " << 9000 << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("error - empty string", []() {
        try {
            whenwords::parse_duration("");
            assert(false && "Expected ParseError");
        } catch (const whenwords::ParseError& e) {
            // Expected error
        }
    });
    run_test("error - no units", []() {
        try {
            whenwords::parse_duration("hello world");
            assert(false && "Expected ParseError");
        } catch (const whenwords::ParseError& e) {
            // Expected error
        }
    });
    run_test("error - negative", []() {
        try {
            whenwords::parse_duration("-5 hours");
            assert(false && "Expected ParseError");
        } catch (const whenwords::ParseError& e) {
            // Expected error
        }
    });
    run_test("error - just number", []() {
        try {
            whenwords::parse_duration("42");
            assert(false && "Expected ParseError");
        } catch (const whenwords::ParseError& e) {
            // Expected error
        }
    });

    // Test human_date
    std::cout << "\n=== Testing human_date ===" << std::endl;
    run_test("today", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705276800), static_cast<int64_t>(1705276800));
        if (result != "Today") {
            std::cerr << "Expected: " << "Today" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("today - same day different time", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705320000), static_cast<int64_t>(1705276800));
        if (result != "Today") {
            std::cerr << "Expected: " << "Today" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("yesterday", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705190400), static_cast<int64_t>(1705276800));
        if (result != "Yesterday") {
            std::cerr << "Expected: " << "Yesterday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("tomorrow", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705363200), static_cast<int64_t>(1705276800));
        if (result != "Tomorrow") {
            std::cerr << "Expected: " << "Tomorrow" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("last Sunday (1 day before Monday)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705190400), static_cast<int64_t>(1705276800));
        if (result != "Yesterday") {
            std::cerr << "Expected: " << "Yesterday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("last Saturday (2 days ago)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705104000), static_cast<int64_t>(1705276800));
        if (result != "Last Saturday") {
            std::cerr << "Expected: " << "Last Saturday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("last Friday (3 days ago)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705017600), static_cast<int64_t>(1705276800));
        if (result != "Last Friday") {
            std::cerr << "Expected: " << "Last Friday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("last Thursday (4 days ago)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1704931200), static_cast<int64_t>(1705276800));
        if (result != "Last Thursday") {
            std::cerr << "Expected: " << "Last Thursday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("last Wednesday (5 days ago)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1704844800), static_cast<int64_t>(1705276800));
        if (result != "Last Wednesday") {
            std::cerr << "Expected: " << "Last Wednesday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("last Tuesday (6 days ago)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1704758400), static_cast<int64_t>(1705276800));
        if (result != "Last Tuesday") {
            std::cerr << "Expected: " << "Last Tuesday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("last Monday (7 days ago) - becomes date", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1704672000), static_cast<int64_t>(1705276800));
        if (result != "January 8") {
            std::cerr << "Expected: " << "January 8" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("this Tuesday (1 day future)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705363200), static_cast<int64_t>(1705276800));
        if (result != "Tomorrow") {
            std::cerr << "Expected: " << "Tomorrow" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("this Wednesday (2 days future)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705449600), static_cast<int64_t>(1705276800));
        if (result != "This Wednesday") {
            std::cerr << "Expected: " << "This Wednesday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("this Thursday (3 days future)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705536000), static_cast<int64_t>(1705276800));
        if (result != "This Thursday") {
            std::cerr << "Expected: " << "This Thursday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("this Sunday (6 days future)", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705795200), static_cast<int64_t>(1705276800));
        if (result != "This Sunday") {
            std::cerr << "Expected: " << "This Sunday" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("next Monday (7 days future) - becomes date", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1705881600), static_cast<int64_t>(1705276800));
        if (result != "January 22") {
            std::cerr << "Expected: " << "January 22" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("same year different month", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1709251200), static_cast<int64_t>(1705276800));
        if (result != "March 1") {
            std::cerr << "Expected: " << "March 1" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("same year end of year", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1735603200), static_cast<int64_t>(1705276800));
        if (result != "December 31") {
            std::cerr << "Expected: " << "December 31" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("previous year", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1672531200), static_cast<int64_t>(1705276800));
        if (result != "January 1, 2023") {
            std::cerr << "Expected: " << "January 1, 2023" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("next year", []() {
        auto result = whenwords::human_date(static_cast<int64_t>(1736121600), static_cast<int64_t>(1705276800));
        if (result != "January 6, 2025") {
            std::cerr << "Expected: " << "January 6, 2025" << ", Got: " << result << std::endl;
            assert(false);
        }
    });

    // Test date_range
    std::cout << "\n=== Testing date_range ===" << std::endl;
    run_test("same day", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1705276800), static_cast<int64_t>(1705276800));
        if (result != "January 15, 2024") {
            std::cerr << "Expected: " << "January 15, 2024" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("same day different times", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1705276800), static_cast<int64_t>(1705320000));
        if (result != "January 15, 2024") {
            std::cerr << "Expected: " << "January 15, 2024" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("consecutive days same month", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1705276800), static_cast<int64_t>(1705363200));
        if (result != "January 15–16, 2024") {
            std::cerr << "Expected: " << "January 15–16, 2024" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("same month range", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1705276800), static_cast<int64_t>(1705881600));
        if (result != "January 15–22, 2024") {
            std::cerr << "Expected: " << "January 15–22, 2024" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("same year different months", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1705276800), static_cast<int64_t>(1707955200));
        if (result != "January 15 – February 15, 2024") {
            std::cerr << "Expected: " << "January 15 – February 15, 2024" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("different years", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1703721600), static_cast<int64_t>(1705276800));
        if (result != "December 28, 2023 – January 15, 2024") {
            std::cerr << "Expected: " << "December 28, 2023 – January 15, 2024" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("full year span", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1704067200), static_cast<int64_t>(1735603200));
        if (result != "January 1 – December 31, 2024") {
            std::cerr << "Expected: " << "January 1 – December 31, 2024" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("swapped inputs - should auto-correct", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1705881600), static_cast<int64_t>(1705276800));
        if (result != "January 15–22, 2024") {
            std::cerr << "Expected: " << "January 15–22, 2024" << ", Got: " << result << std::endl;
            assert(false);
        }
    });
    run_test("multi-year span", []() {
        auto result = whenwords::date_range(static_cast<int64_t>(1672531200), static_cast<int64_t>(1735689600));
        if (result != "January 1, 2023 – January 1, 2025") {
            std::cerr << "Expected: " << "January 1, 2023 – January 1, 2025" << ", Got: " << result << std::endl;
            assert(false);
        }
    });

    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "Passed: " << passed << "/" << total << std::endl;

    if (passed == total) {
        std::cout << "All tests passed! 🎉" << std::endl;
        return 0;
    } else {
        std::cout << "Some tests failed! 💥" << std::endl;
        return 1;
    }
}
