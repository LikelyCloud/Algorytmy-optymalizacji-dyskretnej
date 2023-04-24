param n;
param m;
param k;

set Rows, default 1..n;
set Cols, default 1..m;

param Conteners{r in Rows, c in Cols}, binary;

var Cameras{r in Rows, c in Cols}, binary;

s.t. Con1{r in Rows, c in Cols}: Cameras[r,c] + Conteners[r,c] <= 1;
s.t. Con2{r in Rows, c in Cols: Conteners[r,c] = 1}: sum{o in max(1,c - k)..min(m, c + k)} Cameras[r,o] + sum{p in max(1,r - k)..min(n, r + k)} Cameras[p,c] >= 1;

minimize MinCameras: sum{r in Rows, c in Cols} Cameras[r,c];

solve;

display Cameras;
display MinCameras;

end;
