#include <iostream>
#include <vector>

class Wheel {
public:
    float diameter;
    Wheel(float d) : diameter(d) {}
};

class Engine {
public:
    float power;
    Engine(float p) : power(p) {}
};

class Vehicle {
public:
    virtual void print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Vehicle& v) {
        v.print(out);
        return out;
    }
    virtual ~Vehicle() {}
};

class WaterVehicle : public Vehicle {
protected:
    float draft;
public:
    WaterVehicle(float d) : draft(d) {}
    void print(std::ostream& out) const override {
        out << "WaterVehicle Draft: " << draft;
    }
};

class RoadVehicle : public Vehicle {
protected:
    float rideHeight;
public:
    RoadVehicle(float rh) : rideHeight(rh) {}
};

class Bicycle : public RoadVehicle {
    Wheel w1, w2;
public:
    Bicycle(Wheel wh1, Wheel wh2, float rh)
        : RoadVehicle(rh), w1(wh1), w2(wh2) {}

    void print(std::ostream& out) const override {
        out << "Bicycle Wheels: " << w1.diameter << " " << w2.diameter
            << " Ride height: " << rideHeight;
    }
};

class Car : public RoadVehicle {
    Engine engine;
    Wheel w1, w2, w3, w4;
public:
    Car(Engine e, Wheel wh1, Wheel wh2, Wheel wh3, Wheel wh4, float rh)
        : RoadVehicle(rh), engine(e), w1(wh1), w2(wh2), w3(wh3), w4(wh4) {}

    void print(std::ostream& out) const override {
        out << "Car Engine: " << engine.power << " Wheels: " << w1.diameter
            << " " << w2.diameter << " " << w3.diameter << " " << w4.diameter
            << " Ride height: " << rideHeight;
    }

    float getPower() const { return engine.power; }
};

class Point {
    float x, y, z;
public:
    Point(float x, float y, float z) : x(x), y(y), z(z) {}
};

class Circle : public Vehicle {
    Point center;
    float radius;
public:
    Circle(Point p, float r) : center(p), radius(r) {}
    void print(std::ostream& out) const override {
        out << "Circle radius: " << radius;
    }
};

float getHighestPower(const std::vector<Vehicle*>& v) {
    float maxP = 0;
    for (Vehicle* veh : v) {
        Car* car = dynamic_cast<Car*>(veh);
        if (car) {
            if (car->getPower() > maxP) maxP = car->getPower();
        }
    }
    return maxP;
}

int main() {
    Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);
    std::cout << c << '\n';

    Bicycle t(Wheel(20), Wheel(20), 300);
    std::cout << t << '\n';

    std::vector<Vehicle*> v;
    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));
    v.push_back(new Circle(Point(1, 2, 3), 7));
    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));
    v.push_back(new WaterVehicle(5000));

    for (Vehicle* veh : v) {
        std::cout << *veh << "\n";
    }

    std::cout << "The highest power is " << getHighestPower(v) << '\n';

    for (Vehicle* veh : v) {
        delete veh;
    }
    v.clear();

    return 0;
}