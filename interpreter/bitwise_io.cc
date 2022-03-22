#include "bitwise_io.h"

// here, stdio is better suited than iostream, as only single
// characters are read and written anyway
#include <cstdio>


int const bits_per_byte = 8;
unsigned char const high_bit = 1 << (bits_per_byte - 1);

// input state
unsigned char current_input;
unsigned char mask = 0; // first we need to read a byte

// output state
unsigned char current_output = 0;
int missing_bits = bits_per_byte;

int bitio::read_bit()
{
  // read a new character if required
  if (!mask)
  {
    int character = std::getchar();
    if (character < 0) // end of file
      return -1;
    mask =  high_bit;
    current_input = character;
  }

  bool result = current_input & mask;
  mask >>= 1;
  return result;
}

void bitio::write_bit(bool bit)
{
  current_output <<= 1;
  current_output |= bit;
  --missing_bits;
  if (missing_bits == 0)
    flush_byte();
}

void bitio::flush_byte()
{
  putchar(current_output);
  current_output = 0;
  missing_bits = bits_per_byte;
}
