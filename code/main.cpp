#include "headers.hpp"

int main() {
	PLATFORM platform;
	platform.load("platform.txt");
	int steps;
	cout << "Number of steps = ?" << endl;
	cin >> steps;
	for (int i=0;i<steps;i++){
		platform.simulate();
	}
}
