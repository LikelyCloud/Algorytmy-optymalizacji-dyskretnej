set Products;
set Machines;

param MaxTime;
param Prices{p in Products};
param LaborCost{m in Machines};
param MaterialCost{p in Products};
param MaxDemand{p in Products};
param TreatmentTime{p in Products, m in Machines};

var Output{p in Products} >= 0;

s.t. TimeConstraint{m in Machines}: (sum{p in Products} Output[p] * TreatmentTime[p, m]) / 60 <= MaxTime;
s.t. DemandConstraint{p in Products}: Output[p] <= MaxDemand[p];

maximize Profit: sum{p in Products} Output[p] * (Prices[p] - MaterialCost[p] - sum{m in Machines} (TreatmentTime[p,m] * LaborCost[m] / 60));

solve;

display Output;
display Profit;

end;
