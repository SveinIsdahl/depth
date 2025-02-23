export LD_LIBRARY_PATH=raylib/lib:$LD_LIBRARY_PATH
g++ raylib.cpp -lGL -lm -lpthread -ldl -lrt -lX11 -Lraylib/lib/ -lraylib
./a.out
rm a.out