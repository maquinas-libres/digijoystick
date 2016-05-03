/*
    tamaño de la caja interna y borde
*/
X=40;
Y=31;
Z=13;
E=4;
$fn=20;

difference() {
    cube([31,X,20],center=true);
    translate([0,0,2])
        cube([31-3,X-3,20],center=true);
    translate([10,0,0])
    cube([20,28,12],center=true);

    translate([-10,0,0])
    cube([20,19,12],center=true);
}

translate([50,0,0]) {
    translate([0,0,2])    
    cube([31-4,X-4,2],center=true);
    cube([31,X,2],center=true);
}