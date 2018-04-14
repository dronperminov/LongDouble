FILES=main.cpp LongDouble.cpp
APP_NAME=LongDouble
OPTIMIZE_LEVEL=3
FLAGS=-Wall -Wunreachable-code -pedantic

all:
	g++ $(FLAGS) -O$(OPTIMIZE_LEVEL) $(FILES) -o $(APP_NAME)

clean:
	rm -rf $(APP_NAME)