#ifndef SOUND_DEVICE_INCLUDE_GUARD
#define SOUND_DEVICE_INCLUDE_GUARD

#include <AL/alc.h>

struct SoundDevice {
  ALCdevice *p_ALCdevice;
  ALCcontext *p_ALCcontext;
};

typedef struct SoundDevice *SoundDevice_t;
void SoundDevice_create(SoundDevice_t);
void SoundDevice_destroy(SoundDevice_t, int);

#endif // SOUND_DEVICE_INCLUDE_GUARD
