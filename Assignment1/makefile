all: link

link: compile
	@echo "linking Object files"
	g++ -o bin/Studio bin/main.o bin/Studio.o bin/Action.o bin/Customer.o bin/Trainer.o bin/Workout.o

compile: src/main.cpp src/Studio.cpp src/Action.cpp src/Workout.cpp src/Trainer.cpp src/Customer.cpp
	@echo "compiling source code"
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/main.o src/main.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Action.o src/Action.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Studio.o src/Studio.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Customer.o src/Customer.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Trainer.o src/Trainer.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Workout.o src/Workout.cpp

clean:
	@echo "cleaning bin directory"
	rm -rf bin/*