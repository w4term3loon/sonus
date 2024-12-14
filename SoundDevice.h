#ifndef SOUND_DEVICE_INCLUDE_GUARD
#define SOUND_DEVICE_INCLUDE_GUARD

#include <AL/alc.h>

struct SoundDevice_t {
  ALCdevice *p_ALCdevice;
  ALCcontext *p_ALCcontext;
};

typedef struct SoundDevice_t *SoundDevice;
SoundDevice SoundDevice_create(void);
void SoundDevice_destroy(SoundDevice);

#endif // SOUND_DEVICE_INCLUDE_GUARD
