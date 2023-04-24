param n;
param MaxTime;

set N, default 1..n;
set A, within N cross N;

param Time{(i,j) in A};
param Cost{(i,j) in A};

param Source, symbolic, in N, default 1;
param Sink, symbolic, in N, != Source, default n;

var Used{(i,j) in A}, binary;

s.t. TimeConstraint: sum{(i,j) in A} Time[i,j] * Used[i,j] <= MaxTime;
s.t. PathConstraint{i in N}: sum{(j,i) in A} Used[j,i] + (if i = Source then 1) = sum{(i,j) in A} Used[i,j] + (if i = Sink then 1);

minimize MinCost: sum{(i,j) in A} Cost[i,j] * Used[i,j];

solve;

display Used;
display MinCost;

end;
