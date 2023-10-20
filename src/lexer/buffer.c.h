#ifndef LEXER_BUFFER_C_H
#define LEXER_BUFFER_C_H

#include <stdlib.h>

#include "errcodes.h"
#include "lexer.h"
#include "globals.h"
#include "io.h"

void lex_Buffer_push(char ch)
{
    if (!lex_buffer) lex_buffer = shsc_calloc(1, sizeof(lex_Buffer_t));
    if (!lex_buffer) io_errndie("lex_Buffer_push:" ERR_MSG_MALLOCFAIL);
    if (lex_buffer->push_i >= lex_buffer->size) {
        lex_buffer->buffer = shsc_realloc(lex_buffer->buffer, lex_buffer->size + LEX_MAX_BUFFALLOC_SZ +1);
        if (!lex_buffer->buffer) io_errndie("lex_Buffer_push:" ERR_MSG_REALLOCFAIL);
        lex_buffer->size += LEX_MAX_BUFFALLOC_SZ;
        lex_buffer->buffer[lex_buffer->size -1] = 0;
    }
    lex_buffer->buffer[lex_buffer->push_i++] = ch;
    lex_buffer->buffer[lex_buffer->push_i] = 0;
}

char lex_Buffer_pop()
{
    if (!lex_buffer) abort();
    char tmp = 0;
    if (lex_buffer->push_i > 0) {
        tmp = lex_buffer->buffer[lex_buffer->push_i -1];
        lex_buffer->buffer[--lex_buffer->push_i] = 0;
    }
    return tmp;
}

void lex_Buffer_reset()
{
    if (!lex_buffer) return;
    lex_buffer->buffer[lex_buffer->push_i = 0] = 0;
}

const char *lex_Buffer_getstr()
{
    if (!lex_buffer || !lex_buffer->push_i) return NULL;
    return lex_buffer->buffer;
}

void lex_Buffer_free()
{
    if (!lex_buffer) return;
    shsc_free(lex_buffer->buffer);
    lex_buffer->buffer = NULL;
    shsc_free(lex_buffer);
    lex_buffer = NULL;
}

#else
    #warning re-inclusion of module 'lexer/buffer.c.h'
#endif
