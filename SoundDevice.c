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
  fprintf(stderr, "OpenAL error: %d\n", error);
}

void
SoundDevice_create(SoundDevice_t soundDevice) {
#if DEBUG
  fprintf(stderr, "constructing sound device\n");
#endif

  // create soundDevice
  soundDevice = (SoundDevice_t)malloc(sizeof(struct SoundDevice));
  if (!soundDevice) {
    snderr("failed to allocate memory");
    return;
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
}

void
Shutdown(void);

void
SoundDevice_destroy(SoundDevice_t soundDevice, int shutdown) {
#if DEBUG
  fprintf(stderr, "destructing sound device\n");
#endif

  if (shutdown) {
    Shutdown();
  }

  free((void *)soundDevice);
  soundDevice = NULL;
}

void
Shutdown(void) {
  ALCcontext *ctx = alcGetCurrentContext();
  ALCdevice *dev = alcGetContextsDevice(ctx);

  // free device context from reference
  if (!alcMakeContextCurrent(NULL)) {
    snderr("failed clear context");
  } else {
#if DEBUG
    fprintf(stderr, "device context cleared\n");
#endif
  }

  alcDestroyContext(ctx);
  alcGetError(dev);
#if DEBUG
  fprintf(stderr, "device context destroyed\n");
#endif

  // close device
  if (!alcCloseDevice(dev)) {
    snderr("failed to close device");
  } else {
#if DEBUG
    fprintf(stderr, "device closed\n");
#endif
  }
}
