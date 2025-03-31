import serial
import time

arduino = serial.Serial("/dev/ttyACM0", 9600, timeout=1)  # Ajusta el puerto
while True:
    line = arduino.readline().decode().strip()
    if line == "START":
        start_time = time.perf_counter()
    elif line == "END":
        end_time = time.perf_counter()
        elapsed = end_time - start_time
        print(f"Tiempo sampled: {elapsed:.6f} seconds")

        import time
