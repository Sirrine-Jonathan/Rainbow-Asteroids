CC = g++

all: asteroids

asteroids: driver.o game.o uiInteract.o  velocity.o uiDraw.o ship.o rocks.o powerUp.o point.o flyingObject.o bullet.o
	$(CC) -o asteroids driver.o game.o uiInteract.o velocity.o uiDraw.o ship.o rocks.o powerUp.o point.o flyingObject.o bullet.o -framework OpenGL -framework GLUT

driver.o: game.o uiInteract.o
	$(CC) -c driver.cpp

game.o: game.cpp uiDraw.o uiInteract.o point.o velocity.o flyingObject.o bullet.o ship.o rocks.o powerUp.h
	$(CC) -c game.cpp

uiInteract.o: uiInteract.cpp point.o
	$(CC) -c uiInteract.cpp

uiDraw.o: uiDraw.cpp point.o
	$(CC) -c uiDraw.cpp

velocity.o: velocity.cpp
	$(CC) -c velocity.cpp

ship.o: ship.cpp flyingObject.o uiDraw.o
	$(CC) -c ship.cpp

rocks.o: rocks.cpp flyingObject.o uiDraw.o
	$(CC) -c rocks.cpp

powerUp.o: powerUp.cpp flyingObject.o uiDraw.o
	$(CC) -c powerUp.cpp

point.o: point.cpp velocity.o
	$(CC) -c point.cpp

flyingObject.o: flyingObject.cpp velocity.o point.o uiDraw.o
	$(CC) -c flyingObject.cpp

bullet.o: bullet.cpp flyingObject.o uiDraw.o
	$(CC) -c bullet.cpp

.PHONY: all clean

clean:
	rm *.o asteroids