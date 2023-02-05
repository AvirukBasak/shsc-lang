#ifndef LEX_BUFFER_CH
#define LEX_BUFFER_CH

void lex_buffpush(char ch)
{
    if (!lex_buffer) lex_buffer = calloc(1, sizeof(LexBuffer));
    if (!lex_buffer) lex_throw("memory allocation failed");
    if (lex_buffer->push_i >= lex_buffer->size) {
        lex_buffer->buffer = realloc(lex_buffer->buffer, lex_buffer->size + LEX_MAX_BUFFALLOC_SZ);
        if (!lex_buffer->buffer) lex_throw("memory allocation failed");
        lex_buffer->size += LEX_MAX_BUFFALLOC_SZ;
        lex_buffer->buffer[lex_buffer->size -1] = 0;
    }
    lex_buffer->buffer[lex_buffer->push_i++] = ch;
    lex_buffer->buffer[lex_buffer->push_i] = 0;
}

char lex_buffpop()
{
    if (!lex_buffer) abort();
    char tmp = 0;
    if (lex_buffer->push_i > 0) {
        tmp = lex_buffer->buffer[lex_buffer->push_i -1];
        lex_buffer->buffer[--lex_buffer->push_i] = 0;
    }
    return tmp;
}

void lex_buffreset()
{
    if (!lex_buffer) return;
    lex_buffer->buffer[lex_buffer->push_i = 0] = 0;
}

char *lex_get_buffstr()
{
    if (!lex_buffer->push_i) return "NULL";
    return lex_buffer->buffer;
}

#endif
