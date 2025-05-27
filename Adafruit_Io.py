import serial
import requests

# Adafruit IO credentials
ADAFRUIT_IO_KEY = "YOUR_ADAFRUIT_IO_KEY"  # Replace with your Adafruit IO key
ADAFRUIT_IO_USERNAME = "YOUR_ADAFRUIT_IO_USERNAME"  # Replace with your Adafruit IO username
# Define the feed key on Adafruit IO
FEED_KEY = "YOUR_FEED_KEY"  # Replace with your feed key

# Initialize serial connection to Arduino
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Replace '/dev/ttyACM0' with your Arduino's port

# URL for sending data to Adafruit IO
AIO_URL = f'https://io.adafruit.com/api/v2/{ADAFRUIT_IO_USERNAME}/feeds/{FEED_KEY}/data'

while True:
    # Read data from Arduino
    data = ser.readline().decode().strip()
    print("Received data from Arduino:", data)
    
    # Send data to Adafruit IO
    headers = {
        'Content-Type': 'application/json',
        'X-AIO-Key': ADAFRUIT_IO_KEY
    }
    payload = {'value': data}
    response = requests.post(AIO_URL, json=payload, headers=headers)
    if response.status_code == 201:
        print("Data sent to Adafruit IO successfully")
    else:
        print("Failed to send data to Adafruit IO. Status code:", response.status_code)
