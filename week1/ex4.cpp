#include <iostream>
using namespace std;
void towerOfHanoi(int n, char from_, char to_, char aux_) {
	if (n == 1) {
		cout << "Movedisk 1 from " << from_ << " to " << to_ << endl;
		return;
	}
	towerOfHanoi(n - 1, from_, aux_, to_);
	cout << "Movedisk " << n << " from " << from_ << " to " << to_ << endl;
	towerOfHanoi(n - 1, aux_, to_, from_);
}
int main() {
	int n;
	cin >> n;
	towerOfHanoi(n, 'A', 'C', 'B');
	return 0;
}