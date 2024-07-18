#include "..\header\triangle.hpp"

Triangle::Triangle(float a, float b, float c)
	: side_a_(a), side_b_(b), side_c_(c) {
	ValidateTriangle();
}

Triangle::Triangle(const Triangle& other)
	: side_a_(other.side_a_),
	side_b_(other.side_b_),
	side_c_(other.side_c_) {
	ValidateTriangle();
}

Triangle::Triangle(float sides, float height)
	: side_a_(sides), side_b_(sides), side_c_(sqrt(pow(sides / 2, 2) + pow(height, 2))) {
	ValidateTriangle();
}

void Triangle::ValidateTriangle() {
	AreSidesValid();
	DoSidesFormTriangle();
	AreSidesWithinLimits();
}

void Triangle::AreSidesValid() {
	if (std::isnan(side_a_) || std::isinf(side_a_) || std::isnan(side_b_) || std::isinf(side_b_) || std::isnan(side_c_) || std::isinf(side_c_)) {
		throw std::logic_error("Sides are NaN or infinite. Please choose valid values.");
	}
}

void Triangle::DoSidesFormTriangle() {
	if (side_a_ + side_b_ <= side_c_ || side_a_ + side_c_ <= side_b_ || side_b_ + side_c_ <= side_a_) {
		throw std::logic_error("Sides do not form a triangle. Please choose another option.");
	}
}

void Triangle::AreSidesWithinLimits() {
	if (side_a_ > kMaxSideLength || side_b_ > kMaxSideLength || side_c_ > kMaxSideLength) {
		throw std::logic_error("Sides are too big. Please choose smaller values.");
	}
	if (side_a_ <= 0 || side_b_ <= 0 || side_c_ <= 0) {
		throw std::logic_error("Sides can not be less than or equal to zero. Please choose another option.");
	}
	if (side_a_ < kMinSideLength || side_b_ < kMinSideLength || side_c_ < kMinSideLength) {
		throw std::logic_error("Sides are too small. Please choose bigger values.");
	}
}

float Triangle::GetSideA() const {
	return side_a_;
}

float Triangle::GetSideB() const {
	return side_b_;
}

float Triangle::GetSideC() const {
	return side_c_;
}

float Triangle::CalculateAreaHeron() const {
	float s = (side_a_ + side_b_ + side_c_) / 2;
	return sqrt(s * (s - side_a_) * (s - side_b_) * (s - side_c_));
}

float Triangle::CalculateAreaEqual() const {
	return (side_a_ * side_a_) * (sqrt(3) / 4);
}

Triangle Triangle::operator++() {
	side_a_++;
	side_b_++;
	side_c_++;
	return Triangle(side_a_, side_b_, side_c_);
}

Triangle Triangle::operator++(int) {
	side_a_++;
	side_b_++;
	side_c_++;
	return *this;
}
Triangle Triangle::operator+=(float value) {
	side_a_ = side_a_ + value;
	side_b_ = side_b_ + value;
	side_c_ = side_c_ + value;
	return Triangle(side_a_, side_b_, side_c_);
}

Triangle Triangle::operator--() {
	side_a_--;
	side_b_--;
	side_c_--;
	return Triangle(side_a_, side_b_, side_c_);
}

Triangle Triangle::operator--(int) {
	Triangle temp = *this;
	side_a_--;
	side_b_--;
	side_c_--;
	return temp;
}

Triangle Triangle::operator-=(float value) {
	side_a_ = side_a_ - value;
	side_b_ = side_b_ - value;
	side_c_ = side_c_ - value;
	return Triangle(side_a_, side_b_, side_c_);
}