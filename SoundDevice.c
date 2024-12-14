#include "SoundDevice.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

void
snderr(const char *errmsg) {
  fprintf(stderr, "sound error: %s\n", errmsg);
}

void
cleanAlcErrorOnDevice(ALCdevice *device) {
  ALCenum error = alcGetError(device);
  if (error != ALC_NO_ERROR) {
    fprintf(stderr, "OpenAL error: %d\n", error);
  }
}

SoundDevice
SoundDevice_create(void) {
#if DEBUG
  fprintf(stderr, "constructing sound device\n");
#endif

  // create soundDevice
  SoundDevice soundDevice = (SoundDevice)malloc(sizeof(struct SoundDevice_t));
  if (!soundDevice) {
    snderr("failed to allocate memory");
    return NULL;
  }

  // fetch the default output device
  const ALCchar *defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
  (void)defname;

  // open default device
  soundDevice->p_ALCdevice = alcOpenDevice(defname);
  if (!soundDevice->p_ALCdevice) {
    snderr("failed to open default device");
  }

  // create context
  soundDevice->p_ALCcontext = alcCreateContext(soundDevice->p_ALCdevice, NULL);
  if (!soundDevice->p_ALCcontext) {
    snderr("failed to create device context");
  }

  // actualise context
  if (!alcMakeContextCurrent(soundDevice->p_ALCcontext)) {
    snderr("failed to actualise context");
  }

  // try open all extensions
  const ALCchar *name = NULL;
  if (alcIsExtensionPresent(soundDevice->p_ALCdevice, "ALC_ENUMERATE_ALL_EXT")) {
    name = alcGetString(soundDevice->p_ALCdevice, ALC_ALL_DEVICES_SPECIFIER);
  }

  // if failed to open
  if (name == NULL || alcGetError(soundDevice->p_ALCdevice) != ALC_NO_ERROR) {
    name = alcGetString(soundDevice->p_ALCdevice, ALC_DEVICE_SPECIFIER);
  }

  fprintf(stdout, "Opened \"%s\"\n", name);
  return soundDevice;
}

void
Shutdown(void);

void
SoundDevice_destroy(SoundDevice soundDevice) {
#if DEBUG
  fprintf(stderr, "destructing sound device\n");
#endif

  // free device context from reference
  if (!alcMakeContextCurrent(NULL)) {
    snderr("failed clear context");
  } else {
#if DEBUG
    fprintf(stderr, "device context cleared\n");
#endif
  }

  // destroy device context
  alcDestroyContext(soundDevice->p_ALCcontext);
  cleanAlcErrorOnDevice(soundDevice->p_ALCdevice);
#if DEBUG
  fprintf(stderr, "device context destroyed\n");
#endif

  // close device
  if (!alcCloseDevice(soundDevice->p_ALCdevice)) {
    snderr("failed to close device");
  } else {
#if DEBUG
    fprintf(stderr, "device closed\n");
#endif
  }

  free((void *)soundDevice);
  soundDevice = NULL;
}

