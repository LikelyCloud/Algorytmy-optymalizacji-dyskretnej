set Shifts;
set Districts;

param MinShifts{s in Shifts};
param MinDistricts{d in Districts};
param MinCars{d in Districts, s in Shifts};
param MaxCars{d in Districts, s in Shifts};

var PoliceCars{d in Districts, s in Shifts} >= 0, integer;

s.t. Cond1{d in Districts, s in Shifts}: MaxCars[d, s] >= PoliceCars[d, s] >= MinCars[d, s];
s.t. Cond2{s in Shifts}: sum{d in Districts} PoliceCars[d, s] >= MinShifts[s];
s.t. Cond3{d in Districts}: sum{s in Shifts} PoliceCars[d, s] >= MinDistricts[d];

minimize FinalCars: sum{d in Districts, s in Shifts} PoliceCars[d, s];

solve;

display PoliceCars;
display FinalCars;

end;
