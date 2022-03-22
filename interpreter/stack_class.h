#ifndef STACK_CLASS_H_INC
#define STACK_CLASS_H_INC

#include <deque>

class stack
{
public:
  stack();
  stack(stack const&);
  stack& operator=(stack const&) = delete; // no need to assign stacks
  ~stack();
  stack* top();
  stack* parent();
  void push(stack*);
  stack* pop();
  void rotate_left();
  void rotate_right();
  void print(stack const* current) const;
private:
  stack* parent_stack;
  std::deque<stack*> contents;
};

#endif

// Local Variables:
// mode: c++
// End:
