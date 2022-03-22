#include "interpret.h"

#include <map>
#include <functional>

#include "stack_class.h"
#include "bitwise_io.h"

// the special stacks

stack root;
stack* current = &root;

// The following functions implement the commands of SOS

bool enter()
{
  stack* next = current->top();
  if (next)
    current = next;
  return next;
}

bool leave()
{
  if (current == &root)
    return false;
  current = current->parent();
  return true;
}

bool create()
{
  current->push(new stack);
  return true;
}

bool destroy()
{
  if (!current->top())
    return false;
  delete current->pop();
  return true;
}

bool push()
{
  stack* top = current->pop();
  if (!top) // stack was empty
    return false;
  stack* prev = current->top();
  if (!prev) // stack only contained a single item
  {
    current->push(top); // restore the stack to previous state
    return false;
  }
  prev->push(top);
  return true;
}

bool pop()
{
  stack* top = current->top();
  if (!top)
    return false;
  stack* top_of_top = top->pop();
  if (!top_of_top)
    return false;
  current->push(top_of_top);
  return true;
}

bool duplicate()
{
  stack* top = current->top();
  if (!top)
    return false;
  current->push(new stack(*top));
  return true;
}

bool exchange()
{
  stack* first = current->pop();
  if (!first)
    return false;

  stack* second = current->pop();
  current->push(first);
  // if there was no second element, the push above restored the
  // original state, so the function can return without further action
  if (!second)
    return false;

  current->push(second);
  return true;
}

bool rotate_left()
{
  current->rotate_left();
  return true;
}

bool rotate_right()
{
  current->rotate_right();
  return true;
}

bool read_bit()
{
  int bit = bitio::read_bit();
  if (bit < 0) // EOF
    return false;
  if (bit > 0)
    create();
  return true;
}

bool write_bit()
{
  bool bit = current->top();
  bitio::write_bit(bit);
  return true;
}

// map of functions (parentheses are handled separately)
std::map<char, std::function<bool()> > commands =
  {
    { '>', enter },
    { '<', leave },
    { '+', create },
    { '-', destroy },
    { '^', push },
    { '_', pop },
    { '=', duplicate },
    { '%', exchange },
    { '{', rotate_left },
    { '}', rotate_right },
    { '?', read_bit },
    { '!', write_bit }
  };

#include <iostream>

void interpret(std::string program, bool debug)
{
  std::string::size_type pos = 0, end = program.size();
  while (pos < end)
  {
    if (debug)
    {
      std::cerr << program[pos] << "; ";
      root.print(current);
    }
    if (program[pos] == ')')
    {
      // move to corresponding open parenthesis, or the beginning of
      // the program if no matching parenthesis exists
      int open = 1;
      while (pos > 0 and open > 0)
      {
        --pos;
        switch (program[pos])
        {
        case ')': ++open; break;
        case '(': --open; break;
        }
      }
    }
    else
    {
      bool precondition = true;

      auto command = commands.find(program[pos]);
      if (command != commands.end())
        precondition = command->second();

      if (precondition)
        ++pos;
      else
      {
        // find the matching closing parenthesis
        int open = 1;
        while (pos < end and open > 0)
        {
          switch (program[pos])
          {
          case '(': ++open; break;
          case ')': --open; break;
          }
          ++pos;
        }
      }
    }
    if (debug)
    {
      std::cerr << " -> ";
      root.print(current);
      std::cerr << std::endl;
    }
  }
  bitio::flush_byte();
}
