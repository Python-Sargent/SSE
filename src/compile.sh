g++ -c main.cpp
g++ main.o -o ../run/sse-app -lsfml-graphics -lsfml-window -lsfml-system
cd ../run
./sse-app
cd ../src