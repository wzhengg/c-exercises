#include <stdio.h>

float fahr_to_celsius(float fahr);

int main(void) {
	float fahr;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	for (fahr = lower; fahr <= upper; fahr += step)
		printf("%3.0f %6.1f\n", fahr, fahr_to_celsius(fahr));

	return 0;
}

float fahr_to_celsius(float fahr) {
	return (5.0/9.0) * (fahr-32.0);
}
