//User competes versus the computer where the user can pick between 3 different moves, while the computer has
//different probabilities between the three moves that is calculated automatically. The user and computer each start with 100
//health and switch taking turns every round. The game ends when either of the two party's health is below 0
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

//The function below takes into account both of the user's, computer's health, and the user's move
void attack(double& attackerHealth, double& defenderHealth, int move) {
	//User starts moving
	double prob, compProb, compMoveProb, gainUserHealth = 0.0, loseUserHealth = 0.0, gainCompHealth = 0.0, loseCompHealth = 0.0;
	if (move == 1) {
		prob = (double) rand() / double(RAND_MAX);
		loseCompHealth = (15.0 * prob) + 15.0;
		defenderHealth -= loseCompHealth;
		if (defenderHealth <= 0.0) {
			defenderHealth = 0.0;
			cout << "The user attacked, dealing " << loseCompHealth << " damage to the computer." << endl;
			cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
			cout << "The battle is over. The user has won." << endl;
			return;
		}
		cout << "The user attacked, dealing " << loseCompHealth << " damage to the computer." << endl;
		cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
	} else if (move == 2) {
		prob = (double) rand() / double(RAND_MAX);
		loseCompHealth = prob * 50.0;
		defenderHealth -= loseCompHealth;
		if (defenderHealth <= 0.0) {
			defenderHealth = 0.0;
			cout << "The user attacked, dealing " << loseCompHealth << " damage to the computer." << endl;
			cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
			cout << "The battle is over. The user has won." << endl;
			return;
		}
		cout << "The user attacked, dealing " << loseCompHealth << " damage to the computer." << endl;
		cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
	} else if (move == 3) {
		prob = (double) rand() / double(RAND_MAX);
		gainUserHealth = (prob * 15.0) + 5;
		attackerHealth += gainUserHealth;
		if (attackerHealth >= 100.0) {
			attackerHealth = 100.0;
		}
		cout << "The user gained " << gainUserHealth << " health." << endl;
		cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
	}
	
	//Computer starts moving
	compMoveProb = (double)rand() / double(RAND_MAX);
	if (compMoveProb <= (1.0 / 3)) {
		compProb = (double)rand() / double(RAND_MAX);
		loseUserHealth = (15.0 * compProb) + 15.0;
		attackerHealth -= loseUserHealth;
		if (attackerHealth <= 0.0) {
			attackerHealth = 0.0;
			cout << "The computer attacked, dealing " << loseUserHealth << " damage to the user." << endl;
			cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
			cout << "The battle is over. The computer has won." << endl;
			return;
		}
		cout << "The computer attacked, dealing " << loseUserHealth << " damage to the user." << endl;
		cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
	}
	else if (compMoveProb > (1.0 / 3) && compMoveProb <= (2.0 / 3)) {
		compProb = (double)rand() / double(RAND_MAX);
		loseUserHealth = compProb * 50.0;
		attackerHealth -= loseUserHealth;
		if (attackerHealth <= 0.0) {
			attackerHealth = 0.0;
			cout << "The computer attacked, dealing " << loseUserHealth << " damage to the user." << endl;
			cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
			cout << "The battle is over. The computer has won." << endl;
			return;
		}
		cout << "The computer attacked, dealing " << loseUserHealth << " damage to the user." << endl;
		cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
	}
	else if (compMoveProb >= (2.0 / 3)) {
		compProb = (double)rand() / double(RAND_MAX);
		gainCompHealth = (compProb * 15.0) + 5.0;
		defenderHealth += gainCompHealth;
		if (defenderHealth >= 100.0) {
			defenderHealth = 100.0;
		}
		cout << "The computer gained " << gainCompHealth << " health." << endl;
		cout << "The user has " << attackerHealth << " health and the computer has " << defenderHealth << " health." << endl;
	}
	return;
}

//Takes the user's move, calls the function, and also evaluates if any of the two party's health is below 0
int main() {
	srand(time(NULL));
	double userHealth = 100.0, compHealth = 100.0, moveU = 0.0;
	while (userHealth != 0.0 || compHealth != 0.0) {
		cout << "Enter a value to move (1, 2, or 3): "; cin >> moveU;
		while (moveU != 1 && moveU != 2 && moveU != 3 || (cin.fail())) {
			cin.clear();
			cout << "Error. Enter a value to move (1, 2, or 3): ";  cin >> moveU;
		}
		moveU = (int) moveU;
		attack(userHealth, compHealth, moveU);
		if (userHealth == 0.0 || compHealth == 0.0) {
			break;
		}
	}
	return 0;
}
