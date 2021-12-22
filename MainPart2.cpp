#include <iostream>
#include <cstdio>
#include <time.h>
#include "infect_lib.h"


using namespace std;

int main() {

	srand(time(NULL));

	cout << "west campus size: ";
	int popsize;
	cin >> popsize;

	cout << "probability of transmission: ";
	float probtrans;
	cin >> probtrans;

	cout << "length of sickness: ";
	int sicktime;
	cin >> sicktime;

	cout << "% vaccinated: ";
	float vaxxed;
	cin >> vaxxed;
	cout << endl;

	Population westcampus(popsize);
	westcampus.set_probability_of_transfer(probtrans);
	westcampus.set_sicktime(sicktime);
	westcampus.set_vaxxed(vaxxed);

	westcampus.vaccinate();
	westcampus.random_infection();

	int count = 1;
	while (westcampus.count_infected() != 0) {

		printf("In step %*d #sick: %*d : ", 4, count, 4, westcampus.count_infected());
		
		for (Person dude : westcampus.pop) {
			
			if (dude.is_susceptible()) {
				cout << "? ";
			}
			else if (dude.is_stable()) {
				cout << "- ";
			}
			else if (dude.status == -2) {
				cout << "x ";
			}
			else {
				cout << "+ ";
			}

		}

		cout << endl;
		westcampus.update();
		count++;
	}

	cout << "disease ended after " << count << " steps." << endl;;


}