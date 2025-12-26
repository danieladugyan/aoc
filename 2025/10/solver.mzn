% e.g [3, 5, 4, 7]
array[int] of int: targets;

% e.g [{4}, {2,4}, {3}, {3,4}, {1,3}, {1,2}]
array[int] of set of int: buttons;

set of int: T = index_set(targets);
set of int: B = index_set(buttons);

% map of buttons
array[T, B] of int: buttonMap = array2d(T, B, [
  if t in b then 1 else 0 endif
  | t in T, b in buttons
]);

% counter values for each counter
% array[T] of var int: counters;

% number of clicks on each of the B buttons
array[B] of var int: clicks;

% clicks must not be negative or too large
constraint forall(i in B) ( 0 <= clicks[i] /\ clicks[i] <= max(targets) );

% Solve buttonMap * clicks = target (Ax = b)
constraint forall(t in T) ( sum(i in B)(buttonMap[t, i] * clicks[i]) = targets[t] );

solve minimize sum(clicks);

output ["\(sum(clicks))"];