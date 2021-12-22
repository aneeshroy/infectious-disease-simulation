#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <time.h>

class Person {
public:

	int status = 0;

	bool is_susceptible() {
		return (status == 0);
	}

	bool is_infected() {
		return (status > 0);
	}

	bool is_stable() {
		return status == -1;
	}

	string status_string() {
		if (status == 0) {
			return "healthy";
		}
		else if (status == -1) {
			return "recovered";
		}
		else if (status == -2) {
			return "vaccinated";
		}
		else {
			string n = to_string(status);
			return ("sick for " + n + " more days.");
		}

	}

	void update() {

		if (status > 0) {
			status--;
			if (status == 0) {
				status--;
			}
		}
	}

	void infect(int n) {
		if (is_susceptible()) {
			status = n;
		}
	}

};

class Population {
public:
	vector<Person> pop;
	float prob_transmission;
	float vaxxed;
	int sicklength;

	Population(int npeople) {
		pop.resize(npeople);
	}

	void set_probability_of_transfer(float prob) {
		prob_transmission = prob;
	}

	void set_sicktime(int time) {
		sicklength = time;
	}

	void set_vaxxed(int percent) {
		vaxxed = percent;
	}

	void random_infection() {

		while (count_infected() == 0) {
			int infect = rand() % pop.size();

			pop[infect].infect(sicklength);
		}

	}

	int count_infected() {

		int count = 0;
		for (Person dude : pop) {

			if (dude.is_infected()) {
				count++;
			}

		}

		return count;
	}

	void neighbor_infect(int i) {

		float decider;

		if (pop[i].status == (sicklength)) {
			return;
		}

		if (pop[i].is_infected()) {

			if (i == 0) {
				if (pop[i + 1].is_infected()) {
					return;
				}
				else {
					decider = (float)rand() / RAND_MAX;
					if (prob_transmission > decider) {
						pop[i + 1].infect(sicklength);
					}
				}

			}

			else if (i == (pop.size() - 1)) {
				if (pop[i - 1].is_infected()) {
					return;
				}
				else {
					decider = (float)rand() / RAND_MAX;
					if (prob_transmission > decider) {
						pop[i - 1].infect(sicklength);
					}
				}

			}

			else {
				if (!pop[i - 1].is_infected()) {
					decider = (float)rand() / RAND_MAX;
					if (prob_transmission > decider) {
						pop[i - 1].infect(sicklength);
					}
				}
				if (!pop[i + 1].is_infected()) {
					decider = (float)rand() / RAND_MAX;
					if (prob_transmission > decider) {
						pop[i + 1].infect(sicklength);
					}
				}

			}
		}

	}

	void vaccinate() {

		int numvax = (vaxxed / 100) * pop.size();
		numvax++;
		int count = 0;

		while (count < numvax) {

			int index = rand() % pop.size();
			pop[index].status = -2;
			count++;

		}

	}

	void rand_interactions(int i) {

		int num = rand() % 6 + 1;
		int count = 0;
		while (count < num) {

			int index = rand() % pop.size();

			if (pop[index].is_infected()) {
				if (pop[i].is_infected()) {
				}
				else {
					float decider = (float)rand() / RAND_MAX;
					if (prob_transmission > decider) {
						pop[i].infect(sicklength);
					}
				}
			}
			else {
				if (pop[i].is_infected()) {
					float decider = (float)rand() / RAND_MAX;
					if (prob_transmission > decider) {
						pop[index].infect(sicklength);
					}
				}
			}

			count++;
		}

	}

	void update() {

		for (int i = 0; i < pop.size(); i++) {

			rand_interactions(i);
			neighbor_infect(i);
			pop[i].update();

		}

	}
};
