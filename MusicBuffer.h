#ifndef MUSIC_BUFFER_HEADER_GUARD
#define MUSIC_BUFFER_HEADER_GUARD

#include <AL/alc.h>
#include <sndfile.h>

#define BUFFER_SAMPLE 8192
#define BUFFER_NUM 4

struct MusicBuffer_t {
  ALCuint source;
  ALCuint buffers[BUFFER_NUM];
  ALCenum format;
  SNDFILE *p_sndFile;
  SF_INFO p_sfInfo;
  short *p_memBuf;
};

typedef struct MusicBuffer_t *MusicBuffer;
MusicBuffer MusicBuffer_create(const char*);
void MusicBuffer_destroy(MusicBuffer);
void MusicBuffer_play(MusicBuffer);

#endif // MUSIC_BUFFER_HEADER_GUARD
