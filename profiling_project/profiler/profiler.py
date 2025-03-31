import serial
import time

arduino = serial.Serial("/dev/ttyACM0", 9600, timeout=1)  # Ajusta el puerto
while True:
    elapsed_times = []
    for _ in range(5):
        line = arduino.readline().decode().strip()
        if line == "START":
            start_time = time.perf_counter()
        elif line == "END":
            if "start_time" in locals():
                end_time = time.perf_counter()
                elapsed = end_time - start_time
                elapsed_times.append(elapsed)
                print(f"Tiempo sampled: {elapsed:.6f} seconds")
            else:
                print("Error: 'START' no fue recibido antes de 'END'")

    if len(elapsed_times) == 5:
        average_elapsed = sum(elapsed_times) / len(elapsed_times)
        with open("elapsed_times.txt", "w") as file:
            file.write("Medición\tTiempo Transcurrido (s)\n")
            for idx, elapsed in enumerate(elapsed_times, 1):
                file.write(f"{idx}\t{elapsed:.6f}\n")
            file.write(f"\nPromedio\t{average_elapsed:.6f}\n")
        break
