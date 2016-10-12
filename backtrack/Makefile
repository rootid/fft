BUILD_DEBUG := yes

.PHONY: all combination 
all: ; @echo BUILD_DEBUG is $(BUILD_DEBUG)
	@echo BUILD_INFO $(BUILD_INFO)


ifdef BUILD_DEBUG
FLAGS_DEBUG := -gdwarf-2
endif

FLAGS_ELEVEN = -std=c++11

	
clean :
	rm -rf *.out

combination : 
	$(CXX) $(FLAGS_ELEVEN) $(FLAGS_DEBUG) combinationSum.cpp
