// An interpreter for the SOS programming language

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>

// the actual interpreter
#include "interpret.h"

using std::literals::string_literals::operator ""s;

auto helptext = R"""(usage:
  $0 [-d] file
  $0 [-d] -c code
  $0 --help

Execute code in the SOS programming language.

With option -c, interpret the code given as next argument. Otherwise,
execure the code from the given file.

The option --help displays this help and exits.
)"""s;

// output help text to standard error
void help(std::ostream& out, std::string progname)
{
  for (auto pos = helptext.find("$0");
       pos != std::string::npos;
       pos = helptext.find("$0"))
  {
    helptext.replace(pos, 2, progname);
  }
  out << helptext;
}

int main(int argc, char* argv[])
{
  // we need at least one argument
  if (argc < 2) // program needs help text
  {
    help(std::cerr, argv[0]);
    return EXIT_FAILURE;
  }

  // with the argument --help, output help but don't return an error
  if (argv[1] == "--help"s)
  {
    help(std::cout, argv[0]);
    return EXIT_SUCCESS;
  }

  bool debug = (argv[1] == "-d"s);

  // With the option -c, execute the code from the command line
  if (argv[debug + 1] == "-c"s)
  {
    // there should be exactly one argument after the -c
    if (argc != debug + 3)
    {
      help(std::cerr, argv[0]);
      return EXIT_FAILURE;
    }

    // interpret the code
    interpret(argv[debug + 2], debug);
    return EXIT_SUCCESS;
  }

  // if we get here, the filename form is used. In that case, there
  // should be exactly one argument.
  if (argc != debug + 2)
  {
    help(std::cerr, argv[0]);
    return EXIT_FAILURE;
  }

  // Read the program from the file and interpret it
  std::ifstream file(argv[debug + 1]);
  std::string code(std::istreambuf_iterator<char>(file), {});

  interpret(code, debug);
  return EXIT_SUCCESS;
}
