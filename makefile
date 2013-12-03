OBJS= lexer.o parser.o comp.o  yy.o
CC= g++
CFLAGS= -g -Wall  -std=gnu++0x

comp: $(OBJS)
	g++ ${CFLAGS} $(OBJS) -o comp  -lfl

lexer.cc: naught.lex parser.o StrUtil.h
	flex -o lexer.cc naught.lex

parser.cc:  naught.bison StrUtil.h
	bison --debug -d -o parser.cc naught.bison

%.o:%.cc
	g++ -c $(CFLAGS) $< 

clean:
	rm -f *~ *.o lexer.cc parser.cc parser.hh comp
