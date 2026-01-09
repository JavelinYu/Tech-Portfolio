#include <iostream>
#include <vector>
#include <cstdlib> //For rand() and srand()
#include <ctime>

class Wall {
private:
	int maxHP;
	int currentHP;
	bool isDestroyed = false;
	bool hasLordPresent = false;
	bool hasShield = false;
	std::string name;
public:
	Wall(std::string n, int MHP, bool L) {name = n, maxHP = MHP, currentHP = MHP, hasLordPresent = L;}
	std::string getName() {
		return name;
	}
	void setMaxHP(int MHP) {
		maxHP = MHP;
	}
	int getMaxHP() {
		return maxHP;
	}
	void setCurrentHP(int CHP) {
		currentHP = CHP;
	}
	int getCurrentHP() {
		return currentHP;
	}
	void setIsDestroyed(bool D) {
		isDestroyed = D;
	}
	bool getIsDestroyed() {
		return isDestroyed;
	}
	void setHasLordPresent(bool L) {
		hasLordPresent = L;
	}
	bool getHasLordPresent() {
		return hasLordPresent;
	}
	void setHasShield(bool S) {
		hasShield = S;
	}
	bool getHasShield() {
		return hasShield;
	}
	void takeDamage(int damage) {
		std::cout << name << " takes " << damage << " damage!" << std::endl;
		currentHP -= damage;
		if (currentHP <= 0) {
			currentHP = 0;
			isDestroyed = true;
			std::cout << name << " has been destroyed!" << std::endl;
		}
	}
};

enum class cardName {
	Shield, Repair, Rebuild, // Defensive/Utility
	Spear, Sword, Axe, Bow, Crossbow, Catapult, Ballista, // Offensive
};

class Armory {
private:
	int damage = 0;
public:
	virtual ~Armory() = default;
	int getDmg() {
		return damage;
	}
	void setDmg(int dmg) {
		damage = dmg;
	}
	virtual std::string getName() = 0;
	virtual std::string getDesc() = 0;
	virtual cardName getCardName() = 0;
};

class Shield : public Armory {
public:
	std::string getName() {
		return "Shield";
	}
	std::string getDesc() {
		return "Blocks and ignores damage once to the player's own wall except for Catapult and Ballista.";
	}
	cardName getCardName() {
		return cardName::Shield;
	}
};

class Repair : public Armory {
public:
	std::string getName() {
		return "Repair";
	}
	std::string getDesc() {
		return "Recover your own wall's health by 1. (Cannot be used on wall with full health)";
	}
	cardName getCardName() {
		return cardName::Repair;
	}
};

class Rebuild : public Armory {
public:
	std::string getName() {
		return "Rebuild";
	}
	std::string getDesc() {
		return "Rebuilds a destroyed wall with 1 health.";
	}
	cardName getCardName() {
		return cardName::Rebuild;
	}
};

class Spear : public Armory {
public:
	std::string getName() {
		return "Spear";
	}
	std::string getDesc() {
		return "Deals 1 damage each to any one of the enemy walls in the front row and the wall behind it.";
	}
	cardName getCardName() {
		return cardName::Spear;
	}
};

class Sword : public Armory {
public:
	std::string getName() {
		return "Sword";
	}
	std::string getDesc() {
		return "Deals 1 damage each to 3 enemy walls next to each other in the front row.";
	}
	cardName getCardName() {
		return cardName::Sword;
	}
};

class Axe : public Armory {
public:
	Axe() { setDmg(2); }
	std::string getName() {
		return "Axe";
	}
	std::string getDesc() {
		return "Deals 2 damage to any one of the enemy walls in the front row.";
	}
	cardName getCardName() {
		return cardName::Axe;
	}
};

class Bow : public Armory {
public:
	std::string getName() {
		return "Bow";
	}
	std::string getDesc() {
		return "Deals 1 damage each to 3 enemy walls next to each other in the back row.";
	}
	cardName getCardName() {
		return cardName::Bow;
	}
};

class Crossbow : public Armory {
public:
	std::string getName() {
		return "Crossbow";
	}
	std::string getDesc() {
		return "Deals 2 damage to any one of the enemy walls in the back row.";
	}
	cardName getCardName() {
		return cardName::Crossbow;
	}
};

