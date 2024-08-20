#include <iostream>
#include "Device.h"

int main()
{
    Device device("Main Device");

    Cube cube(3.0, 4.0, 5.0, 2.0);
    Sphere sphere(2.5, 1.5);
    Cylinder cylinder(7.0, 3.0, 1.8);
    Pyramid pyramid(8.0, 5.0, 1.2);

    device.AddShape(cube);
    device.AddShape(sphere);
    device.AddShape(cylinder);
    device.AddShape(pyramid);

    Device Device1("Device1");
    Cube smallCube(2.0, 2.0, 2.0, 1.0);
    Sphere smallSphere(1.5, 1.0);

    Device1.AddShape(smallCube);
    Device1.AddShape(smallSphere);
    device.AddSubDevice(Device1);

    device.Print();

    std::cout << "Press Enter to exit...\n";
    std::cin.get();

    return 0;
}
