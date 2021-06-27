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

bool checkCollinearity(sf::Vector2f siteOne, sf::Vector2f siteTwo, sf::Vector2f siteThree) {
	return (siteOne.x * (siteTwo.y - siteThree.y) + siteTwo.x * (siteThree.y - siteOne.y) + siteThree.x * (siteOne.y - siteTwo.y) == 0);
}

void getCircleCenter(sf::Vector2f siteOne, sf::Vector2f siteTwo, sf::Vector2f siteThree, float& x_, float& y_) {
	if (checkCollinearity(siteOne, siteTwo, siteThree)) {
		float A = 2 * (siteTwo.x - siteOne.x);
		float C = 2 * (siteTwo.y - siteOne.y);
		float D = siteTwo.y * siteTwo.y - siteOne.y * siteOne.y + siteTwo.x * siteTwo.x - siteOne.x * siteOne.x;
		float E = 2 * (siteTwo.x - siteThree.x);
		float H = 2 * (siteTwo.y - siteThree.y);
		float K = siteThree.y * siteThree.y - siteTwo.y * siteTwo.y + siteThree.x * siteThree.x - siteTwo.x * siteTwo.x;

		y_ = (D * E - K * A) / (H * A - C * E);
		x_ = -(C * y_ - D) / A;
	}
}