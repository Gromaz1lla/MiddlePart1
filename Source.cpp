#include <iostream>
#include <cmath>

class Vector
{
public:
	Vector()
	{
		x = 0; y = 0; z = 0;
	}

	Vector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	operator float() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	
	friend Vector operator+(const Vector& a, const Vector& b);
	friend Vector operator-(const Vector& a, const Vector& b); 
	friend Vector operator*(const Vector& v, float n);         

	friend std::ostream& operator<<(std::ostream& out, const Vector& v);
	friend std::istream& operator>>(std::istream& in, Vector& v); 

	friend bool operator>(const Vector& a, const Vector& b);

	float operator[](int index) const
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		return 0;
	}

private:
	float x, y, z;
};


Vector operator+(const Vector& a, const Vector& b)
{
	return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator-(const Vector& a, const Vector& b)
{
	return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector operator*(const Vector& v, float n)
{
	return Vector(v.x * n, v.y * n, v.z * n);
}

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

std::istream& operator>>(std::istream& in, Vector& v)
{
	in >> v.x >> v.y >> v.z;
	return in;
}

bool operator>(const Vector& a, const Vector& b)
{
	return static_cast<float>(a) > static_cast<float>(b);
}

int main()
{
	Vector v1, v2;

	
	std::cin >> v1 >> v2;

	// Тестирование и вывод
	std::cout << "V1: " << v1 << "\n";
	std::cout << "V2: " << v2 << "\n";
	std::cout << "Sum: " << v1 + v2 << "\n";
	std::cout << "Diff: " << v1 - v2 << "\n";
	std::cout << "Mult (V1 * 10): " << v1 * 10.0f << "\n";
	std::cout << "Length V1: " << static_cast<float>(v1) << "\n";

	if (v1 > v2)
		std::cout << "V1 is longer than V2" << "\n";
	else
		std::cout << "V1 is not longer than V2" << "\n";

	return 0;
}