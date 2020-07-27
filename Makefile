
output: main.o
	g++ main.o -o WeCraft -lglfw3 -lopengl32 -lglew32 -lgdi32

main.o: main.cpp
	g++ -c main.cpp

clean:
	del *.o WeCraft.exe