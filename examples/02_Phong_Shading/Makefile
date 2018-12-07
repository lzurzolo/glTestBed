CC = g++

CFLAGS = -Wall -g

INCLUDES = -I. -I../../src/public

LFLAGS = -L../../lib

LIBS = -ldl -lglfw

SRCS = phongShading.cpp ../../src/private/glTestBedBase.cpp ../../src/private/Shader.cpp ../../lib/gl3w.c ../../lib/tiny_obj_loader.cpp

OBJS = $(SRCS:.c=.o)

MAIN = ../../bin/phongShading

.PHONY: depend clean

all: $(MAIN)
	@echo phongShading has been compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
		$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
		makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it