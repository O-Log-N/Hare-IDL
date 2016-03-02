flex hare-idl.l
bison -dvt hare-idl.y

del hare-idl.tab.cpp
del lex.yy.cpp

ren hare-idl.tab.c hare-idl.tab.cpp
ren lex.yy.c lex.yy.cpp

sed -i.old s/"#include <unistd.h>"/\/\/\0/g lex.yy.cpp
del lex.yy.cpp.old
