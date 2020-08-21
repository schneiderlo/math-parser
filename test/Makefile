ROOT_DIR := ../../..

CXXFLAGS=-MMD -MP -std=c++14 -U__STRICT_ANSI__
CXXFLAGS+= -I$(ROOT_DIR)

src = main.cpp 

includes = module/core/library.hpp

object=$(src:.cpp=.o)

%: %.o
	$(LINK.cpp) -o $@ $^
	
main: $(object)

-include $(src:.cpp=.d)

clean:
	rm -f *~ *.o *.d

rmv: clean
	rm -f main
