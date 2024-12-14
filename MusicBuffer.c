#include <AL/alext.h>
#include <stdlib.h>

#include "MusicBuffer.h"

extern void
snderr(const char *errmsg);

MusicBuffer
MusicBuffer_create(const char *filename) {
  MusicBuffer musicBuffer = (MusicBuffer)malloc(sizeof(struct MusicBuffer_t));
  if (!musicBuffer) {
    snderr("failed to create music buffer");
    return NULL;
  }

  alGenSources(1, &musicBuffer->source);
  alGenBuffers(BUFFER_NUM, musicBuffer->buffers);

  musicBuffer->p_sndFile = sf_open(filename, SFM_READ, &musicBuffer->p_sfInfo);
  if (!musicBuffer->p_sndFile) {
    snderr("failed to open provided music file");
    free((void *)musicBuffer);
    return NULL;
  }

  // determine format
  switch (musicBuffer->p_sfInfo.channels) {
  case 1:
    musicBuffer->format = AL_FORMAT_MONO16;
    break;
  case 2:
    musicBuffer->format = AL_FORMAT_STEREO16;
    break;
  case 3:
    if (sf_command(musicBuffer->p_sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) ==
        SF_AMBISONIC_B_FORMAT) {
      musicBuffer->format = AL_FORMAT_BFORMAT2D_16;
    }
    break;
  case 4:
    if (sf_command(musicBuffer->p_sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) ==
        SF_AMBISONIC_B_FORMAT) {
      musicBuffer->format = AL_FORMAT_BFORMAT3D_16;
    }
    break;
  default:
    sf_close(musicBuffer->p_sndFile);
    musicBuffer->p_sndFile = NULL;

    snderr("unsupported channel count from file");
    free((void *)musicBuffer);

    return NULL;
  }

  // calculate buffer size
  size_t frameSize = ((size_t)BUFFER_SAMPLE * (size_t)musicBuffer->p_sfInfo.channels) * sizeof(short);
  musicBuffer->p_memBuf = (short *)(malloc(frameSize));

  return musicBuffer;
}

void
MusicBuffer_destroy(MusicBuffer musicBuffer) {
  alDeleteSources(1, &musicBuffer->source);
  if (musicBuffer->p_sndFile) {
    sf_close(musicBuffer->p_sndFile);
  }
  musicBuffer->p_sndFile = NULL;
  free((void *)musicBuffer->p_memBuf);
  alDeleteBuffers(BUFFER_NUM, musicBuffer->buffers);

  free((void *)musicBuffer);
  musicBuffer = NULL;
}
