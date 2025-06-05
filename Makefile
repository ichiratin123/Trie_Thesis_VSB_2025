compiler = g++

flags = -std=c++23 -Wall -municode

src = $(wildcard *.cpp)

object = $(src:.cpp=.o)

target = trieapp.exe

all: $(target)

$(target): $(object)
	$(compiler) $(flags) -o $(target) $(object)

%.o: %.cpp
	$(compiler) $(flags) -c $< -o $@

clean:
	del /Q $(object) $(target) 2> nul

