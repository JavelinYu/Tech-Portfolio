#include <iostream>

class Shape() {
private:
	double width, length, height;
public:
	Shape(double w, l, h) {
		width = w;
		length = l;
		height = h;
	}
	~Shape(){}
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
		std::
		return width;
	}
	double GetLength() {
		
		return length;
	}
	double GetHeight() {
		
		return height;
	}
}

class Triangle : public Shape {
public:
	Triangle(double w, l, h) : Shape(w, l, h) {

	}
}

class Circle : public Shape {
private:
	double PI = 3.1416;
public:
	Circle(double w,l,h) :Shape(w,l,h) {
		PI = p;
	}

}

class Square : public Shape {
public:
	Square(double w, l, h) :Shape(w, l, h) {

	}
	double CalculateArea() {
		return GetWidth() * GetLength(); 
	}
}

int main() {
	Square One(2, 2, 2); 
	std::cout << Square.CalculateArea;

}
#include <iostream>

class Shape() {
private:
	double width, length, height;
public:
	Shape(double w, l, h) {
		width = w;
		length = l;
		height = h;
	}
	~Shape(){}
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
		std::
		return width;
	}
	double GetLength() {
		
		return length;
	}
	double GetHeight() {
		
		return height;
	}
}

class Triangle : public Shape {
public:
	Triangle(double w, l, h) : Shape(w, l, h) {

	}
}

class Circle : public Shape {
private:
	double PI = 3.1416;
public:
	Circle(double w,l,h) :Shape(w,l,h) {
		PI = p;
	}

}

class Square : public Shape {
public:
	Square(double w, l, h) :Shape(w, l, h) {

	}
	double CalculateArea() {
		return GetWidth() * GetLength(); 
	}
}

int main() {
	Square One(2, 2, 2); 
	std::cout << Square.CalculateArea;

}