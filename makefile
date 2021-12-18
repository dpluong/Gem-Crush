PROG = match3
# Step 1: Change "clang++" to "emcc" to run game in browser
CC = clang++

include common.mk

CXXFLAGS += `sdl2-config --cflags`
CXXFLAGS += -g 

LDFLAGS += `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# linking the program.

# Step 2: Append the below line after the "$(CC) -o $@ $(OBJS) $(LDFLAGS)" line to run game in browser
# -s USE_SDL=2 -s USE_SDL_IMAGE=2 --emrun --preload-file assets --use-preload-plugins -o match3.html
$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) 
