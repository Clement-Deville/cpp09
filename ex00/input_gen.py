#!/usr/bin/python3
import random
from datetime import datetime, timedelta

start_date = datetime(2010, 8, 20)
end_date = datetime(2025, 12, 31)

current = start_date

print("date | value")

while current <= end_date:
    qty = random.randint(1, 1000)
    print(f"{current.strftime('%Y-%m-%d')} | {qty}")
    current += timedelta(days=random.randint(1,80))
