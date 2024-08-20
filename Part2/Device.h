#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

constexpr double PI = 3.14159265358979323846;

class Shape
{
public:
    Shape(double density = 1.0) : density_(density) {}
    virtual ~Shape() {}

    virtual double GetVolume() const = 0;
    virtual double GetSurfaceArea() const = 0;
    double GetMass() const { return density_ * GetVolume(); }

    virtual Shape* Clone() const = 0;

protected:
    double density_;
};

class Cube : public Shape
{
public:
    Cube(double length = 0, double width = 0, double height = 0, double density = 1.0)
        : Shape(density), length_(length), width_(width), height_(height)
    {
        CalculateVolume();
        CalculateSurfaceArea();
    }

    Cube* Clone() const override { return new Cube(*this); }

    double GetVolume() const override { return volume_; }
    double GetSurfaceArea() const override { return surfaceArea_; }

    void SetDimensions(double length, double width, double height)
    {
        length_ = length;
        width_ = width;
        height_ = height;
        CalculateVolume();
        CalculateSurfaceArea();
    }

private:
    void CalculateVolume() { volume_ = length_ * width_ * height_; }
    void CalculateSurfaceArea() { surfaceArea_ = 2 * (length_ * width_ + width_ * height_ + height_ * length_); }

    double length_, width_, height_, volume_, surfaceArea_;
};

class Sphere : public Shape
{
public:
    Sphere(double radius = 0, double density = 1.0)
        : Shape(density), radius_(radius)
    {
        CalculateVolume();
        CalculateSurfaceArea();
    }

    Sphere* Clone() const override { return new Sphere(*this); }

    double GetVolume() const override { return volume_; }
    double GetSurfaceArea() const override { return surfaceArea_; }

    void SetRadius(double radius)
    {
        radius_ = radius;
        CalculateVolume();
        CalculateSurfaceArea();
    }

private:
    void CalculateVolume() { volume_ = (4.0 / 3.0) * PI * std::pow(radius_, 3); }
    void CalculateSurfaceArea() { surfaceArea_ = 4 * PI * std::pow(radius_, 2); }

    double radius_, volume_, surfaceArea_;
};

class Cylinder : public Shape
{
public:
    Cylinder(double height = 0, double radius = 0, double density = 1.0)
        : Shape(density), height_(height), radius_(radius)
    {
        CalculateVolume();
        CalculateSurfaceArea();
    }

    Cylinder* Clone() const override { return new Cylinder(*this); }

    double GetVolume() const override { return volume_; }
    double GetSurfaceArea() const override { return surfaceArea_; }

    void SetHeight(double height)
    {
        height_ = height;
        CalculateVolume();
        CalculateSurfaceArea();
    }

    void SetRadius(double radius)
    {
        radius_ = radius;
        CalculateVolume();
        CalculateSurfaceArea();
    }

private:
    void CalculateVolume() { volume_ = PI * std::pow(radius_, 2) * height_; }
    void CalculateSurfaceArea() { surfaceArea_ = 2 * PI * radius_ * (radius_ + height_); }

    double height_, radius_, volume_, surfaceArea_;
};

class Pyramid : public Shape
{
public:
    Pyramid(double height = 0, double baseWidth = 0, double density = 1.0)
        : Shape(density), height_(height), baseWidth_(baseWidth)
    {
        CalculateVolume();
        CalculateSurfaceArea();
    }

    Pyramid* Clone() const override { return new Pyramid(*this); }

    double GetVolume() const override { return volume_; }
    double GetSurfaceArea() const override { return surfaceArea_; }

    void SetHeight(double height)
    {
        height_ = height;
        CalculateVolume();
        CalculateSurfaceArea();
    }

    void SetBaseWidth(double baseWidth)
    {
        baseWidth_ = baseWidth;
        CalculateVolume();
        CalculateSurfaceArea();
    }

private:
    void CalculateVolume() { volume_ = (baseWidth_ * baseWidth_ * height_) / 3; }
    void CalculateSurfaceArea()
    {
        double slantHeight = std::sqrt((baseWidth_ / 2) * (baseWidth_ / 2) + height_ * height_);
        surfaceArea_ = baseWidth_ * baseWidth_ + 2 * baseWidth_ * slantHeight;
    }

    double height_, baseWidth_, volume_, surfaceArea_;
};

class Device
{
public:
    Device(const std::string& name = "no name") : name_(name) {}

    void AddShape(const Shape& shape)
    {
        shapes_.push_back(shape.Clone());
    }

    void AddSubDevice(const Device& subDevice)
    {
        subDevices_.push_back(subDevice.Clone());
    }

    double GetVolume() const
    {
        double volume = 0.0;
        for (const auto& shape : shapes_)
            volume += shape->GetVolume();
        for (const auto& subDevice : subDevices_)
            volume += subDevice->GetVolume();
        return volume;
    }

    double GetSurfaceArea() const
    {
        double surfaceArea = 0.0;
        for (const auto& shape : shapes_)
            surfaceArea += shape->GetSurfaceArea();
        for (const auto& subDevice : subDevices_)
            surfaceArea += subDevice->GetSurfaceArea();
        return surfaceArea;
    }

    double GetMass() const
    {
        double mass = 0.0;
        for (const auto& shape : shapes_)
            mass += shape->GetMass();
        for (const auto& subDevice : subDevices_)
            mass += subDevice->GetMass();
        return mass;
    }

    void Print() const
    {
        std::cout << "Device Name: " << name_ << std::endl;
        std::cout << "Total Volume: " << GetVolume() << std::endl;
        std::cout << "Total Surface Area: " << GetSurfaceArea() << std::endl;
        std::cout << "Total Mass: " << GetMass() << std::endl;

        if (!shapes_.empty())
        {
            std::cout << "Shapes:" << std::endl;
            for (const auto& shape : shapes_)
            {
                std::cout << "  Shape Volume: " << shape->GetVolume() << ", "
                    << "Surface Area: " << shape->GetSurfaceArea() << ", "
                    << "Mass: " << shape->GetMass() << std::endl;
            }
        }
        else
        {
            std::cout << "No shapes in this device." << std::endl;
        }

        if (!subDevices_.empty())
        {
            std::cout << "SubDevices:" << std::endl;
            for (const auto& subDevice : subDevices_)
            {
                subDevice->Print();
                std::cout << "--------------------" << std::endl;
            }
        }
        else
        {
            std::cout << "No sub-devices in this device." << std::endl;
        }
    }

    Device* Clone() const
    {
        Device* clonedDevice = new Device(name_);
        for (const auto& shape : shapes_)
            clonedDevice->shapes_.push_back(shape->Clone());
        for (const auto& subDevice : subDevices_)
            clonedDevice->subDevices_.push_back(subDevice->Clone());
        return clonedDevice;
    }

    ~Device()
    {
        for (auto shape : shapes_)
            delete shape;
        for (auto subDevice : subDevices_)
            delete subDevice;
    }

private:
    std::string name_;
    std::vector<Shape*> shapes_;
    std::vector<Device*> subDevices_;
};
