#include <iostream>

class Shape {
private:
	double width;
	double length;
	double height;
public:
	Shape(double w, double l, double h) {
		width = w;
		length = l;
		height = h;
	}
	~Shape() {}
	void SetWidth(double w) {
		width = w;
	}
	void SetLength(double l) {
		length = l;
	}
	void SetHeight(double h) {
		height = h;
	}
	double GetWidth() {
		return width;
	}
	double GetLength() {
		return length;
	}
	double GetHeight() {
		return height;
	}
};

class Triangle : public Shape {
public:
	Triangle(double w, double l, double h) : Shape(w, l, h) {

	}
	double CalculateArea() {
		return GetWidth() * GetLength() / 2;
	}
	//either prism or pyramid
	double CalculateVolume() {
		return GetWidth() * GetLength() * GetHeight() / 3; //using triangle base pyramid
	}
};

class Circle : public Shape {
private:
	double PI = 3.1416;
public:
	Circle(double w, double l, double h) :Shape(w, l, h) {

	}
	double CalculateArea() {
		return PI * GetWidth() * GetWidth();
	}
	double CalculateVolume() {
		return PI * GetWidth() * GetWidth() * GetWidth() * 4 / 3;
	}
};

class Square : public Shape {
public:
	Square(double w, double l, double h) :Shape(w, l, h) {

	}
	double CalculateArea() {
		return GetWidth() * GetLength();
	}
	double CalculateVolume() {
		return GetWidth() * GetLength() * GetHeight();
	}
};

void ErrorMessage() {
	std::cout << "Invalid input. Please enter a number: ";
	std::cin.clear();
	std::cin.ignore();
}

int main() {
	int n; 
	char c;
	double w=0, l=0, h=0;
	bool error = true;
	do {
		do {
			error = false;
			std::cout << "Please enter a number to select a shape (1: Triangle, 2: Circle, 3: Square): " << std::endl;
			std::cin >> n;	
			if (n == 2) {
				std::cout << "Please enter width: ";
				while (!(std::cin >> w)) {
					ErrorMessage();
				}
			}
			else if (n == 1 || n == 3) {
				std::cout << "Please enter width: ";
				while (!(std::cin >> w)) {
					ErrorMessage();
				}
				std::cout << "Please enter length: ";
				while (!(std::cin >> l)) {
					ErrorMessage();
				}
				std::cout << "Please enter height: ";
				while (!(std::cin >> h)) {
					ErrorMessage();
				}
			}
			else {
				ErrorMessage();
				system("cls");
				error = true;
			}
		} while (error);//selects shape and enter dimensions
		switch (n) {
		case 1: {
			Triangle t(w, l, h);
			std::cout << "The area of the triangle is: " << t.CalculateArea() << std::endl;
			std::cout << "The volume of the triangle is: " << t.CalculateVolume() << std::endl;
			break;
		}
		case 2: {
			Circle c(w, l, h);
			std::cout << "The area of the circle is: " << c.CalculateArea() << std::endl;
			std::cout << "The volume of the circle is: " << c.CalculateVolume() << std::endl;
			break;
			}
		case 3: {
			Square s(w, l, h);
			std::cout << "The area of the square is: " << s.CalculateArea() << std::endl;
			std::cout << "The volume of the square is: " << s.CalculateVolume() << std::endl;
			break;
			}
		}//calculates area and volume of shape chosen
		do {
			std::cout << "Do you want to restart? (Y/N): ";
			std::cin >> c;
			if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') {
				system("cls");
				error = false;
			}
			else {
				std::cout << "Invalid input! Try again!" << std::endl;
				std::cin.clear();
				std::cin.ignore();
				system("cls");
				error = true;
			}
		} while (error);//confirmation to restart the program
	} while (c == 'y' || c == 'Y');//repeats the entire program if yes

	std::cin.get();
	return 0;
}