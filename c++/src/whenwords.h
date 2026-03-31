#ifndef WHENWORDS_H
#define WHENWORDS_H

#include <string>
#include <chrono>
#include <stdexcept>

namespace whenwords {

// Exception class for parsing errors
class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string& message) : std::runtime_error(message) {}
};

// Duration options structure
struct DurationOptions {
    bool compact = false;
    int max_units = 2;
};

// Convert timestamp to Unix seconds (int64_t)
int64_t normalize_timestamp(const std::string& timestamp);
int64_t normalize_timestamp(int64_t timestamp);
int64_t normalize_timestamp(double timestamp);

// Main functions
std::string timeago(const std::string& timestamp, const std::string& reference = "");
std::string timeago(int64_t timestamp, int64_t reference = -1);
std::string timeago(double timestamp, double reference = -1);

std::string duration(double seconds, const DurationOptions& options = DurationOptions());

int64_t parse_duration(const std::string& input);

std::string human_date(const std::string& timestamp, const std::string& reference = "");
std::string human_date(int64_t timestamp, int64_t reference = -1);
std::string human_date(double timestamp, double reference = -1);

std::string date_range(const std::string& start, const std::string& end);
std::string date_range(int64_t start, int64_t end);
std::string date_range(double start, double end);

} // namespace whenwords

#endif // WHENWORDS_H
