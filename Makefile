program: program.o public.o stm.o try_block.o template.o expression.o decl_specifier_seq.o
	g++ -o program program.o public.o stm.o try_block.o template.o expression.o decl_specifier_seq.o
program.o: program.cpp public.cpp public.h 
	g++ -c program.cpp
public.o: public.cpp public.h
	g++ -c public.cpp
stm.o: stm.cpp stm.h public.h
	g++ -c stm.cpp
try_block.o: try_block.cpp try_block.h public.h
	g++ -c try_block.cpp
template.o: template.cpp template.h public.h
	g++ -c template.cpp
expression.o: expression.cpp expression.h public.h
	g++ -c expression.cpp
decl_specifier_seq.o: decl_specifier_seq.cpp decl_specifier_seq.h public.h
	g++ -c decl_specifier_seq.cpp
clean:
	rm *.o
	rm program
