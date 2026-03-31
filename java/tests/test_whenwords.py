import pytest
import sys
sys.path.insert(0, 'src')
from whenwords import timeago, duration, parse_duration, human_date, date_range


def test_timeago_just_now_identical_timestamps():
    assert timeago(1704067200, 1704067200) == "just now"

def test_timeago_just_now_30_seconds_ago():
    assert timeago(1704067170, 1704067200) == "just now"

def test_timeago_just_now_44_seconds_ago():
    assert timeago(1704067156, 1704067200) == "just now"

def test_timeago_1_minute_ago_45_seconds():
    assert timeago(1704067155, 1704067200) == "1 minute ago"

def test_timeago_1_minute_ago_89_seconds():
    assert timeago(1704067111, 1704067200) == "1 minute ago"

def test_timeago_2_minutes_ago_90_seconds():
    assert timeago(1704067110, 1704067200) == "2 minutes ago"

def test_timeago_30_minutes_ago():
    assert timeago(1704065400, 1704067200) == "30 minutes ago"

def test_timeago_44_minutes_ago():
    assert timeago(1704064560, 1704067200) == "44 minutes ago"

def test_timeago_1_hour_ago_45_minutes():
    assert timeago(1704064500, 1704067200) == "1 hour ago"

def test_timeago_1_hour_ago_89_minutes():
    assert timeago(1704061860, 1704067200) == "1 hour ago"

def test_timeago_2_hours_ago_90_minutes():
    assert timeago(1704061800, 1704067200) == "2 hours ago"

def test_timeago_5_hours_ago():
    assert timeago(1704049200, 1704067200) == "5 hours ago"

def test_timeago_21_hours_ago():
    assert timeago(1703991600, 1704067200) == "21 hours ago"

def test_timeago_1_day_ago_22_hours():
    assert timeago(1703988000, 1704067200) == "1 day ago"

def test_timeago_1_day_ago_35_hours():
    assert timeago(1703941200, 1704067200) == "1 day ago"

def test_timeago_2_days_ago_36_hours():
    assert timeago(1703937600, 1704067200) == "2 days ago"

def test_timeago_7_days_ago():
    assert timeago(1703462400, 1704067200) == "7 days ago"

def test_timeago_25_days_ago():
    assert timeago(1701907200, 1704067200) == "25 days ago"

def test_timeago_1_month_ago_26_days():
    assert timeago(1701820800, 1704067200) == "1 month ago"

def test_timeago_1_month_ago_45_days():
    assert timeago(1700179200, 1704067200) == "1 month ago"

def test_timeago_2_months_ago_46_days():
    assert timeago(1700092800, 1704067200) == "2 months ago"

def test_timeago_6_months_ago():
    assert timeago(1688169600, 1704067200) == "6 months ago"

def test_timeago_11_months_ago_319_days():
    assert timeago(1676505600, 1704067200) == "11 months ago"

def test_timeago_1_year_ago_320_days():
    assert timeago(1676419200, 1704067200) == "1 year ago"

def test_timeago_1_year_ago_547_days():
    assert timeago(1656806400, 1704067200) == "1 year ago"

def test_timeago_2_years_ago_548_days():
    assert timeago(1656720000, 1704067200) == "2 years ago"

def test_timeago_5_years_ago():
    assert timeago(1546300800, 1704067200) == "5 years ago"

def test_timeago_future_in_just_now_30_seconds():
    assert timeago(1704067230, 1704067200) == "just now"

def test_timeago_future_in_1_minute():
    assert timeago(1704067260, 1704067200) == "in 1 minute"

def test_timeago_future_in_5_minutes():
    assert timeago(1704067500, 1704067200) == "in 5 minutes"

def test_timeago_future_in_1_hour():
    assert timeago(1704070200, 1704067200) == "in 1 hour"

def test_timeago_future_in_3_hours():
    assert timeago(1704078000, 1704067200) == "in 3 hours"

def test_timeago_future_in_1_day():
    assert timeago(1704150000, 1704067200) == "in 1 day"

def test_timeago_future_in_2_days():
    assert timeago(1704240000, 1704067200) == "in 2 days"

def test_timeago_future_in_1_month():
    assert timeago(1706745600, 1704067200) == "in 1 month"

def test_timeago_future_in_1_year():
    assert timeago(1735689600, 1704067200) == "in 1 year"

def test_duration_zero_seconds():
    assert duration(0) == "0 seconds"

