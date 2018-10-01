#include "headers.hpp"

int main() {
	PLATFORM platform;
	platform.load("platform.txt");
	for (int i=0;i<10;i++){
		platform.simulate();
	}
}
