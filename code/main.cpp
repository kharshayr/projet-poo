#include "headers.hpp"

int main() {
	PLATFORM platform;
	platform.load("platform.txt");
	for (int i=0;i<100;i++){
		platform.simulate("platform.txt");
	}
}
