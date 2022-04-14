#include "stack_class.h"

#include <iostream>

stack::stack():
  parent_stack(nullptr)
{
}

stack::stack(stack const& other):
  parent_stack(nullptr)
{
  for (stack* element: other.contents)
    push(new stack(*element));
}

stack::~stack()
{
  for (stack* element: contents)
    delete element;
}

stack* stack::top()
{
  if (contents.empty())
    return nullptr;
  return contents.back();
}

stack* stack::parent()
{
  return parent_stack;
}

void stack::push(stack* value)
{
  value->parent_stack = this;
  contents.push_back(value);
}

stack* stack::pop()
{
  if (contents.empty())
    return nullptr;
  stack* retval = contents.back();
  contents.pop_back();
  return retval;
}

void stack::rotate_left()
{
  if (!contents.empty())
  {
    stack* bottom = contents.front();
    contents.pop_front();
    contents.push_back(bottom);
  }
}

void stack::rotate_right()
{
  if (!contents.empty())
  {
    stack* top = contents.back();
    contents.pop_back();
    contents.push_front(top);
  }
}

void stack::print(stack const* current) const
{
  std::cerr << "[";
  if (this == current)
    std::cerr << " ";
  for (stack* item: contents)
    item->print(current);
  if (this == current)
    std::cerr << " ";
  std::cerr << "]";
}
