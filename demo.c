#include "SoundDevice.h"
#include <time.h>

int main(void) {
  SoundDevice_t soundDevice = NULL;
  SoundDevice_create(soundDevice);
  SoundDevice_destroy(soundDevice, 1);
}
