#include <stdlib.h>
#include "memory.h"

#include "chunk.h"
#include "value.h"

void init_chunk(Chunk* chunk){
  chunk -> count = 0;
  chunk -> capacity = 0;
  chunk -> lines.capacity = 0;
  chunk -> lines.count = 0;
  chunk -> code = NULL;
  chunk -> lines.lines = NULL;
  init_value_array(&chunk->constants);
}

static void compress_line(CompressedLines buffer, int line){
  int i;
  for (i = 1; i < buffer.capacity; i += 2){
    if (buffer.lines[i] == line){
      buffer.lines[i - 1]+=1;
      break;
    } 

    if (buffer.lines[i] == 0) {
        buffer.lines[i] = line;
        buffer.lines[i - 1] += 1;
        buffer.count += 2;
        break;
    }
  }
}

void write_chunk(Chunk* chunk, uint8_t byte, int line){
  if (chunk->capacity < chunk->count + 1){
    int old_capacity = chunk-> capacity;
    chunk->capacity = GROW_CAPACITY(old_capacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;

  if (chunk->lines.capacity < chunk->lines.count +1){
    int old_capacity = chunk->lines.capacity;
    chunk->lines.capacity = GROW_CAPACITY(old_capacity);
    chunk->lines.lines = GROW_ARRAY(LineValue, chunk->lines.lines, old_capacity, chunk->lines.capacity);
    int i;
    for (i = 0; i < chunk->lines.capacity; i++) {
        chunk->lines.lines[i] = 0;
    }
  }

  compress_line(chunk->lines, line);

  chunk->count++;
}

void free_chunk(Chunk* chunk){
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines.lines, chunk->capacity);
  free_value_array(&chunk->constants);
  init_chunk(chunk);
}

int add_constant(Chunk* chunk, Value value){
  write_value_array(&chunk->constants, value);
  return chunk->constants.count -1;
}

int get_line(Chunk* chunk, int offset){

  int i;
  int acc = 0;
  for (i=0; i < chunk->lines.capacity; i += 2){
    if (offset < chunk->lines.lines[i] + acc){
      return chunk->lines.lines[i + 1];
    }
    acc += chunk->lines.lines[i];
  }
}
