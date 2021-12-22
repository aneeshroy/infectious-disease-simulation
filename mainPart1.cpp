#include "infect_lib.h"

using namespace std;


int main(){

	Person joe;
	int step = 1;
	for (; ; step++) {
		joe.update();
		float bad_luck = (float)rand() / (float)RAND_MAX;
		if (bad_luck > .95)
			joe.infect(5);
		cout << "On day " << step << ", Joe is "
			<< joe.status_string() << endl;
		if (joe.is_stable())
			break;
	}

};