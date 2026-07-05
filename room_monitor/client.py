import csv
import re
import time
from datetime import datetime

import requests

URL = "http://192.168.1.2/"

# Create CSV with header (only once)
with open("room_data.csv", "a", newline="") as f:
    writer = csv.writer(f)
    if f.tell() == 0:
        writer.writerow(["Time", "Temperature", "Humidity"])

while True:
    try:
        r = requests.get(URL, timeout=5)

        if r.status_code == 200:
            html = r.text

            temp = float(re.search(r"Temperature\s*:\s*([\d.]+)", html).group(1))
            humidity = float(re.search(r"Humidity\s*:\s*([\d.]+)", html).group(1))
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

            print(timestamp, temp, humidity)

            with open("room_data.csv", "a", newline="") as f:
                writer = csv.writer(f)
                writer.writerow([timestamp, temp, humidity])

        else:
            print("HTTP Error:", r.status_code)

    except Exception as e:
        print(e)

    time.sleep(5)
