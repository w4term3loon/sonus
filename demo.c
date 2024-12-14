#include "SoundDevice.h"
#include <time.h>

int main(void) {
  SoundDevice soundDevice = SoundDevice_create();
  SoundDevice_destroy(soundDevice);
}