def test_duration_1_second():
    assert duration(1) == "1 second"

def test_duration_45_seconds():
    assert duration(45) == "45 seconds"

def test_duration_1_minute():
    assert duration(60) == "1 minute"

def test_duration_1_minute_30_seconds():
    assert duration(90) == "1 minute, 30 seconds"

def test_duration_2_minutes():
    assert duration(120) == "2 minutes"

def test_duration_1_hour():
    assert duration(3600) == "1 hour"

def test_duration_1_hour_1_minute():
    assert duration(3661) == "1 hour, 1 minute"

def test_duration_1_hour_30_minutes():
    assert duration(5400) == "1 hour, 30 minutes"

def test_duration_2_hours_30_minutes():
    assert duration(9000) == "2 hours, 30 minutes"

def test_duration_1_day():
    assert duration(86400) == "1 day"

def test_duration_1_day_2_hours():
    assert duration(93600) == "1 day, 2 hours"

def test_duration_7_days():
    assert duration(604800) == "7 days"

def test_duration_1_month_30_days():
    assert duration(2592000) == "1 month"

def test_duration_1_year_365_days():
    assert duration(31536000) == "1 year"

def test_duration_1_year_2_months():
    assert duration(36720000) == "1 year, 2 months"

def test_duration_compact_1h_1m():
    assert duration(3661, {'compact': True}) == "1h 1m"

def test_duration_compact_2h_30m():
    assert duration(9000, {'compact': True}) == "2h 30m"

def test_duration_compact_1d_2h():
    assert duration(93600, {'compact': True}) == "1d 2h"

def test_duration_compact_45s():
    assert duration(45, {'compact': True}) == "45s"

def test_duration_compact_0s():
    assert duration(0, {'compact': True}) == "0s"

def test_duration_max_units_1_hours_only():
    assert duration(3661, {'max_units': 1}) == "1 hour"

def test_duration_max_units_1_days_only():
    assert duration(93600, {'max_units': 1}) == "1 day"

def test_duration_max_units_3():
    assert duration(93661, {'max_units': 3}) == "1 day, 2 hours, 1 minute"

def test_duration_compact_max_units_1():
    assert duration(9000, {'compact': True, 'max_units': 1}) == "3h"

def test_duration_error_negative_seconds():
    with pytest.raises(ValueError):
        duration(-100)

def test_parse_duration_compact_hours_minutes():
    assert parse_duration("2h30m") == 9000

def test_parse_duration_compact_with_space():
    assert parse_duration("2h 30m") == 9000

def test_parse_duration_compact_with_comma():
    assert parse_duration("2h, 30m") == 9000

def test_parse_duration_verbose():
    assert parse_duration("2 hours 30 minutes") == 9000

def test_parse_duration_verbose_with_and():
    assert parse_duration("2 hours and 30 minutes") == 9000

def test_parse_duration_verbose_with_comma_and():
    assert parse_duration("2 hours, and 30 minutes") == 9000

def test_parse_duration_decimal_hours():
    assert parse_duration("2.5 hours") == 9000

def test_parse_duration_decimal_compact():
    assert parse_duration("1.5h") == 5400

def test_parse_duration_single_unit_minutes_verbose():
    assert parse_duration("90 minutes") == 5400

def test_parse_duration_single_unit_minutes_compact():
    assert parse_duration("90m") == 5400

def test_parse_duration_single_unit_min():
    assert parse_duration("90min") == 5400

def test_parse_duration_colon_notation_h_mm():
    assert parse_duration("2:30") == 9000

def test_parse_duration_colon_notation_h_mm_ss():
    assert parse_duration("1:30:00") == 5400

def test_parse_duration_colon_notation_with_seconds():
    assert parse_duration("0:05:30") == 330

def test_parse_duration_days_verbose():
    assert parse_duration("2 days") == 172800

def test_parse_duration_days_compact():
    assert parse_duration("2d") == 172800

def test_parse_duration_weeks_verbose():
    assert parse_duration("1 week") == 604800

def test_parse_duration_weeks_compact():
    assert parse_duration("1w") == 604800

def test_parse_duration_mixed_verbose():
    assert parse_duration("1 day, 2 hours, and 30 minutes") == 95400

def test_parse_duration_mixed_compact():
    assert parse_duration("1d 2h 30m") == 95400

def test_parse_duration_seconds_only_verbose():
    assert parse_duration("45 seconds") == 45

def test_parse_duration_seconds_compact_s():
    assert parse_duration("45s") == 45

