#include <iostream>
#include <cstdio>
#include <time.h>
#include "infect_lib.h"


using namespace std;

int main() {

	srand(time(NULL));

	Population westcampus(200);
	westcampus.set_probability_of_transfer(.2);
	westcampus.set_sicktime(6);
	westcampus.set_vaxxed(90);
	
	westcampus.vaccinate();
	westcampus.random_infection();

	int count = 1;
	while (westcampus.count_infected() != 0) {
		westcampus.update();
		count++;
	}
	//int num = 0;
	//for (Person dude : westcampus.pop) {
	//	if(dude.is_susceptible()) {
	//		num++;
	//	}
	//}
	//cout << num << endl;
	//float percent = (float)num / (float)(200 - 180);

	//cout << percent;

	cout << "disease ended after " << count << " steps." << endl;;


}

