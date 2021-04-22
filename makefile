.PHONY = all clean
cc = gcc
libs = -lGL -lglfw -lGLEW
flags = -g
# macros = -D_GLFW_X11 -D_GLFW_GLX -D_GLFW_USE_OPENGL

SRCS = $(wildcard src/*.c)
BINS = $(SRCS:src/%.c=%)
LINK = $(BINS:%=build/%.o)

all: ${BINS}
	@echo linking...
	@$(cc) $(libs) $(flags) $(LINK) -o gratest
	@echo done

%: src/%.c
	@echo compiling $<
	@$(cc) -c $< -o build/$@.o

clean:
	@echo cleaning...
	@rm build/* gratest
