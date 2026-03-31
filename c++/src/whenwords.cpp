#include "whenwords.h"
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <cmath>
#include <iomanip>
#include <ctime>

namespace whenwords {

// Helper: Normalize timestamp to int64_t
int64_t normalize_timestamp(const std::string& timestamp) {
    // Try to parse as integer
    try {
        size_t pos;
        int64_t value = std::stoll(timestamp, &pos);
        if (pos == timestamp.size()) {
            return value;
        }
    } catch (...) {}
    
    // Try to parse as double
    try {
        size_t pos;
        double value = std::stod(timestamp, &pos);
        if (pos == timestamp.size()) {
            return static_cast<int64_t>(value);
        }
    } catch (...) {}
    
    // Try to parse as ISO 8601
    // This is a simplified parser - real implementation would be more robust
    std::regex iso8601_regex(R"(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(\.\d+)?(Z|[+-]\d{2}:\d{2})?)");
    if (std::regex_match(timestamp, iso8601_regex)) {
        // For simplicity, we'll just throw an error for ISO 8601 for now
        // In a real implementation, we'd parse this properly
        throw ParseError("ISO 8601 parsing not implemented");
    }
    
    throw ParseError("Invalid timestamp format");
}

int64_t normalize_timestamp(int64_t timestamp) {
    return timestamp;
}

int64_t normalize_timestamp(double timestamp) {
    return static_cast<int64_t>(timestamp);
}

// Helper: Format time ago string
std::string format_timeago(int64_t diff) {
    bool future = diff < 0;
    diff = std::abs(diff);
    
    if (diff < 45) {
        return "just now";
    } else if (diff < 90) {
        return future ? "in 1 minute" : "1 minute ago";
    } else if (diff < 45 * 60) {
        int minutes = static_cast<int>(std::round(diff / 60.0));
        return future ? "in " + std::to_string(minutes) + " minutes" : 
               std::to_string(minutes) + " minutes ago";
    } else if (diff < 90 * 60) {
        return future ? "in 1 hour" : "1 hour ago";
    } else if (diff < 22 * 3600) {
        int hours = static_cast<int>(std::round(diff / 3600.0));
        return future ? "in " + std::to_string(hours) + " hours" : 
               std::to_string(hours) + " hours ago";
    } else if (diff < 36 * 3600) {
        return future ? "in 1 day" : "1 day ago";
    } else if (diff < 26 * 86400) {
        int days = static_cast<int>(std::round(diff / 86400.0));
        return future ? "in " + std::to_string(days) + " days" : 
               std::to_string(days) + " days ago";
    } else if (diff < 46 * 86400) {
        return future ? "in 1 month" : "1 month ago";
    } else if (diff < 320 * 86400) {
        int months = static_cast<int>(std::round(diff / (30.0 * 86400)));
        return future ? "in " + std::to_string(months) + " months" : 
               std::to_string(months) + " months ago";
    } else if (diff < 548 * 86400) {
        return future ? "in 1 year" : "1 year ago";
    } else {
        int years = static_cast<int>(std::round(diff / (365.0 * 86400)));
        return future ? "in " + std::to_string(years) + " years" : 
               std::to_string(years) + " years ago";
    }
}

// timeago implementations
std::string timeago(const std::string& timestamp, const std::string& reference) {
    int64_t ts = normalize_timestamp(timestamp);
    int64_t ref = reference.empty() ? ts : normalize_timestamp(reference);
    int64_t diff = ref - ts;
    return format_timeago(diff);
}

std::string timeago(int64_t timestamp, int64_t reference) {
    int64_t ref = (reference == -1) ? timestamp : reference;
    int64_t diff = ref - timestamp;
    return format_timeago(diff);
}

std::string timeago(double timestamp, double reference) {
    int64_t ts = normalize_timestamp(timestamp);
    int64_t ref = (reference == -1) ? ts : normalize_timestamp(reference);
    int64_t diff = ref - ts;
    return format_timeago(diff);
}

// duration implementation
std::string duration(double seconds, const DurationOptions& options) {
    if (seconds < 0) {
        throw ParseError("Duration cannot be negative");
    }
    if (std::isnan(seconds) || std::isinf(seconds)) {
        throw ParseError("Invalid duration value");
    }
    
    struct Unit {
        const char* name;
        const char* compact;
        double seconds;
    } units[] = {
        {"year", "y", 365 * 86400},
        {"month", "m", 30 * 86400},
        {"day", "d", 86400},
        {"hour", "h", 3600},
        {"minute", "m", 60},
        {"second", "s", 1}
    };
    
    std::vector<std::pair<double, const Unit*>> parts;
    double remaining = seconds;
    
    for (auto& unit : units) {
        if (remaining >= unit.seconds || unit.seconds == 1) {
            double value = remaining / unit.seconds;
            parts.emplace_back(value, &unit);
            remaining = std::fmod(remaining, unit.seconds);
        }
    }
    
    // Apply max_units
    if (parts.size() > static_cast<size_t>(options.max_units)) {
        parts.resize(options.max_units);
        // Round the last part
        if (!parts.empty()) {
            parts.back().first = std::round(parts.back().first);
        }
    }
    
    // Build the result
    std::stringstream ss;
    bool first = true;
    
    for (auto& [value, unit] : parts) {
        int count = static_cast<int>(value);
        if (count == 0) continue;
        
        if (!first) {
            if (options.compact) {
                ss << " ";
            } else {
                ss << ", ";
            }
        }
        
        ss << count;
        if (options.compact) {
            ss << unit->compact;
        } else {
            ss << " " << unit->name;
            if (count != 1) ss << "s";
        }
        
        first = false;
    }
    
    if (ss.str().empty()) {
        return options.compact ? "0s" : "0 seconds";
    }
    
    return ss.str();
}

// parse_duration implementation
int64_t parse_duration(const std::string& input) {
    if (input.empty()) {
        throw ParseError("Empty duration string");
    }
    
    // Check for negative
    if (!input.empty() && input[0] == '-') {
        throw ParseError("Negative duration not allowed");
    }
    
    // Check for colon notation
    if (input.find(':') != std::string::npos) {
        std::vector<std::string> parts;
        std::stringstream ss(input);
        std::string part;
        while (std::getline(ss, part, ':')) {
            parts.push_back(part);
        }
        
        if (parts.size() == 2) {
            // h:mm
            int hours = std::stoi(parts[0]);
            int minutes = std::stoi(parts[1]);
            return hours * 3600 + minutes * 60;
        } else if (parts.size() == 3) {
            // h:mm:ss
            int hours = std::stoi(parts[0]);
            int minutes = std::stoi(parts[1]);
            int seconds = std::stoi(parts[2]);
            return hours * 3600 + minutes * 60 + seconds;
        }
    }
    
    // Regex pattern for duration parts (with optional whitespace)
    std::regex pattern(R"((\d+(?:\.\d+)?)\s*([a-zA-Z]+))");
    std::smatch matches;
    std::string::const_iterator search_start(input.cbegin());
    
    int64_t total = 0;
    bool found = false;
    
    while (std::regex_search(search_start, input.cend(), matches, pattern)) {
        found = true;
        double value = std::stod(matches[1]);
        std::string unit = matches[2];
        
        // Normalize unit to lowercase
        std::transform(unit.begin(), unit.end(), unit.begin(), ::tolower);
        
        // Debug output
        // std::cerr << "Match: " << matches[1] << " " << unit << std::endl;
        
        if (unit == "s" || unit == "sec" || unit == "secs" || unit == "second" || unit == "seconds") {
            total += static_cast<int64_t>(value);
        } else if (unit == "m" || unit == "min" || unit == "mins" || unit == "minute" || unit == "minutes") {
            total += static_cast<int64_t>(value * 60);
        } else if (unit == "h" || unit == "hr" || unit == "hrs" || unit == "hour" || unit == "hours") {
            total += static_cast<int64_t>(value * 3600);
        } else if (unit == "d" || unit == "day" || unit == "days") {
            total += static_cast<int64_t>(value * 86400);
        } else if (unit == "w" || unit == "wk" || unit == "wks" || unit == "week" || unit == "weeks") {
            total += static_cast<int64_t>(value * 604800);
        }
        
        search_start = matches.suffix().first;
    }
    
    if (!found) {
        throw ParseError("No parseable duration units found");
    }
    
    return total;
}

// Helper: Convert timestamp to tm struct in UTC
std::tm timestamp_to_tm(int64_t timestamp) {
    std::tm tm = {};
    std::time_t t = static_cast<std::time_t>(timestamp);
    gmtime_r(&t, &tm);
    return tm;
}

// Helper: Format date
std::string format_date(const std::tm& tm, bool include_year = true) {
    const char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    
    std::stringstream ss;
    ss << months[tm.tm_mon] << " " << (tm.tm_mday);
    if (include_year) {
        ss << ", " << (tm.tm_year + 1900);
    }
    return ss.str();
}

// Helper: Get weekday name
std::string get_weekday_name(int weekday) {
    const char* weekdays[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    return weekdays[weekday];
}

// human_date implementation
std::string human_date(const std::string& timestamp, const std::string& reference) {
    int64_t ts = normalize_timestamp(timestamp);
    int64_t ref = reference.empty() ? ts : normalize_timestamp(reference);
    return human_date(ts, ref);
}

std::string human_date(int64_t timestamp, int64_t reference) {
    int64_t ref = (reference == -1) ? timestamp : reference;
    
    std::tm ts_tm = timestamp_to_tm(timestamp);
    std::tm ref_tm = timestamp_to_tm(ref);
    
    // Check if same day
    if (ts_tm.tm_year == ref_tm.tm_year && 
        ts_tm.tm_mon == ref_tm.tm_mon && 
        ts_tm.tm_mday == ref_tm.tm_mday) {
        return "Today";
    }
    
    // Check if yesterday
    std::tm yesterday = ref_tm;
    yesterday.tm_mday--;
    mktime(&yesterday); // Normalize
    if (ts_tm.tm_year == yesterday.tm_year && 
        ts_tm.tm_mon == yesterday.tm_mon && 
        ts_tm.tm_mday == yesterday.tm_mday) {
        return "Yesterday";
    }
    
    // Check if tomorrow
    std::tm tomorrow = ref_tm;
    tomorrow.tm_mday++;
    mktime(&tomorrow); // Normalize
    if (ts_tm.tm_year == tomorrow.tm_year && 
        ts_tm.tm_mon == tomorrow.tm_mon && 
        ts_tm.tm_mday == tomorrow.tm_mday) {
        return "Tomorrow";
    }
    
    // Check if within past 7 days
    int64_t diff_days = (ref - timestamp) / 86400;
    if (diff_days > 0 && diff_days < 7) {
        return "Last " + get_weekday_name(ts_tm.tm_wday);
    }
    
    // Check if within next 7 days
    diff_days = (timestamp - ref) / 86400;
    if (diff_days > 0 && diff_days < 7) {
        return "This " + get_weekday_name(ts_tm.tm_wday);
    }
    
    // Check if same year
    if (ts_tm.tm_year == ref_tm.tm_year) {
        return format_date(ts_tm, false);
    }
    
    // Different year
    return format_date(ts_tm, true);
}

std::string human_date(double timestamp, double reference) {
    int64_t ts = normalize_timestamp(timestamp);
    int64_t ref = (reference == -1) ? ts : normalize_timestamp(reference);
    return human_date(ts, ref);
}

// date_range implementation
std::string date_range(const std::string& start, const std::string& end) {
    int64_t s = normalize_timestamp(start);
    int64_t e = normalize_timestamp(end);
    return date_range(s, e);
}

std::string date_range(int64_t start, int64_t end) {
    // Swap if start > end
    if (start > end) {
        std::swap(start, end);
    }
    
    std::tm start_tm = timestamp_to_tm(start);
    std::tm end_tm = timestamp_to_tm(end);
    
    // Same day
    if (start_tm.tm_year == end_tm.tm_year && 
        start_tm.tm_mon == end_tm.tm_mon && 
        start_tm.tm_mday == end_tm.tm_mday) {
        return format_date(start_tm, true);
    }
    
    // Same month
    if (start_tm.tm_year == end_tm.tm_year && 
        start_tm.tm_mon == end_tm.tm_mon) {
        const char* months[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };
        std::stringstream ss;
        ss << months[start_tm.tm_mon] << " " << start_tm.tm_mday << "–" << end_tm.tm_mday;
        ss << ", " << (start_tm.tm_year + 1900);
        return ss.str();
    }
    
    // Same year
    if (start_tm.tm_year == end_tm.tm_year) {
        const char* months[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };
        std::stringstream ss;
        ss << months[start_tm.tm_mon] << " " << start_tm.tm_mday << " – ";
        ss << months[end_tm.tm_mon] << " " << end_tm.tm_mday;
        ss << ", " << (start_tm.tm_year + 1900);
        return ss.str();
    }
    
    // Different years
    return format_date(start_tm, true) + " – " + format_date(end_tm, true);
}

std::string date_range(double start, double end) {
    int64_t s = normalize_timestamp(start);
    int64_t e = normalize_timestamp(end);
    return date_range(s, e);
}

} // namespace whenwords
