bit-test: bit-test.o Bitstream.o
	g++ -o bit-test bit-test.o Bitstream.o
bit-test.o: bit-test.cpp Bitstream.o Bitstream.h
	g++ -c bit-test.cpp
test_write: test_write.o Bitstream.o 
	g++ -o test_write test_write.o Bitstream.o
test_write.o: test_write.cpp Bitstream.o Bitstream.h
	g++ -c test_write.cpp
Bitstream.o: Bitstream.cpp Bitstream.h
	g++ -c Bitstream.cpp
clean:
	rm *.o
