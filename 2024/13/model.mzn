int: ax;
int: ay;
int: bx;
int: by;
int: x;
int: y;

var 0..: a;
var 0..: b;

% X-coord
constraint ax*a + bx*b = x;

% Y-coord
constraint ay*a + by*b = y;

solve minimize 3*a + b;

output ["\(3*a + b)"];