
del *.h.idlbin
C++2HareIDL.exe -find-class=ItemBase -find-class=Item -find-class=Root -serialize -o sample.h.idlbin sample.h -- -fno-ms-compatibility -I..\..\src -xc++