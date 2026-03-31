# whenwords for Python

Human-friendly time formatting and parsing.

## Installation

Copy the `src/` directory into your project and import:

```python
from src.whenwords import timeago, duration, parse_duration, human_date, date_range
```

## Quick start

```python
from whenwords import timeago, duration, parse_duration, human_date, date_range

# Relative time
print(timeago(1704067110, 1704067200))  # "2 minutes ago"

# Format duration
print(duration(3661))  # "1 hour, 1 minute"
print(duration(9000, {'compact': True, 'max_units': 1}))  # "3h"

# Parse duration string
print(parse_duration("2h 30m"))  # 9000.0

# Human-readable date
print(human_date(1705190400, 1705276800))  # "Yesterday"

# Date range
print(date_range(1705276800, 1705881600))  # "January 15–22, 2024"
```

## Functions

### timeago(timestamp, reference?) → str

Returns a human-readable relative time string.

**Parameters:**
- `timestamp`: Unix timestamp (seconds), ISO 8601 string, or datetime
- `reference`: Optional reference timestamp (defaults to timestamp)

**Returns:** Relative time string like "2 minutes ago" or "in 3 hours"

```python
timeago(1704067110, 1704067200)  # "2 minutes ago"
timeago(1704070200, 1704067200)  # "in 1 hour"
```

### duration(seconds, options?) → str

Formats a duration (not relative to now).

**Parameters:**
- `seconds`: Non-negative number of seconds
- `options`: Optional dict with `compact` (bool) and `max_units` (int)

**Returns:** Formatted duration string

```python
duration(3661)  # "1 hour, 1 minute"
duration(3661, {'compact': True})  # "1h 1m"
duration(9000, {'max_units': 1})  # "3h"
```

### parse_duration(string) → float

Parses a human-written duration string into seconds.

**Parameters:**
- `string`: Duration string like "2h 30m" or "2 hours 30 minutes"

**Returns:** Number of seconds

```python
parse_duration("2h30m")  # 9000.0
parse_duration("2:30")  # 9000.0
parse_duration("2 hours and 30 minutes")  # 9000.0
```

### human_date(timestamp, reference?) → str

Returns a contextual date string.

**Parameters:**
- `timestamp`: Unix timestamp, ISO 8601 string, or datetime
- `reference`: Reference timestamp for comparison

**Returns:** Contextual date like "Today", "Yesterday", "Last Friday", or "January 15"

```python
human_date(1705190400, 1705276800)  # "Yesterday"
human_date(1705104000, 1705276800)  # "Last Saturday"
human_date(1709251200, 1705276800)  # "March 1"
```

### date_range(start, end) → str

Formats a date range with smart abbreviation.

**Parameters:**
- `start`: Start timestamp
- `end`: End timestamp

**Returns:** Formatted date range

```python
date_range(1705276800, 1705363200)  # "January 15–16, 2024"
date_range(1705276800, 1707955200)  # "January 15 – February 15, 2024"
```

## Error handling

All functions raise `ValueError` for invalid inputs:

```python
try:
    parse_duration("")
except ValueError as e:
    print(e)  # "Empty string"

try:
    duration(-100)
except ValueError as e:
    print(e)  # "seconds must be non-negative and finite"
```

## Accepted types

All timestamp parameters accept:
- Unix timestamps (int or float, in seconds)
- ISO 8601 strings (`"2024-01-01T00:00:00Z"`)
- Python `datetime` objects
