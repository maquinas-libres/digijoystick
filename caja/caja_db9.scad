/*
    tamaño de la caja interna y borde
*/
X=50;
Y=48;
Z=13;
E=4;
$fn=20;

module base () {
// base
difference() {
translate([0,0,-2])
   minkowski () {
    cube([X+E-8,Y+E-8,Z],center=true);
   cylinder(d=8, h=1);
}

minkowski() {   
   cube([X-8,Y-8,Z],center=true);
   cylinder(d=8, h=1);
}
minkowski () {
    translate([0,24,1])
    cube([20-4,20-4,13-3],center=true);
   rotate([90,0,0]) 
    cylinder(d=4, h=1);
}
// cable
minkowski () {
    translate([0,-24,3])
    cube([7,11,7],center=true);   
   rotate([90,0,0]) 
    cylinder(d=4, h=1);
}

translate([0,Y/2-E-4,4])
        cube([X-E,E/2,Z-E],center=true); 
            // tornillos

       
        translate([(X/2)-5,(Y/2)-5,-8])
            difference() {
        cylinder(h=4, r=E, center=true);
      
        }
        translate([(X*-1/2)+5,(Y*-1/2)+5,-8])
          difference() {
        cylinder(h=4, r=E, center=true);

        }
            
        
}


    // tornillos
        translate([(X/2)-5,(Y/2)-5,-5.5])
            difference() {
              cylinder(h=2.5, r=E, center=true);
              cylinder(h=2.5, r=1.5, center=true);
            }
        translate([(X*-1/2)+5,(Y*-1/2)+5,-5.5])
          difference() {
            cylinder(h=2.5, r=E, center=true);
            cylinder(h=2.5, r=1.5, center=true);
          }

}


 
/*
font="Oxygene 1";

// texto
 linear_extrude(height = 0.5) {
    text("RETRO", font = font);
    translate([0,10,0])
    text("JOYSTICK", font = font, size=7);
}
 
 */

module tapa () {
    // tapa
    difference() {
           union() {
        difference() {
            translate([0,0,3])
               minkowski () {
                cube([X+E-13,Y+E-13,Z],center=true);
               cylinder(d=8, h=1);
            }
            // interior
            minkowski() {   
               cube([X-13,Y-13,Z],center=true);
               cylinder(d=8, h=1);
            }
            }
        translate([0,Y/2-E-2,4])
        cube([X-E,E/2,Z-E],center=true); 
            // tornillos
        translate([(X/2)-5,(Y/2)-5,3])
            difference() {
        cylinder(h=Z, r=E, center=true);
          cylinder(h=Z, r=1.5, center=true);
        }
        translate([(X*-1/2)+5,(Y*-1/2)+5,3])
          difference() {
        cylinder(h=Z, r=E, center=true);
          cylinder(h=Z, r=1.5, center=true);
        }
            }
      

        // cable
        minkowski () {
            translate([0,-24,-6])
            cube([7,10,7],center=true);   
           rotate([90,0,0]) 
            cylinder(d=4, h=1);
        }
    }

}

tapa();
base();