def test_parse_duration_seconds_compact_sec():
    assert parse_duration("45sec") == 45

def test_parse_duration_hours_hr():
    assert parse_duration("2hr") == 7200

def test_parse_duration_hours_hrs():
    assert parse_duration("2hrs") == 7200

def test_parse_duration_minutes_mins():
    assert parse_duration("30mins") == 1800

def test_parse_duration_case_insensitive():
    assert parse_duration("2H 30M") == 9000

def test_parse_duration_whitespace_tolerance():
    assert parse_duration("  2 hours   30 minutes  ") == 9000

def test_parse_duration_error_empty_string():
    with pytest.raises(ValueError):
        parse_duration("")

def test_parse_duration_error_no_units():
    with pytest.raises(ValueError):
        parse_duration("hello world")

def test_parse_duration_error_negative():
    with pytest.raises(ValueError):
        parse_duration("-5 hours")

def test_parse_duration_error_just_number():
    with pytest.raises(ValueError):
        parse_duration("42")

def test_human_date_today():
    assert human_date(1705276800, 1705276800) == "Today"

def test_human_date_today_same_day_different_time():
    assert human_date(1705320000, 1705276800) == "Today"

def test_human_date_yesterday():
    assert human_date(1705190400, 1705276800) == "Yesterday"

def test_human_date_tomorrow():
    assert human_date(1705363200, 1705276800) == "Tomorrow"

def test_human_date_last_sunday_1_day_before_monday():
    assert human_date(1705190400, 1705276800) == "Yesterday"

def test_human_date_last_saturday_2_days_ago():
    assert human_date(1705104000, 1705276800) == "Last Saturday"

def test_human_date_last_friday_3_days_ago():
    assert human_date(1705017600, 1705276800) == "Last Friday"

def test_human_date_last_thursday_4_days_ago():
    assert human_date(1704931200, 1705276800) == "Last Thursday"

def test_human_date_last_wednesday_5_days_ago():
    assert human_date(1704844800, 1705276800) == "Last Wednesday"

def test_human_date_last_tuesday_6_days_ago():
    assert human_date(1704758400, 1705276800) == "Last Tuesday"

def test_human_date_last_monday_7_days_ago_becomes_date():
    assert human_date(1704672000, 1705276800) == "January 8"

def test_human_date_this_tuesday_1_day_future():
    assert human_date(1705363200, 1705276800) == "Tomorrow"

def test_human_date_this_wednesday_2_days_future():
    assert human_date(1705449600, 1705276800) == "This Wednesday"

def test_human_date_this_thursday_3_days_future():
    assert human_date(1705536000, 1705276800) == "This Thursday"

def test_human_date_this_sunday_6_days_future():
    assert human_date(1705795200, 1705276800) == "This Sunday"

def test_human_date_next_monday_7_days_future_becomes_date():
    assert human_date(1705881600, 1705276800) == "January 22"

def test_human_date_same_year_different_month():
    assert human_date(1709251200, 1705276800) == "March 1"

def test_human_date_same_year_end_of_year():
    assert human_date(1735603200, 1705276800) == "December 31"

def test_human_date_previous_year():
    assert human_date(1672531200, 1705276800) == "January 1, 2023"

def test_human_date_next_year():
    assert human_date(1736121600, 1705276800) == "January 6, 2025"

def test_date_range_same_day():
    assert date_range(1705276800, 1705276800) == "January 15, 2024"

def test_date_range_same_day_different_times():
    assert date_range(1705276800, 1705320000) == "January 15, 2024"

def test_date_range_consecutive_days_same_month():
    assert date_range(1705276800, 1705363200) == "January 15–16, 2024"

def test_date_range_same_month_range():
    assert date_range(1705276800, 1705881600) == "January 15–22, 2024"

def test_date_range_same_year_different_months():
    assert date_range(1705276800, 1707955200) == "January 15 – February 15, 2024"

def test_date_range_different_years():
    assert date_range(1703721600, 1705276800) == "December 28, 2023 – January 15, 2024"

def test_date_range_full_year_span():
    assert date_range(1704067200, 1735603200) == "January 1 – December 31, 2024"

def test_date_range_swapped_inputs_should_auto_correct():
    assert date_range(1705881600, 1705276800) == "January 15–22, 2024"

def test_date_range_multi_year_span():
    assert date_range(1672531200, 1735689600) == "January 1, 2023 – January 1, 2025"

