WIZSDK = /opt/open2x/gcc-4.1.1-glibc-2.3.6
TARGET = arm-open2x-linux

CC = $(WIZSDK)/bin/$(TARGET)-gcc
CXX = $(WIZSDK)/bin/$(TARGET)-g++
STRIP = $(WIZSDK)/bin/$(TARGET)-strip
NAME   = tutorial8

CFLAGS = -I$(WIZSDK)/include -I$(WIZSDK)/include/GLES -O2
LIBS   = -L$(WIZSDK)/lib -lopengles_lite -lwizGLES -ldl 
LDFLAGS = -g

OBJECTS = Arena.o Bullet.o ExplosionParticle.o ExplosionPS.o FixedTrig.o GameContext.o \
	GLControl.o Heart.o Input.o main.o ObjectManager.o Player.o \
	Rocket.o RocketMan.o SmokeParticle.o SmokePS.o text.o TexturedObject.o \
	TextureManager.o wiz.o VBOAllocator.o GameObject.o

all:	$(NAME)

$(NAME):$(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@
	$(STRIP) $(NAME)

.cpp.o:
	$(CXX) -c $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJECTS) $(NAME)
	rm -f $(NAME)
