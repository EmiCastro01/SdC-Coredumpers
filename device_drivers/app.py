import time
import sys
import matplotlib.pyplot as plt


def read_from_driver(dev, signal):
    # Lee solo una línea y parsea dos valores
    with open(dev, "r") as f:
        line = f.readline()
    parts = line.strip().split(",")
    if len(parts) != 2:
        return None
    try:
        s1, s2 = map(int, parts)
    except ValueError:
        return None
    return s1 if signal == 1 else s2


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: plot_signal.py <signal(1|2)> <dev=/dev/coredumpers>")
        sys.exit(1)
    sig = int(sys.argv[1])
    dev = sys.argv[2]
    xs, ys = [], []
    plt.ion()
    fig, ax = plt.subplots()
    while True:
        val = read_from_driver(dev, sig)
        if val is None:
            time.sleep(0.1)
            continue
        xs.append(time.time())
        ys.append(val)
        ax.clear()
        ax.plot(xs, ys)
        ax.set_xlabel("Time (s)")
        ax.set_ylabel("Value")
        ax.set_title(f"Signal {sig}")
        plt.pause(0.1)
