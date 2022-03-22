#ifndef BITWISE_IO_H_INC
#define BITWISE_IO_H_INC

namespace bitio
{
  // read a single bit from stdin; returns -1 for EOF
  int read_bit();

  // write a single bit to stdout
  void write_bit(bool);

  // forcean incomplete byte to stdout, left_padding it with zeros
  void flush_byte();
}

#endif

// Local Variables:
// mode: c++
// End:
