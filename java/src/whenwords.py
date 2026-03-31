from datetime import datetime
from typing import Union, Optional, Dict, Any
import math


def _to_timestamp(ts: Union[int, float, str]) -> float:
    if isinstance(ts, str):
        try:
            dt = datetime.fromisoformat(ts.replace('Z', '+00:00'))
            return dt.timestamp()
        except ValueError:
            raise ValueError(f"Invalid timestamp format: {ts}")
    return float(ts)


def _pluralize(n: int, singular: str, plural: Optional[str] = None) -> str:
    if plural is None:
        plural = singular + 's'
    return singular if n == 1 else plural


def timeago(timestamp: Union[int, float, str], reference: Optional[Union[int, float, str]] = None) -> str:
    ts = _to_timestamp(timestamp)
    ref = _to_timestamp(reference) if reference is not None else ts
    
    diff = ref - ts
    is_future = diff < 0
    diff = abs(diff)
    
    if diff < 45:
        return "just now"
    
    def format_result(value: int, unit: str) -> str:
        unit_str = _pluralize(value, unit)
        if is_future:
            return f"in {value} {unit_str}"
        return f"{value} {unit_str} ago"
    
    if diff < 90:
        return format_result(1, "minute")
    
    if diff < 45 * 60:
        minutes = round(diff / 60)
        return format_result(minutes, "minute")
    
    if diff < 90 * 60:
        return format_result(1, "hour")
    
    if diff < 22 * 3600:
        hours = round(diff / 3600)
        return format_result(hours, "hour")
    
    if diff < 36 * 3600:
        return format_result(1, "day")
    
    if diff < 26 * 86400:
        days = round(diff / 86400)
        return format_result(days, "day")
    
    if diff < 46 * 86400:
        return format_result(1, "month")
    
    if diff < 320 * 86400:
        months = round(diff / (30 * 86400))
        return format_result(months, "month")
    
    if diff < 548 * 86400:
        return format_result(1, "year")
    
    years = round(diff / (365 * 86400))
    return format_result(years, "year")