class Catapult : public Armory {
public:
	std::string getName() {
		return "Catapult";
	}
	std::string getDesc() {
		return "Deals 3 damage to any enemy wall.";
	}
	cardName getCardName() {
		return cardName::Catapult;
	}
};

class Ballista : public Armory {
public:
	std::string getName() {
		return "Ballista";
	}
	std::string getDesc() {
		return "Deals 1 damage each to 5 unique enemy walls at random. (May target destroyed walls)";
	}
	cardName getCardName() {
		return cardName::Ballista;
	}
};

class Player {
private:
	std::vector<Armory*> Deck;
	std::vector<Armory*> Hand;
	std::vector<Wall> Field;
public:
	void createDeck() {
		getDeck().push_back(new Catapult());
		getDeck().push_back(new Ballista());
		getDeck().push_back(new Shield());
		getDeck().push_back(new Repair());
		getDeck().push_back(new Rebuild());
		for (int i = 1; i <= 3; i++) {
			getDeck().push_back(new Spear());
			getDeck().push_back(new Sword());
			getDeck().push_back(new Axe());
			getDeck().push_back(new Bow());
			getDeck().push_back(new Crossbow());
		}

	}
	void shuffleDeck() {
		for (int i = Deck.size() - 1; i > 0; i--) {
			int j = rand() % (i + 1);

			Armory* temp = Deck[i];
			Deck[i] = Deck[j];
			Deck[j] = temp;
		}
	}
	void drawCard() {
		while (Hand.size() < 5 && Deck.size() > 0) {
			Hand.push_back(Deck.back());
			Deck.pop_back();
		}
		if (Deck.size() == 0) {
			std::cout << "Deck is empty!" << std::endl << std::endl;
		}
		else {
			std::cout << "Deck has " << Deck.size() << " cards left." << std::endl << std::endl;
		}
	}
	void displayHand() {
		if (Hand.empty()) {
			std::cout << "Your hand is empty." << std::endl << std::endl;
		}
		else {
			std::cout << "Your hand:" << std::endl;
			for (int i = 0; i < Hand.size(); ++i) {
				std::cout << i+1 << ") " << Hand[i]->getName() << ": " << Hand[i]->getDesc() << std::endl;
			}
			std::cout << std::endl;
		}
	}
	std::vector<Armory*>& getDeck() {
		return Deck;
	}
	std::vector<Armory*>& getHand() {
		return Hand;
	}
	
	std::vector<Wall>& getWall() {
		return Field;
	}
	void createWalls() {
		getWall().push_back(Wall("P1", 3, false));
		getWall().push_back(Wall("P2", 3, false));
		getWall().push_back(Wall("P3", 3, false));
		getWall().push_back(Wall("P4", 3, false));
		getWall().push_back(Wall("P5", 3, false));
		getWall().push_back(Wall("S1", 5, false));
		getWall().push_back(Wall("S2", 5, false));
		getWall().push_back(Wall("S3", 5, false));
		getWall().push_back(Wall("S4", 5, false));
		getWall().push_back(Wall("S5", 5, false));
	}
	void displayWalls(bool p1Turn) {
		if (p1Turn) {
			std::cout << "Your Walls: " << std::endl;
			for (int i = 0; i < Field.size(); i++) {
				std::cout << Field[i].getName() << " " << Field[i].getCurrentHP() << "/" << Field[i].getMaxHP() << "\t";
				if (i == 4 || i == 9) {
					std::cout << std::endl;
				}
			}
		}
		else {
			std::cout << "Your Opponent's Walls: " << std::endl;
			for (int i = Field.size() - 1; i >= 0; i--) {
				std::cout << Field[i].getName() << " " << Field[i].getCurrentHP() << "/" << Field[i].getMaxHP() << "\t";
				if (i == 5 || i == 0) {
					std::cout << std::endl;
				}
			}
		}
	}

