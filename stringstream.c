#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "stdlib.h"

//
// Created by Maximilian Schüller on 23.12.2022.
//

#include "stringstream.h"

void stream_terminate(StringStream *s) {
    if(s->str && s->maxLoad) {
        s->str[s->size] = '\0';
    }
}

StringStream stream_mkStringStream() {
    return stream_mkStringStreamSize(STREAM_SIZE);
}
StringStream stream_mkStringStreamSize(int size) {
    StringStream stream;
    stream.size = 0;
    stream.maxLoad = 0;

    int maxLoad = 1;
    while (maxLoad < size) {
        maxLoad *= 2;
    }

    stream.str = calloc(maxLoad, sizeof(char));
    if(stream.str) {
        stream.maxLoad = maxLoad;
        stream_terminate(&stream);
    }

    return stream;
}
StringStream stream_mkStringStreamFromString(char *str) {
    int size = strlen(str);

    StringStream stream = stream_mkStringStreamSize(size);
    if(stream.maxLoad) {
        memcpy(stream.str, str, size * sizeof(char));
        stream.size = size;
    }

    return stream;
}

char stream_increase(StringStream *stream, int inc) {
    int newSize = stream->size + inc + 1;

    if(newSize > stream->maxLoad) {
        int maxLoad = stream->maxLoad;
        if(!maxLoad) {
            maxLoad = 1;
        }
        while (maxLoad <= newSize) {
            maxLoad *= 2;
        }

        char *newString = realloc(stream->str, maxLoad * sizeof(char));
        if(!newString) {
            newString = calloc(maxLoad, sizeof(char));
            memcpy(newString, stream->str, maxLoad * sizeof(char));

            free(stream->str);
            stream->str = newString;
        } else if(newString != stream->str) {
            //free(stream->str);
            stream->str = newString;
        }
        stream->maxLoad = maxLoad;
        return !0;
    }
    return 0;
}

int stream_available(StringStream *stream) {
    return stream->maxLoad - stream->size - 1;
}

void stream_fprintf(StringStream *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int available = stream_available(stream);
    int formatSize = vsnprintf(stream->str + stream->size, available * sizeof(char), format, args);
    va_end(args);

    if(stream_increase(stream, formatSize)) {
        available = stream_available(stream);
        va_start(args, format);
        formatSize = vsnprintf(stream->str + stream->size, available * sizeof(char), format, args);
        va_end(args);
    }

    stream->size += formatSize;
    stream_terminate(stream);
}
void stream_read(StringStream *stream, void *data, int length) {
    stream_increase(stream, length);

    memcpy(stream->str + stream->size, data, length);

    stream->size += length;
    stream_terminate(stream);
}
void stream_cursorBackwarts(StringStream *stream, int length) {
    if(!stream->size || !stream->maxLoad) {
        printf("\nOMG\n%d <-> %d\n", stream->size, stream->maxLoad);
        return;
    }

    stream->size = length >= stream->size ? 0 : stream->size - length;
    stream_terminate(stream);
}

void stream_readFile(StringStream *stream, FILE *file, int length) {
    if(length == 0) {
        int currPos = ftell(file);
        fseek(file, 0L, SEEK_END);
        length = ftell(file) - currPos;
        fseek(file, currPos, SEEK_SET);
        printf("Read File to end, length %d\n", length);
    } else {
        printf("Read File with length %d\n", length);
    }

    stream_increase(stream, length);
    fread(stream->str + stream->size, sizeof(char), length, file);
    printf("Finish?");
    stream->size += length;
    stream_terminate(stream);
}
void stream_writeFile(StringStream *stream, FILE *file, int first, int last) {
    if(first >= stream->size) {
        return;
    }

    if(!last) {
        last = stream->size;
    }

    if(last >= first) {
        if(last > stream->size) {
            last = stream->size;
        }

        fwrite(stream->str + first, sizeof(char), last - first, file);
    }
}

void stream_clear(StringStream *stream) {
    free(stream->str);
    stream->size = 0;
    stream->maxLoad = 0;
    //stream_terminate(stream);
}

void stream_print(StringStream *stream) {
    printf("%s", stream->str);
}

void stream_printFull(StringStream *stream) {
    printf("#String Stream\n\tSize: %d; Capacity: %d\n\t\"%s\"\n#String Stream\n", stream->size, stream->maxLoad, stream->str);
}

void fusch(StringStream *s) {
    for (int i = 0; i < s->size; ++i) {
        if(s->str[i] == '\0') {
            s->str[i] = '0';
        }
    }
    s->str[s->size] = '\0';
}