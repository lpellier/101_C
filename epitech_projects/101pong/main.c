// header

#include "pong.h"
#include <math.h>

int main(int ac, char **av) {
	t_vector p0;
	t_vector p1;
	int time_shift;

	if (ac != 8) {
		printf("USAGE : $./101pong x0 y0 z0 x1 y1 z1 n\n");
		exit(EXIT_FAILURE);
	}
	p0.x = atof(av[1]);
	p0.y = atof(av[2]);
	p0.z = atof(av[3]);
	p1.x = atof(av[4]);
	p1.y = atof(av[5]);
	p1.z = atof(av[6]);
	time_shift = atoi(av[7]);

	// should check for arg validity

	t_vector speed;

	speed.x = p1.x - p0.x;
	speed.y = p1.y - p0.y;
	speed.z = p1.z - p0.z;
	printf("The velocity vector of the ball is:\n(%.2f, %.2f, %.2f)\n", speed.x, speed.y, speed.z);
	
	printf("At time t + %d, ball coordinates will be:\n(%.2f, %.2f, %.2f)\n", \
			time_shift, p1.x + time_shift * speed.x, p1.y + time_shift * speed.y, \
			p1.z + time_shift * speed.z);

	// Now we check whether the ball will hit the z == 0 plane
	if ((p1.z > 0 && speed.z < 0) || (p1.z < 0 && speed.z > 0) || p1.z == 0) {
		// if it will hit it, we now need to calculate the incidence angle
		// betwen speed vector (x, y, z) and plane's normal vector (0, 0, 1);	
		// this is the norme or length of vector
		double speed_norme = sqrt(pow(speed.x, 2) + pow(speed.y, 2) + pow(speed.z, 2));
		double plane_norme = sqrt(pow(1, 2)); // == 1
		// this is the scalar product of the speed vector and the normal vector of the plane (0, 0, 1)
		double scalar_product = speed.x * 0 + speed.y * 0 + speed.z * 1;
		double theta = acos(scalar_product / (speed_norme * plane_norme));
		// conversion from radians to degrees
		theta *= 180 / M_PI;
		// making sure our number is positive
		theta = fabs(theta);
		// making sure we're below 90
		while (theta > 90)
			theta -= 90;
		printf("The incidence angle is:\n%.2f degrees", theta);
	}
	else {
		printf("The ball won't reach the paddle.\n");
	}
	exit(EXIT_SUCCESS);
}
