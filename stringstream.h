#include "stdio.h"
//
// Created by Maximilian Schüller on 23.12.2022.
//

#ifndef C_STUDENT_MANAGEMENT_STRINGSTREAM_H
#define C_STUDENT_MANAGEMENT_STRINGSTREAM_H

#define STREAM_SIZE 4

typedef struct stream {
    char *str;
    int maxLoad;
    int size;
} StringStream;

StringStream stream_mkStringStream();
StringStream stream_mkStringStreamSize(int size);
StringStream stream_mkStringStreamFromString(char *str);

char stream_increase(StringStream *stream, int inc);
int stream_available(StringStream *stream);
void stream_fprintf(StringStream *stream, const char *format, ...);
void stream_read(StringStream *stream, void *data, int length);
void stream_cursorBackwarts(StringStream *stream, int length);

void stream_readFile(StringStream *stream, FILE *file, int length);
void stream_writeFile(StringStream *stream, FILE *file, int first, int last);

void stream_clear(StringStream *stream);
void stream_print(StringStream *stream);
void stream_printFull(StringStream *stream);

char *stream_substr(StringStream *s, unsigned int i, int n);


#endif //C_STUDENT_MANAGEMENT_STRINGSTREAM_H
