#include "Utility.h"

void getIntersect(sf::Vector2f vertOne, sf::Vector2f vertTwo, int lineHeight, float& x1_, float& x2_) {
	float a = vertOne.x;
	float b = vertOne.y;
	float delta = vertTwo.x;
	float gamma = vertTwo.y;

	//std::cout << "a = " << a << ", b = " << b << 
	//			 "\ndelta = " << delta << ", gamma = " << gamma << std::endl;

	float A = b - lineHeight;
	float B = gamma - lineHeight;
	float C = gamma - b;

	//std::cout << "A = " << A << ", B = " << B << ", C = " << C << std::endl;

	float alpha = B - A;
	float beta = (2 * delta * A) - (2 * a * B);
	float eta = (a * a * B) - (delta * delta * A) - (A * B * C);

	//std::cout << "alpha = " << alpha << ", beta = " << beta << ", eta = " << eta << std::endl;

	float determinant = beta * beta - (4 * alpha * eta);

	if (determinant > 0) {
		x1_ = (-beta + sqrt(determinant)) / (2 * alpha);
		x2_ = (-beta - sqrt(determinant)) / (2 * alpha);
	}
}