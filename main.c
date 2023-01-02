#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_KARTS 4
#define MAX_LAPS 10
#define NUM_CIRCUITS 3

const char* circuit_names[NUM_CIRCUITS] = { "Magnicourt", "Silverstone", "Monaco" };

struct Kart {
  int position;
  char name[32];
  int laps_completed;
  double lap_times[MAX_LAPS];
  double total_time;
};

void init_karts(struct Kart* karts) {
  for (int i = 0; i < NUM_KARTS; i++) {
    sprintf(karts[i].name, "Kart %d", i + 1);
    karts[i].laps_completed = 0;
    karts[i].total_time = 0.0;
  }
}

void simulate_lap(struct Kart* kart, const char* circuit) {
  double lap_time = (double)rand() / RAND_MAX * 20.0 + 10.0;
  kart->lap_times[kart->laps_completed] = lap_time;
  kart->total_time += lap_time;
  kart->laps_completed++;
  printf("%s completed lap %d on circuit %s in %.2lf seconds\n", kart->name, kart->laps_completed, circuit, lap_time);
}

void sort_karts(struct Kart* karts) {
  for (int i = 0; i < NUM_KARTS; i++) {
    for (int j = i + 1; j < NUM_KARTS; j++) {
      if (karts[i].total_time > karts[j].total_time) {
        struct Kart temp = karts[i];
        karts[i] = karts[j];
        karts[j] = temp;
      }
    }
  }
}

int main() {
  srand(time(NULL));

  struct Kart karts[NUM_KARTS];
  init_karts(karts);

  for (int i = 0; i < NUM_CIRCUITS; i++) {
    const char* circuit = circuit_names[i];
    int laps = rand() % MAX_LAPS + 1;
    printf("Racing on circuit %s with %d laps\n", circuit, laps);
    for (int j = 0; j < laps; j++) {
      for (int k = 0; k < NUM_KARTS; k++) {
        simulate_lap(&karts[k], circuit);
      }
      sort_karts(karts);
    }
    printf("\n");
  }

  printf("Final results:\n");
  for (int i = 0; i < NUM_KARTS; i++) {
    printf("%d. %s: %d laps, %.2lf seconds\n", 1, karts[i].name, karts[i].laps_completed, karts[i].total_time);
}

return 0;
}