	void lordPos() {
		for (int i = 5; i < Field.size(); i++) {
			if (Field[i].getHasLordPresent()) {
				std::cout << "Your lord is hidden behind " << Field[i].getName() << "." << std::endl;
			}
		}
	}	
	void hideLord(bool p1Turn) {
		int selection;
		if (p1Turn) {
			std::cout << "Player 1, ";
		}
		else {
			std::cout << "Player 2, ";
		}
		std::cout << "please conceal your lord behind one of the stone walls! (Select any of walls from S1 to S5.)" << std::endl;
		do {
			std::cin >> selection;
			if (selection <= 0 || selection >= 6) {
				std::cout << "Please select a valid wall!" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		} while (selection <= 0 || selection >= 6);
		//+4 means its on the back row because the first 5 of the vector are front rows
		Field[selection + 4].setHasLordPresent(true);
		std::cout << "Your lord is now hidden behind " << Field[selection + 4].getName() << ". Please enter anything to continue: "; 
		std::cin.ignore(10000, '\n');
		std::cin.get();
	}

	void playCard(Player& opponent);
};

void ErrorMessage() {
	std::cout << "Invalid input. Please enter a valid target: ";
	std::cin.clear();
	std::cin.ignore(10000, '\n');
}
void PassTurn() {
	std::cout << "Press Enter to continue: ";
	std::cin.ignore(10000, '\n');
	std::cin.get();
}

void getWallSelection(int& wallSelection) {
	do {
		std::cin >> wallSelection;
		if (wallSelection <= 0 || wallSelection >= 11) {
			std::cout << "Please select a valid wall!" << std::endl;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (wallSelection <= 0 || wallSelection >= 11);
}
void getFrontWallSelection(int& wallSelection) {
	do {
		std::cin >> wallSelection;
		if (wallSelection <= 0 || wallSelection >= 6) {
			std::cout << "Please select a valid wall!" << std::endl;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (wallSelection <= 0 || wallSelection >= 6);
}
void getBackWallSelection(int& wallSelection) {
	do {
		std::cin >> wallSelection;
		if (wallSelection <= 5 || wallSelection >= 11) {
			std::cout << "Please select a valid wall!" << std::endl;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (wallSelection <= 5 || wallSelection >= 11);
}

void Player::playCard(Player& opponent) {
	int cardSelection;
	int wallSelection;
	
	if(!Hand.empty()) {
		//selects card
		std::cout << "Please select a card: ";
		bool valid = false;
		//bugs on repair and rebuild
		do {
			std::cin >> cardSelection;
			if (cardSelection <= 0 || cardSelection > Hand.size()) {
				std::cout << "Please select a valid card!" << std::endl;
				std::cin.clear();
				std::cin.ignore();
				continue;
			}
			if (Hand[cardSelection - 1]->getName() == "Repair") {
				bool canRepair = false;
				for (int i = 0; i < Field.size(); i++) {
					// Check if wall is not destroyed AND not at full HP
					if (!Field[i].getIsDestroyed() && Field[i].getCurrentHP() < Field[i].getMaxHP()) {
						canRepair = true;
						break; // Found a valid target, we can proceed
					}
				}
				if (!canRepair) {
					std::cout << "Cannot play Repair! All your walls are either destroyed or at full HP." << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					continue; // Loop again, as the selection was invalid
				}
			}
			if (Hand[cardSelection - 1]->getName() == "Rebuild") {
				bool canRebuild = false;
				for (int i = 0; i < Field.size(); i++) {
					// Check if wall is not destroyed AND not at full HP
					if (Field[i].getIsDestroyed()) {
						canRebuild = true;
						break; // Found a valid target, we can proceed
					}
				}
				if (!canRebuild) {
					std::cout << "Cannot play Repair! All your walls are not destroyed." << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					continue; // Loop again, as the selection was invalid
				}
			}
			valid = true;
		} while (!valid);

		Armory* playedCard = Hand[cardSelection - 1];
		cardName cardName = playedCard->getCardName();
		//selects wall based on card selected
		using enum cardName; //works on c++ 20

		switch (cardName) {
		case Repair:{
			std::cout << "You chosen Repair. Please select one of your walls (1-5 for P1-P5, 6-10 for S1-S5): ";
			getWallSelection(wallSelection);
			while (getWall()[wallSelection - 1].getIsDestroyed()) {
				std::cout << "The wall is destroyed, please select another wall: ";
				getWallSelection(wallSelection);
			}
			while (getWall()[wallSelection - 1].getCurrentHP() == getWall()[wallSelection - 1].getMaxHP()) {
				std::cout << "The wall's HP is full, please select another wall: ";
				getWallSelection(wallSelection);
			}
			getWall()[wallSelection - 1].setCurrentHP(getWall()[wallSelection - 1].getCurrentHP() + 1);
			break;
		}
		case Rebuild:{
			std::cout << "You chosen Rebuild. Please select one of your walls (1-5 for P1-P5, 6-10 for S1-S5): ";
			getWallSelection(wallSelection);
			while (!getWall()[wallSelection - 1].getIsDestroyed()) {
				std::cout << "The wall is not destroyed, please select another wall: ";
				getWallSelection(wallSelection);
			}
			getWall()[wallSelection - 1].setIsDestroyed(false);
			getWall()[wallSelection - 1].setCurrentHP(1);
			break;
		}
		case Shield:{
			std::cout << "You chosen Shield. Please select one of your walls (1-5 for P1-P5, 6-10 for S1-S5): ";
			getWallSelection(wallSelection);
			while (getWall()[wallSelection - 1].getIsDestroyed()) {
				std::cout << "The wall is destroyed, please select another wall: ";
				getWallSelection(wallSelection);
			}
			getWall()[wallSelection - 1].setHasShield(true);
			break;
		}
		case Ballista: {
		std::cout << "You chosen Ballista! 5 of your opponent's walls will be selected at random." << std::endl;
		std::vector<int> targets;
		int i = 0;
		while (i < 5) {
			wallSelection = rand() % 10;
			bool hit = false;
			for (int j = 0; j < targets.size(); j++) {
				if (targets[j] == wallSelection) {
					hit = true;
					break;
				}
			}
			if (!hit) {
				opponent.getWall()[wallSelection].takeDamage(1);
				targets.push_back(wallSelection);
				i++;
			}
		}
		break;
	}
		case Catapult:{
			std::cout << "You chose Catapult! Please select one of your opponent's walls (1-5 for P1-P5, 6-10 for S1-S5): ";
			getWallSelection(wallSelection);
			while (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
				std::cout << "The wall is destroyed, please select another wall: ";
				getWallSelection(wallSelection);
			}
			opponent.getWall()[wallSelection - 1].takeDamage(3);
			break;
		}			
		case Spear: {
			std::cout << "You chose Spear! Please select one of your opponent's walls (1-5 for P1-P5): ";
			getFrontWallSelection(wallSelection);
			while (opponent.getWall()[wallSelection - 1].getIsDestroyed() && opponent.getWall()[wallSelection + 5 - 1].getIsDestroyed()) {
				std::cout << "The wall is this column in both rows are destroyed, please select another wall column: ";
				getFrontWallSelection(wallSelection);
			}
			//damage the front
			if (!opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
				if (opponent.getWall()[wallSelection - 1].getHasShield()) {
					opponent.getWall()[wallSelection - 1].setHasShield(false);
				}
				else {
					opponent.getWall()[wallSelection - 1].takeDamage(1);
				}
			}
			//pierce to the back
			if (opponent.getWall()[wallSelection - 1+5].getHasShield()) {
				opponent.getWall()[wallSelection - 1+5].setHasShield(false);
			}
			else {
				opponent.getWall()[wallSelection - 1+5].takeDamage(1);
			}
			break;
		}		
		case Axe: {
			std::cout << "You chose Axe! Please select one of your opponent's walls (1-5 for P1-P5): ";
			getFrontWallSelection(wallSelection);
			//redirect to the other row of the same column if destroyed
			while (opponent.getWall()[wallSelection - 1].getIsDestroyed() && opponent.getWall()[wallSelection + 5 - 1].getIsDestroyed()) {
				std::cout << "The wall is this column in both rows are destroyed, please select another wall column: ";
				getFrontWallSelection(wallSelection);
			}
			if(opponent.getWall()[wallSelection - 1].getIsDestroyed()){
				std::cout << "This wall column is destroyed, redirecting attack to the other row!" << std::endl; 
				if (opponent.getWall()[wallSelection + 5 - 1].getHasShield()) {
					opponent.getWall()[wallSelection + 5 - 1].setHasShield(false);
				}
				else {
					opponent.getWall()[wallSelection + 5 - 1].takeDamage(2);
				}
			}
			else {
				if (opponent.getWall()[wallSelection - 1].getHasShield()) {
					opponent.getWall()[wallSelection - 1].setHasShield(false);
				}
				else {
					opponent.getWall()[wallSelection - 1].takeDamage(2);
				}
			}
			break;
		}
		case Sword: {
			std::cout << "You chose Sword! Please select one of your opponent's walls (1-5 for P1-P5): ";
			getFrontWallSelection(wallSelection);
			while (opponent.getWall()[wallSelection - 1].getIsDestroyed() && opponent.getWall()[wallSelection + 5 - 1].getIsDestroyed()) {
				std::cout << "The wall is this column in both rows are destroyed, please select another wall column: ";
				getFrontWallSelection(wallSelection);
			}
			switch (wallSelection) {
			case 1:{
				//redirection + 5 to hit the back row
				if (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
					if (opponent.getWall()[wallSelection - 1 + 5].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 5].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 5].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 + 6].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 6].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 6].takeDamage(1);
					}
				}
				else {
					//damage the selection
					if (opponent.getWall()[wallSelection - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 + 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 1].takeDamage(1);
					}
				}
				break;
			}
			case 2:
			case 3:
			case 4:{
				if (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
					if (opponent.getWall()[wallSelection - 1 + 5].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 5].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 5].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 + 6].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 6].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 6].takeDamage(1);
					}
					if (opponent.getWall()[wallSelection - 1 + 4].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 4].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 4].takeDamage(1);
					}
				}
				else {
					//damage the selection
					if (opponent.getWall()[wallSelection - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 + 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 1].takeDamage(1);
					}
					if (opponent.getWall()[wallSelection - 1 - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 1].takeDamage(1);
					}
				}
				break;
			}
			case 5:{
				if (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
					if (opponent.getWall()[wallSelection - 1 + 5].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 5].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 5].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 + 4].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 4].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 4].takeDamage(1);
					}
				}
				else {
					//damage the selection
					if (opponent.getWall()[wallSelection - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 1].takeDamage(1);
					}
				}
				break;
			}
			}
			break;
		}
		case Bow: {
			std::cout << "You chose Bow! Please select one of your opponent's walls (6-10 for S1-S5): ";
			getBackWallSelection(wallSelection);
			while (opponent.getWall()[wallSelection - 1].getIsDestroyed() && opponent.getWall()[wallSelection - 5 - 1].getIsDestroyed()) {
				std::cout << "The wall is this column in both rows are destroyed, please select another wall column: ";
				getBackWallSelection(wallSelection);
			}
			switch (wallSelection) {
			case 6: {
				//redirection
				if (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
					if (opponent.getWall()[wallSelection - 1 - 5].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 5].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 5].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 - 4].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 4].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 4].takeDamage(1);
					}
				}
				else {
					//damage the selection
					if (opponent.getWall()[wallSelection - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 + 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 1].takeDamage(1);
					}
				}
				break;
			}
			case 7:
			case 8:
			case 9: {
				if (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
					if (opponent.getWall()[wallSelection - 1 - 5].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 5].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 5].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 - 6].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 6].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 6].takeDamage(1);
					}
					if (opponent.getWall()[wallSelection - 1 - 4].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 4].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 4].takeDamage(1);
					}
				}
				else {
					//damage the selection
					if (opponent.getWall()[wallSelection - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 + 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1 + 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 + 1].takeDamage(1);
					}
					if (opponent.getWall()[wallSelection - 1 - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 1].takeDamage(1);
					}
				}
				break;
			}
			case 10: {
				if (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
					if (opponent.getWall()[wallSelection - 1 - 5].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 5].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 5].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 - 6].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 6].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 6].takeDamage(1);
					}
				}
				else {
					//damage the selection
					if (opponent.getWall()[wallSelection - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1].takeDamage(1);
					}
					//hit the sides
					if (opponent.getWall()[wallSelection - 1 - 1].getHasShield()) {
						opponent.getWall()[wallSelection - 1 - 1].setHasShield(false);
					}
					else {
						opponent.getWall()[wallSelection - 1 - 1].takeDamage(1);
					}
				}
				break;
			}
			}
			break;
		}
		case Crossbow:{
			std::cout << "You chose Crossbow! Please select one of your opponent's walls (6-10 for S1-S5): ";
			getBackWallSelection(wallSelection);
			while (opponent.getWall()[wallSelection - 1].getIsDestroyed() && opponent.getWall()[wallSelection - 5 - 1].getIsDestroyed()) {
				std::cout << "The wall is this column in both rows are destroyed, please select another wall column: ";
				getBackWallSelection(wallSelection);
			}
			if (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
				std::cout << "This wall column is destroyed, redirecting attack to the other row!" << std::endl;
				if (opponent.getWall()[wallSelection - 5 - 1].getHasShield()) {
					opponent.getWall()[wallSelection - 5 - 1].setHasShield(false);
				}
				else {
					opponent.getWall()[wallSelection - 5 - 1].takeDamage(2);
				}
			}
			else {
				if (opponent.getWall()[wallSelection - 1].getHasShield()) {
					opponent.getWall()[wallSelection - 1].setHasShield(false);
				}
				else {
					opponent.getWall()[wallSelection - 1].takeDamage(2);
				}
			}
		}
		}
		Hand.erase(Hand.begin() + (cardSelection - 1));
	}
	else {
		std::cout << "You have no cards left! Please select one of your opponent's walls (1-5 for P1-P5): ";
		getFrontWallSelection(wallSelection);
		while (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
			if (opponent.getWall()[wallSelection - 1].getIsDestroyed()) {
				wallSelection = wallSelection + 5;
			}
			std::cout << "The wall is destroyed, please select another wall: ";
			getFrontWallSelection(wallSelection);
		}
		if (opponent.getWall()[wallSelection - 1].getHasShield()) {
			opponent.getWall()[wallSelection - 1].setHasShield(false);
		}
		else {
			opponent.getWall()[wallSelection - 1].takeDamage(1);
		}
	}
}

