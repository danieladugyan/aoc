% e.g [3, 5, 4, 7]
array[int] of int: targets;

% e.g [{4}, {2,4}, {3}, {3,4}, {1,3}, {1,2}]
array[int] of set of int: buttons;

set of int: L = index_set(targets);
set of int: B = index_set(buttons);

% counter values for each counter
array[L] of var int: c;

% number of clicks on each of the B buttons
array[B] of var int: clicks;

% counters are set by clicks
constraint forall(i in L) ( c[i] = sum(b in B where i in buttons[b])(clicks[b]) );

% counters must have correct values
constraint forall(i in L) ( c[i] = targets[i] );

% clicks must not be negative
constraint forall(i in B) ( clicks[i] >= 0 );
constraint forall(i in B) ( clicks[i] <= max(targets) );

solve minimize sum(clicks);

output ["\(sum(clicks))"];