def duration(seconds: Union[int, float], options: Optional[Dict[str, Any]] = None) -> str:
    if seconds < 0 or math.isnan(seconds) or math.isinf(seconds):
        raise ValueError("seconds must be non-negative and finite")
    
    opts = options or {}
    compact = opts.get('compact', False)
    max_units = opts.get('max_units', 2)
    
    if seconds == 0:
        return "0s" if compact else "0 seconds"
    
    remaining = seconds
    units = []
    
    year_seconds = 365 * 86400
    month_seconds = 30 * 86400
    day_seconds = 86400
    hour_seconds = 3600
    minute_seconds = 60
    
    unit_defs = [
        ('year', year_seconds),
        ('month', month_seconds),
        ('day', day_seconds),
        ('hour', hour_seconds),
        ('minute', minute_seconds),
        ('second', 1),
    ]
    
    for name, unit_seconds in unit_defs:
        if remaining >= unit_seconds:
            count = int(remaining // unit_seconds)
            units.append((name, count))
            remaining -= count * unit_seconds
    
    if len(units) > max_units and max_units == 1:
        largest_name = units[0][0]
        for name, unit_seconds in unit_defs:
            if name == largest_name:
                total_in_largest = seconds / unit_seconds
                rounded = int(math.floor(total_in_largest + 0.5))
                units = [(largest_name, rounded)]
                break
    elif len(units) > max_units:
        units = units[:max_units]
    
    if compact:
        parts = [f"{count}{name[0]}" for name, count in units]
        return ' '.join(parts)
    else:
        parts = [f"{count} {_pluralize(count, name)}" for name, count in units]
        return ', '.join(parts)


def parse_duration(string: str) -> float:
    import re
    
    s = string.strip().lower()
    if not s:
        raise ValueError("Empty string")
    
    if s.startswith('-'):
        raise ValueError("Negative duration")
    
    colon_match = re.match(r'^(\d+):(\d+)(?::(\d+))?$', s)
    if colon_match:
        hours = int(colon_match.group(1))
        minutes = int(colon_match.group(2))
        seconds = int(colon_match.group(3)) if colon_match.group(3) else 0
        return hours * 3600 + minutes * 60 + seconds
    
    unit_map = {
        's': 1, 'sec': 1, 'secs': 1, 'second': 1, 'seconds': 1,
        'm': 60, 'min': 60, 'mins': 60, 'minute': 60, 'minutes': 60,
        'h': 3600, 'hr': 3600, 'hrs': 3600, 'hour': 3600, 'hours': 3600,
        'd': 86400, 'day': 86400, 'days': 86400,
        'w': 604800, 'wk': 604800, 'wks': 604800, 'week': 604800, 'weeks': 604800,
    }
    
    total = 0.0
    
    pattern = r'(\d+(?:\.\d+)?)\s*([a-zA-Z]+)'
    matches = re.findall(pattern, s)
    
    if not matches:
        raise ValueError(f"No parseable units in: {string}")
    
    for value_str, unit in matches:
        value = float(value_str)
        if value < 0:
            raise ValueError("Negative duration")
        unit_lower = unit.lower()
        if unit_lower not in unit_map:
            raise ValueError(f"Unknown unit: {unit}")
        total += value * unit_map[unit_lower]
    
    return total


def human_date(timestamp: Union[int, float, str], reference: Optional[Union[int, float, str]] = None) -> str:
    from datetime import timezone
    
    ts = _to_timestamp(timestamp)
    ref = _to_timestamp(reference) if reference is not None else ts
    
    ts_dt = datetime.fromtimestamp(ts, tz=timezone.utc)
    ref_dt = datetime.fromtimestamp(ref, tz=timezone.utc)
    
    ts_date = ts_dt.date()
    ref_date = ref_dt.date()
    
    diff_days = (ts_date - ref_date).days
    
    if diff_days == 0:
        return "Today"
    elif diff_days == -1:
        return "Yesterday"
    elif diff_days == 1:
        return "Tomorrow"
    elif -6 <= diff_days <= -2:
        weekdays = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
        return f"Last {weekdays[ts_date.weekday()]}"
    elif 2 <= diff_days <= 6:
        weekdays = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
        return f"This {weekdays[ts_date.weekday()]}"
    else:
        months = ["January", "February", "March", "April", "May", "June",
                  "July", "August", "September", "October", "November", "December"]
        month_name = months[ts_date.month - 1]
        if ts_date.year == ref_date.year:
            return f"{month_name} {ts_date.day}"
        else:
            return f"{month_name} {ts_date.day}, {ts_date.year}"


def date_range(start: Union[int, float, str], end: Union[int, float, str]) -> str:
    from datetime import timezone
    
    start_ts = _to_timestamp(start)
    end_ts = _to_timestamp(end)
    
    if start_ts > end_ts:
        start_ts, end_ts = end_ts, start_ts
    
    start_dt = datetime.fromtimestamp(start_ts, tz=timezone.utc)
    end_dt = datetime.fromtimestamp(end_ts, tz=timezone.utc)
    
    start_date = start_dt.date()
    end_date = end_dt.date()
    
    months = ["January", "February", "March", "April", "May", "June",
              "July", "August", "September", "October", "November", "December"]
    
    start_month = months[start_date.month - 1]
    end_month = months[end_date.month - 1]
    
    if start_date == end_date:
        return f"{start_month} {start_date.day}, {start_date.year}"
    elif start_date.year == end_date.year and start_date.month == end_date.month:
        return f"{start_month} {start_date.day}–{end_date.day}, {start_date.year}"
    elif start_date.year == end_date.year:
        return f"{start_month} {start_date.day} – {end_month} {end_date.day}, {start_date.year}"
    else:
        return f"{start_month} {start_date.day}, {start_date.year} – {end_month} {end_date.day}, {end_date.year}"
