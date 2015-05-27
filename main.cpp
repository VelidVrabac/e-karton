#include <iostram>

using namespace std;

void printf(int n) {
	if(n<2)
	  cout << n;
	else {
		printf(n-1);
		cout << "," << n;
	}
}

int main(){

	cout << "Test" << endl;
	int N = 9;
	printf(N);
	return 0;
}