void TurnMessage(bool p1Turn) {
	if (p1Turn) {
		std::cout << "It's Player 1's turn." << std::endl;
	}
	else {
		std::cout << "It's Player 2's turn." << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	Player P1;
	Player P2;
	bool p1Turn = true;
	bool lordReveal = false;
	//setup the game
	P1.createDeck();
	P1.shuffleDeck();
	P2.createDeck();
	P2.shuffleDeck();
	P1.createWalls();
	P2.createWalls();
	//game start
	P1.hideLord(p1Turn);
	system("cls");
	P2.hideLord(!p1Turn);
	system("cls");
	//gameplay loop
	do {
		TurnMessage(p1Turn);
		if (p1Turn) {
			//Display Walls
			P2.displayWalls(!p1Turn);
			std::cout << std::endl;
			P1.displayWalls(p1Turn);
			std::cout << std::endl;
			P1.lordPos();
			std::cout << std::endl;
			P1.drawCard();
			P1.displayHand();
			P1.playCard(P2);
		}
		else {
			//Display Walls
			P1.displayWalls(p1Turn);
			std::cout << std::endl;
			P2.displayWalls(!p1Turn);
			std::cout << std::endl;
			P2.lordPos();
			std::cout << std::endl;
			P2.drawCard();
			P2.displayHand();
			P2.playCard(P1);
		} 
		for (int i = 0; i < P2.getWall().size(); ++i) {
			if (P2.getWall()[i].getHasLordPresent() && P2.getWall()[i].getIsDestroyed()) {
				lordReveal = true;
				std::cout << "Player 1 wins!" << std::endl;
				std::cout << "Player 2's lord was hiding behind " << P2.getWall()[i].getName() << "." << std::endl;
				break;
			}
		}
		for (int i = 0; i < P1.getWall().size(); ++i) {
			if (P1.getWall()[i].getHasLordPresent() && P1.getWall()[i].getIsDestroyed()) {
				lordReveal = true;
				std::cout << "Player 2 wins!" << std::endl;
				std::cout << "Player 1's lord was hiding behind " << P1.getWall()[i].getName() << "." << std::endl;
				break;
			}
		}
		PassTurn();
		p1Turn = !p1Turn; //inverts the turn boolean
		system("cls");
	} while (!lordReveal);

	std::cin.get();
	return 0;
}