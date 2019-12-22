CC=g++
CCFLAGS=-Wall -Wextra -Werror -pedantic -march=x86-64 -std=c++17

standard:
	$(CC) $(CCFLAGS) particle.cpp star.cpp firework.cpp main.cpp -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -o main.bin

optimized:
	$(CC) $(CCFLAGS) -O2 particle.cpp star.cpp firework.cpp main.cpp -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -o main.bin

debug:
	$(CC) $(CCFLAGS) -g particle.cpp star.cpp firework.cpp main.cpp -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -o main.bin

clean:
	rm -f *.o *.bin
	echo "Pulizia Completa"

