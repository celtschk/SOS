LINK.o := $(LINK.cc)

sos: sos.o interpret.o stack_class.o bitwise_io.o

bitwise_io.o: bitwise_io.cc bitwise_io.h
interpret.o: interpret.cc interpret.h stack_class.h bitwise_io.h
sos.o: sos.cc interpret.h
stack_class.o: stack_class.cc stack_class.h
