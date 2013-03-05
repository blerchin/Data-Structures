test_write: test_write.o Bitstream.o 
	g++ -o test_write test_write.o Bitstream.o
test_write.o: test_write.cpp Bitstream.o Bitstream.h
	g++ -c test_write.cpp
Bitstream.o: Bitstream.cpp Bitstream.h
	g++ -c Bitstream.cpp
clean:
	rm *.o
