test_bit: test_bit.o Bitstream.o 
	g++ -o test_bit test_bit.o Bitstream.o
test_bit.o: test_bit.cpp Bitstream.o Bitstream.h
	g++ -c test_bit.cpp
Bitstream.o: Bitstream.cpp Bitstream.h
	g++ -c Bitstream.cpp
clean:
	rm *.o
