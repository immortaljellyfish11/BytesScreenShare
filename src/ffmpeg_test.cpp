// ffmpeg_test.cpp
extern "C" {
#include <libavformat/avformat.h>
}

#include <QDebug>

void testFFmpeg()
{
    unsigned version = avformat_version();
    qDebug() << "FFmpeg avformat version:" << version;
}
