#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

class ENERGY {
private:
	int energy;
	int lvl;

public:
	ENERGY() {
		energy = 25;

	}
	void select(int num) {
		lvl = num;
	}
	int ChangeEM() {
		return lvl;
	}
	void diff() {
		if (lvl == 1) {
			energy = 25;
		}
		if (lvl == 2) {
			energy = 17;
		}
		if (lvl == 3) {
			energy = 12;
		}
	}
	void PrintEnergy() {
		cout << "Energy: " << energy << endl;
	}

	void DeductEnergy() {
		--energy;
	}
	void EnergyBall() {
		energy = energy + 5;
	}
	void BigEnergy() {
		energy = energy + 15;
	}
	int ValueEnergy() {
		return energy;
	}
	void Calc(int remaining) {

		if (remaining == 0) {
			energy = 0;
		}

		else {
			energy = remaining;
		}
	}
};

class ATTACK {
public:
	int Combat(int attack, int totalenergy) {
		int remaining = 0;

		if (attack <= totalenergy) {
			remaining = totalenergy - attack;
			return remaining;
		}
		else {
			remaining = 0;
			return remaining;
		}
	}
};

class MAZE {
protected:
	char mcaaMaze[10][10];
	int maze[10][10];
	int atk;
	char hero;
	unsigned int rowHero;
	unsigned int columnHero;
	int Remain;
	int totalenergy;

	ENERGY energy;
	ATTACK attack;

public:
	MAZE() {
		int lvl = 0;
		cout << "Welcome to Dungeon Runner" << endl;
		cout << "Choose Difficulty (1 for Easy, 2 for Normal, 3 for Hard) :\t" << endl;

		while (true) //if there char type, this will avoid infinite loop that cause by int type used for "lvl"
		{
			if ((cin >> lvl) && (lvl >= 1) && (lvl <= 3)) break;
			std::cout << "Error. Put between 1 to 3 only.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (lvl <= 3 && lvl >= 1) {
			energy.select(lvl); system("cls");
		}
		else cout << " Error. Put between 1 to 3 only.\n" << endl;

		char caaMaze[10][11] = {
			"**********",
			"*X**  ** *",
			"* *  **  *",
			"*        *",
			"* * B*** *",
			"* ** * ***",
			"* *  *   *",
			"* **     *",
			"*  * *** *",
			"**********" };
		//generator random number
		time_t qTime;
		time(&qTime);
		srand((unsigned int)qTime);

		//monster  location
		bool  FoundSpot = false;
		unsigned int monster = 0;
		unsigned int number = 1;
		unsigned int Change = energy.ChangeEM() - 1; //total monsters affected by difficulty (monsters increase with increasing of difficulty)
		while (!FoundSpot) {
			unsigned int row = rand() % 9;
			unsigned int col = rand() % 10;
			if (caaMaze[row][col] == ' ') {
				caaMaze[row][col] = '0' + number;
				monster++;
				number++;
				if (monster == (5 + Change))
					FoundSpot = true;
			}

		}

		//trivia box
		FoundSpot = false;
		unsigned int box = 0;
		while (!FoundSpot) {
			unsigned int row = rand() % 9;
			unsigned int col = rand() % 10;
			if (caaMaze[row][col] == ' ') {
				caaMaze[row][col] = 'T';
				box++;
				if (box == 1)
					FoundSpot = true;
			}

		}


		//energyball  location
		FoundSpot = false;
		unsigned int Energyball = 0;
		unsigned int ChangeM = energy.ChangeEM() - 1; //the total food values affected by difficulty (food values decrease with increasing of difficulty)
		while (!FoundSpot) {
			unsigned int row = rand() % 9;
			unsigned int col = rand() % 10;
			if (caaMaze[row][col] == ' ') {
				caaMaze[row][col] = 'E';
				Energyball++;
				if (Energyball == (5 - ChangeM))
					FoundSpot = true;
			}

		}

		//hero location
		FoundSpot = false;
		while (!FoundSpot) {
			unsigned int row = rand() % 9;
			unsigned int col = rand() % 10;
			if (caaMaze[row][col] == ' ') {
				caaMaze[row][col] = 'H';
				rowHero = row;
				columnHero = col;
				FoundSpot = true;
			}
		}

		//bomb location
		FoundSpot = false;
		unsigned int bomb = 0;
		while (!FoundSpot) {
			unsigned int row = rand() % 9;
			unsigned int col = rand() % 10;
			if (caaMaze[row][col] == ' ') {
				caaMaze[row][col] = '@';
				bomb++;
				if (bomb == 1)
					FoundSpot = true;
			}

		}


		for (unsigned int row = 0; row < 10; row++) {
			for (unsigned int column = 0; column < 10; column++) {

				mcaaMaze[row][column] = caaMaze[row][column];
			}
		}
	}

