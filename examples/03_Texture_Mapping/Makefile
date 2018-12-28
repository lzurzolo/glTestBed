CC = g++

CFLAGS = -Wall -g

INCLUDES = -I. -I../../src/public

LFLAGS = -L../../lib

LIBS = -ldl -lglfw

SRCS = textureMapping.cpp ../../src/private/glTestBedBase.cpp ../../src/private/Shader.cpp ../../lib/gl3w.c ../../lib/tiny_obj_loader.cpp ../../lib/stb_image.cpp

OBJS = $(SRCS:.c=.o)

MAIN = ../../bin/textureMapping

.PHONY: depend clean

all: $(MAIN)
	@echo textureMapping has been compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
		$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
		makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it