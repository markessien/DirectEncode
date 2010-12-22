# Compile file for the erdmpg dll

CC=g++
CFLAGS=-c -DBUILD_DLL -DNDEBUG -mno-cygwin -I../ffmpeg/libavutil -I../ffmpeg -I../ffmpeg/libavcodec -I../ffmpeg/libavformat -I../ffmpeg/libswscale
LDFLAGS=-L../ffmpeg/libavutil -L../ffmpeg/libavcodec -L../ffmpeg/libavformat -L../faac/libfaac/.libs -L../lame-398/libmp3lame/.libs -L../ffmpeg/libswscale
SOURCES=Buffer.cpp Encode.cpp EncodeParameters.cpp erdmpglib.cpp License.cpp Licenseauth.cpp LogoOverlay.cpp MemoryProtocol.cpp Multiplex.cpp stdafx.cpp SyncWait.cpp Timestamps.cpp Profiles.cpp AudioResample.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=erdmpg-6.dll


all: erdmpg

erdmpg: $(OBJECTS)
	$(CC) $(LDFLAGS) -shared -o erdmpg-6.dll $(OBJECTS)  -lgcc -lkernel32 -luser32 -lgdi32 -lmsacm32 -lwinmm -lavformaterd -lavcodecerd -lavutilerd -lfaac -lmp3lame -Wl,--out-implib,erdmpg-6.a

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf *.dll
	rm -rf *.a


