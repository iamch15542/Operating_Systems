run: 
	g++ -Wall -o hw4_Series hw4_Series.c -lpthread
	g++ -Wall -o hw4_Pi hw4_Pi.c -lpthread
	g++ -Wall -o gen test_generater.cpp

clean:
	rm -f gen hw4_Series hw4_Pi output.txt

test:
	./gen > output.txt && ./hw4_Series < output.txt && rm -f output.txt

test2:
	./hw4_Pi	
