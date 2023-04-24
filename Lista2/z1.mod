set Airports;
set Companies;

param CompanyFuel {c in Companies};
param AirportFuel {a in Airports};
param CostTable {a in Airports, c in Companies};

var val {a in Airports, c in Companies} >= 0;

s.t. Con1 {a in Airports}: sum {c in Companies} val[a, c] >= AirportFuel[a];
s.t. Con2 {c in Companies}: sum {a in Airports} val[a, c] <= CompanyFuel[c];

minimize FinalCost: sum {a in Airports, c in Companies} val[a, c] * CostTable[a, c];

solve;

display val;
display FinalCost;

end;