	char GetMazeSquare(unsigned int uiRow, unsigned int uiCol) {
		return mcaaMaze[uiRow][uiCol];
	}

	void PrintMaze() {
		int row, column;

		for (row = 0; row<10; row++) {
			for (column = 0; column<10; column++) {
				cout << mcaaMaze[row][column];
			}cout << endl;
		}
	}

	void step() {
		int count;
		char step;
		int x;
		energy.diff();
		energy.PrintEnergy();

		for (count = 0; count<100; count--) {
			cout << "Please enter W, A, S, D to move: ";
			cin >> step;
			system("cls");
			switch (step) {
			case 'w': case'W': {
				if (mcaaMaze[rowHero - 1][columnHero] == '*') {
					PrintMaze(); energy.PrintEnergy(); cout << "Can't go through there!" << endl; continue;
				}
				if (mcaaMaze[rowHero - 1][columnHero] == 'X') {
					mcaaMaze[rowHero - 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					PrintMaze();
					cout << "DUNGEON CLEARED!" << endl;
					return;
				}

				if (mcaaMaze[rowHero - 1][columnHero] == 'T') {
					cout << "Welcome to TRIVIA" << endl;
					cout << "Choose what you interest\n1.SPORTS\n2.SCIENTIST\n3.FUNNY" << endl;
					cin >> x;
					if (x == 1) {
						cout << "Which country’s first ever home football international was played at the Racecourse Ground in 1877 ?\n Wales" << endl;
						cout << "In inches, how big is the diameter of a basketball hoop ? 18" << endl;
						cout << "What sport used the term ‘home run’ long before baseball ? Cricket" << endl;
					}
					if (x == 2) {
						cout << "1.Albert Einstein\nAlbert Einstein changed the world of science with his brilliant work in theoretical physics. His theories, equations and ideas became the stuff of legend and his image is known around the world." << endl;
						cout << "1.Isaac Newton\nIsaac Newton developed the theory of universal gravitation as well as his famous three laws of motion, forever leaving his mark on physics, astronomy and mathematics." << endl;
						cout << "1.Charles Darwin\nCharles Darwin introduced the idea of natural selection to the world, backing up his theories on evolution with substantial observational data recorded on his long sea voyages." << endl;
					}
					if (x == 3) {
						cout << "The difference between stupidity and genius is that genius has its limits." << endl;
						cout << "Education is what remains after one has forgotten everything he learned in school." << endl;
						cout << "The worst thing I can be is the same as everybody else. I hate that." << endl;
					}
					continue;
				}

				if (mcaaMaze[rowHero - 1][columnHero] == 'E') {
					mcaaMaze[rowHero][columnHero] = ' ';
					mcaaMaze[rowHero - 1][columnHero] = 'H';
					rowHero = rowHero - 1;
					PrintMaze();
					energy.EnergyBall();
					energy.PrintEnergy();
					continue;
				}

				if (mcaaMaze[rowHero - 1][columnHero] == ' ') {
					mcaaMaze[rowHero - 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					rowHero = rowHero - 1;
					PrintMaze();
					energy.DeductEnergy();
					energy.PrintEnergy();
					if (energy.ValueEnergy() == 0) {
						cout << "You DIE!" << endl;
						return;
					}
					continue;
				}

				if (mcaaMaze[rowHero - 1][columnHero] == '@') {
					cout << "YOU HIT BOMB! YOU DIE!" << endl;
					return;
				}

				if (mcaaMaze[rowHero - 1][columnHero] == 'B') {
					mcaaMaze[rowHero - 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					rowHero = rowHero - 1;
					int temp = Question();
					if (temp == 1) {
						energy.BigEnergy();
						system("cls");
						PrintMaze();
						energy.PrintEnergy();
						cout << "You are correct! Congratulations." << endl;
						continue;
					}
					if (temp == 0) {
						system("cls");
						cout << "NOT THE CORRECT ANSWER!" << endl;
						cout << "You DIE!" << endl;
						return;
					}
				}

				else {
					maze[rowHero - 1][columnHero] = mcaaMaze[rowHero - 1][columnHero] - '0';
					totalenergy = energy.ValueEnergy();
					atk = maze[rowHero - 1][columnHero];
					Remain = attack.Combat(atk, totalenergy);
					energy.Calc(Remain);
					mcaaMaze[rowHero - 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					rowHero = rowHero - 1;
					PrintMaze();
					energy.PrintEnergy();
					if (energy.ValueEnergy() == 0) {
						cout << "You DIE!" << endl;
						return;
					}
					continue;
				}
			}

			case 'a': case 'A': {
				if (mcaaMaze[rowHero][columnHero - 1] == '*') {
					PrintMaze(); energy.PrintEnergy(); cout << "Can't go through there!" << endl; continue;
				}
				if (mcaaMaze[rowHero][columnHero - 1] == 'X') {
					mcaaMaze[rowHero][columnHero - 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					PrintMaze();
					cout << "DUNGEON CLEARED!" << endl;
					return;
				}
				if (mcaaMaze[rowHero][columnHero - 1] == 'E') {
					mcaaMaze[rowHero][columnHero - 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					columnHero = columnHero - 1;
					PrintMaze();
					energy.EnergyBall();
					energy.PrintEnergy();
					continue;
				}
				if (mcaaMaze[rowHero][columnHero - 1] == ' ') {
					mcaaMaze[rowHero][columnHero - 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					columnHero = columnHero - 1;
					PrintMaze();
					energy.DeductEnergy();
					energy.PrintEnergy();
					if (energy.ValueEnergy() == 0) {
						cout << "You DIE!" << endl;
						return;
					}
					continue;
				}
				if (mcaaMaze[rowHero][columnHero - 1] == '@') {
					cout << "YOU HIT BOMB! YOU DIE!" << endl;
					return;
				}


				if (mcaaMaze[rowHero][columnHero - 1] == 'T') {
					cout << "Welcome to TRIVIA" << endl;
					cout << "Choose what you interest\n1.SPORTS\n2.EDUCATION\n3.FUNNY" << endl;
					cin >> x;
					if (x == 1) {
						cout << "Which country’s first ever home football international was played at the Racecourse Ground in 1877 ?\n Wales" << endl;
						cout << "In inches, how big is the diameter of a basketball hoop ? 18" << endl;
						cout << "What sport used the term ‘home run’ long before baseball ? Cricket" << endl;
					}
					if (x == 2) {
						cout << "1.Albert Einstein\nAlbert Einstein changed the world of science with his brilliant work in theoretical physics. His theories, equations and ideas became the stuff of legend and his image is known around the world." << endl;
						cout << "1.Isaac Newton\nIsaac Newton developed the theory of universal gravitation as well as his famous three laws of motion, forever leaving his mark on physics, astronomy and mathematics." << endl;
						cout << "1.Charles Darwin\nCharles Darwin introduced the idea of natural selection to the world, backing up his theories on evolution with substantial observational data recorded on his long sea voyages." << endl;
					}
					if (x == 3) {
						cout << "The difference between stupidity and genius is that genius has its limits." << endl;
						cout << "Education is what remains after one has forgotten everything he learned in school." << endl;
						cout << "The worst thing I can be is the same as everybody else. I hate that." << endl;
					}
					continue;
				}

				if (mcaaMaze[rowHero][columnHero - 1] == 'B') {
					mcaaMaze[rowHero][columnHero - 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					columnHero = columnHero - 1;
					int temp = Question();
					if (temp == 1) {
						energy.BigEnergy();
						system("cls");
						PrintMaze();
						energy.PrintEnergy();
						cout << "You are correct! Congratulations." << endl;
						continue;
					}
					if (temp == 0) {
						system("cls");
						cout << "NOT THE CORRECT ANSWER!" << endl;
						cout << "You DIE!" << endl;
						return;
					}
				}
				else {
					maze[rowHero][columnHero - 1] = mcaaMaze[rowHero][columnHero - 1] - '0';
					totalenergy = energy.ValueEnergy();
					atk = maze[rowHero][columnHero - 1]; //monster energy
					Remain = attack.Combat(atk, totalenergy);//remaining energy after fight
					energy.Calc(Remain);
					mcaaMaze[rowHero][columnHero - 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					columnHero = columnHero - 1;
					PrintMaze();
					energy.PrintEnergy();
					if (energy.ValueEnergy() == 0) {
						cout << "You DIE!" << endl;
						return;
					}
					continue;
				}
			}

			case 's': case 'S': {
				if (mcaaMaze[rowHero + 1][columnHero] == '*') {
					PrintMaze(); energy.PrintEnergy(); cout << "Can't go through there!" << endl; continue;
				}
				if (mcaaMaze[rowHero + 1][columnHero] == 'X') {
					mcaaMaze[rowHero + 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					PrintMaze();
					cout << "DUNGEON CLEARED!" << endl;
					return;
				}
				if (mcaaMaze[rowHero + 1][columnHero] == 'E') {
					mcaaMaze[rowHero + 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					rowHero = rowHero + 1;
					PrintMaze();
					energy.EnergyBall();
					energy.PrintEnergy();
					continue;
				}

				if (mcaaMaze[rowHero + 1][columnHero] == 'T') {
					cout << "Welcome to TRIVIA" << endl;
					cout << "Choose what you interest\n1.SPORTS\n2.EDUCATION\n3.FUNNY" << endl;
					cin >> x;
					if (x == 1) {
						cout << "Which country’s first ever home football international was played at the Racecourse Ground in 1877 ?\n Wales" << endl;
						cout << "In inches, how big is the diameter of a basketball hoop ? 18" << endl;
						cout << "What sport used the term ‘home run’ long before baseball ? Cricket" << endl;
					}
					if (x == 2) {
						cout << "1.Albert Einstein\nAlbert Einstein changed the world of science with his brilliant work in theoretical physics. His theories, equations and ideas became the stuff of legend and his image is known around the world." << endl;
						cout << "1.Isaac Newton\nIsaac Newton developed the theory of universal gravitation as well as his famous three laws of motion, forever leaving his mark on physics, astronomy and mathematics." << endl;
						cout << "1.Charles Darwin\nCharles Darwin introduced the idea of natural selection to the world, backing up his theories on evolution with substantial observational data recorded on his long sea voyages." << endl;
					}
					if (x == 3) {
						cout << "The difference between stupidity and genius is that genius has its limits." << endl;
						cout << "Education is what remains after one has forgotten everything he learned in school." << endl;
						cout << "The worst thing I can be is the same as everybody else. I hate that." << endl;
					}

					continue;
				}

				if (mcaaMaze[rowHero + 1][columnHero] == ' ') {
					mcaaMaze[rowHero + 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					rowHero = rowHero + 1;
					PrintMaze();
					energy.DeductEnergy();
					energy.PrintEnergy();
					if (energy.ValueEnergy() == 0) {
						cout << "You DIE!" << endl;
						return;
					}
					continue;
				}

				if (mcaaMaze[rowHero + 1][columnHero] == '@') {
					cout << "YOU HIT BOMB! YOU DIE!" << endl;
					return;
				}

				if (mcaaMaze[rowHero + 1][columnHero] == 'B') {
					mcaaMaze[rowHero + 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					rowHero = rowHero + 1;
					int temp = Question();
					if (temp == 1) {
						energy.BigEnergy();
						system("cls");
						PrintMaze();
						energy.PrintEnergy();
						cout << "You are correct! Congratulations." << endl;
						continue;
					}
					if (temp == 0) {
						system("cls");
						cout << "NOT THE CORRECT ANSWER!" << endl;
						cout << "You DIE!" << endl;
						return;
					}
				}

				else {
					maze[rowHero + 1][columnHero] = mcaaMaze[rowHero + 1][columnHero] - '0';
					totalenergy = energy.ValueEnergy();
					atk = maze[rowHero + 1][columnHero];
					Remain = attack.Combat(atk, totalenergy);
					energy.Calc(Remain);
					mcaaMaze[rowHero + 1][columnHero] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					rowHero = rowHero + 1;
					PrintMaze();
					energy.PrintEnergy();
					if (energy.ValueEnergy() == 0) {
						cout << "You DIE!" << endl;
						return;
					}
					continue;
				}
			}

			case 'd': case 'D': {
				if (mcaaMaze[rowHero][columnHero + 1] == '*')
				{
					PrintMaze(); energy.PrintEnergy(); cout << "Can't go through there!" << endl; continue;
				}
				if (mcaaMaze[rowHero][columnHero + 1] == 'X') {
					mcaaMaze[rowHero][columnHero + 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					PrintMaze();
					cout << "DUNGEON CLEARED!" << endl;
					return;
				}
				if (mcaaMaze[rowHero][columnHero + 1] == 'E') {
					mcaaMaze[rowHero][columnHero + 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					columnHero = columnHero + 1;
					PrintMaze();
					energy.EnergyBall();
					energy.PrintEnergy();
					continue;

				}
				if (mcaaMaze[rowHero][columnHero + 1] == ' ') {
					mcaaMaze[rowHero][columnHero + 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					columnHero = columnHero + 1;
					PrintMaze();
					energy.DeductEnergy();
					energy.PrintEnergy();
					if (energy.ValueEnergy() == 0) {
						cout << "You DIE!" << endl;
						return;
					}
					continue;
				}

				if (mcaaMaze[rowHero][columnHero + 1] == '@') {
					cout << "YOU HIT BOMB! YOU DIE!" << endl;
					return;
				}


				if (mcaaMaze[rowHero][columnHero + 1] == 'T') {
					cout << "Welcome to TRIVIA" << endl;
					cout << "Choose what you interest\n1.SPORTS\n2.EDUCATION\n3.FUNNY" << endl;
					cin >> x;
					if (x == 1) {
						cout << "Which country’s first ever home football international was played at the Racecourse Ground in 1877 ?\n Wales" << endl;
						cout << "In inches, how big is the diameter of a basketball hoop ? 18" << endl;
						cout << "What sport used the term ‘home run’ long before baseball ? Cricket" << endl;
					}
					if (x == 2) {
						cout << "1.Albert Einstein\nAlbert Einstein changed the world of science with his brilliant work in theoretical physics. His theories, equations and ideas became the stuff of legend and his image is known around the world." << endl;
						cout << "1.Isaac Newton\nIsaac Newton developed the theory of universal gravitation as well as his famous three laws of motion, forever leaving his mark on physics, astronomy and mathematics." << endl;
						cout << "1.Charles Darwin\nCharles Darwin introduced the idea of natural selection to the world, backing up his theories on evolution with substantial observational data recorded on his long sea voyages." << endl;
					}
					if (x == 3) {
						cout << "The difference between stupidity and genius is that genius has its limits." << endl;
						cout << "Education is what remains after one has forgotten everything he learned in school." << endl;
						cout << "The worst thing I can be is the same as everybody else. I hate that." << endl;
					}

					continue;
				}

				if (mcaaMaze[rowHero][columnHero + 1] == 'B') {
					mcaaMaze[rowHero][columnHero + 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					columnHero = columnHero + 1;
					int temp = Question();
					if (temp == 1) {
						energy.BigEnergy();
						system("cls");
						PrintMaze();
						energy.PrintEnergy();
						cout << "You are correct! Congratulations." << endl;
						continue;
					}
					if (temp == 0) {
						system("cls");
						cout << "NOT THE CORRECT ANSWER!" << endl;
						cout << "You DIE!" << endl;
						return;
					}
				}
				else {
					maze[rowHero][columnHero + 1] = mcaaMaze[rowHero][columnHero + 1] - '0';
					totalenergy = energy.ValueEnergy();
					atk = maze[rowHero][columnHero + 1];
					Remain = attack.Combat(atk, totalenergy);
					energy.Calc(Remain);
					mcaaMaze[rowHero][columnHero + 1] = 'H';
					mcaaMaze[rowHero][columnHero] = ' ';
					columnHero = columnHero + 1;
					PrintMaze();
					energy.PrintEnergy();
					if (energy.ValueEnergy() == 0) {
						cout << "You DIE!" << endl;
						return;
					}
					continue;
				}
			}
			}
		}
	}

	int Question() {
		int answer;

		cout << "Welcome to the dungeon special quiz! Answer the question to get 15 energy." << endl;
		cout << "BUT, if you fail to answer, you WILL DIE!" << endl << "Let's begin" << endl << endl << endl;
		cout << "Who is largely responsible for breaking the German Enigma codes, created a test that provided a foundation for artificial intelligence?" << endl;
		cout << "1) Alan Turing" << endl << "2) Jeff Bezos" << endl << "3) George Boole" << endl << "4) Chares Babbage" << endl << endl;

		cout << "Your answer: ";
		cin >> answer;

		if (answer != 1) {
			return 0;
		}
		else {
			return 1;
		}
	}
};

int main() {

	MAZE maze1;
	ENERGY energy1;
	maze1.PrintMaze();
	maze1.step();
	cout << "Thanks For Playing" << endl;

	return 0;
}