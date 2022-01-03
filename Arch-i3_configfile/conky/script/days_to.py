#! /bin/python3
from datetime import datetime
import sys
import re

# 对参数进行基础检查，保证只有一个参数且该参数为一个8位的数字
if len(sys.argv) != 2:
    print("Error: invalid argument count.")
    print("Usage: days_to YYMMDD.")
    exit()

if not re.match("[0-9]{8}", sys.argv[1]):
    print("Error: invalid date format.")
    print("Usage: days_to YYMMDD.")
    exit()

# 从参数中获取年月日，并判断日期是否合法
year  = int(sys.argv[1][0:4])
month = int(sys.argv[1][4:6])
day   = int(sys.argv[1][6:])

if (month > 12 or day > 31):
    print("Error: invalid date value.")
    exit()

is_leap_year = (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)
if (month == 2) and (day > 29 or ((not is_leap_year) and day > 28)):
    print("Error: invalid date value.")
    exit()

is_small_month = [4,6,9,11].count(month)
if is_small_month and day > 30:
    print("Error: invalid date value.")
    exit()

# 生成日期与当前日期，并输出天数差值
target = datetime.strptime(sys.argv[1], "%Y%m%d")
now = datetime.now()

diff = target - now;
print(diff.days + 1, end='')

