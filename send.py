import serial
import time

# Setup COM8 with correct baud rate (should match Arduino)
ser = serial.Serial('COM8', 9600)
time.sleep(2)  # Wait for Arduino to reset

try:
    while True:
        # Example data — replace with real sensor/data source if needed
        cpu_usage = "45%"     # You can dynamically fetch with psutil if needed
        gpu_usage = "30%"
        fps_value = "60fps"

        # Create the formatted string
        data = f"CPU:{cpu_usage}GPU:{gpu_usage}FPS:{fps_value}\n"

        # Send to Arduino
        ser.write(data.encode('utf-8'))
        print("Sent:", data.strip())

        time.sleep(2)  # Send every 2 seconds

except KeyboardInterrupt:
    print("Stopped by user")

finally:
    ser.close()
