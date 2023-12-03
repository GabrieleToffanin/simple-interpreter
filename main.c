#include <stdio.h>

#include "common.h"
#include"debug.h"
#include "chunk.h"
#include "time.h"

int main(){
  Chunk chunk;

  init_chunk(&chunk);

  double constant = add_constant(&chunk, 1.2);
  write_chunk(&chunk, OP_CONSTANT, 125);
  write_chunk(&chunk, constant, 125);

  double constant2 = add_constant(&chunk, 57.45);
  write_chunk(&chunk, OP_CONSTANT, 126);
  write_chunk(&chunk, constant2, 126);

  write_chunk(&chunk, OP_RETURN, 127);
  disassemble_chunk(&chunk, "test chunk");
  free_chunk(&chunk); 

  return 0;
}
