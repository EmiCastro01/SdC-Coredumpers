// signal_gen.c
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEV_OUT "/dev/coredumpers"
#define PERIOD_US 1000000 // 1 segundo en microsegundos
#define STEPS 100         // Número de pasos por periodo

int main() {
  int fd = open(DEV_OUT, O_WRONLY);
  if (fd < 0) {
    perror("open /dev/coredumpers");
    return 1;
  }
  // Generar señal triangular: sube de 0 a MAX y baja
  const int MAX = 1023;
  const int half = STEPS / 2;
  while (1) {
    // Subida
    for (int i = 0; i <= half; i++) {
      int v = (MAX * i) / half;
      int v2 = MAX - v;
      char buf[32];
      int n = snprintf(buf, sizeof(buf), "%d,%d", v, v2);
      if (n < 0) {
        fprintf(stderr, "snprintf error: %s", strerror(errno));
        break;
      }
      if (write(fd, buf, n) < 0) {
        perror("write to device");
        break;
      }
      usleep(PERIOD_US / STEPS);
    }
    // Bajada
    for (int i = half; i >= 0; i--) {
      int v = (MAX * i) / half;
      int v2 = MAX - v;
      char buf[32];
      int n = snprintf(buf, sizeof(buf), "%d,%d", v, v2);
      if (n < 0) {
        fprintf(stderr, "snprintf error: %s", strerror(errno));
        break;
      }
      if (write(fd, buf, n) < 0) {
        perror("write to device");
        break;
      }
      usleep(PERIOD_US / STEPS);
    }
  }
  close(fd);
  return 0;
}
