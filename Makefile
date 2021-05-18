cpp = g++ -std=c++17

all: pad nopad

pad: trace_nopad.cpp common.h
	$(cpp) $^ -o $@

nopad: trace_padk.cpp common.h
	$(cpp) $^ -o $@
  
.PHONY: clean
clean :
	rm pad nopad

