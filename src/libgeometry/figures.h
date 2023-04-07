typedef struct {
	int x;
	int y;
} Coordinates;

typedef struct
{
	Coordinates point1;
	float radius;
} Circle;

typedef struct
{
	Coordinates point1; // повторяется
  	Coordinates point2;
  	Coordinates point3;
} Triangle;
