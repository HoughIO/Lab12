#Graham Hough
#CS216 Lab12
#makefile

FILES= parsetree.h  
	#(listing all the files you need)
Lab12: $(FILES)
	g++ -o Lab12 *.cpp $^
	#(generating the lab executable file.)
	chmod u+x Lab12
	#(makes the lab file executable)
clean:
	rm -f Lab12
test:
	./Lab12
