/* Designed by A.J. v.d. Werken, Oct 2021       */
/* Optial sensor RPR220 - find it on AliExpress */
/* Fits on a Sensus 620 Watermeter (Vitens)     */
/* Works with WATERLEZER (ESPHOME)              */

$fn=30;

module sensus620mount_top()
{
    // Solid
    difference()
    {
        union()
        {
            hull()
            {
                translate([-17.4,-4.6,0]) cylinder(d2=14, d1=16, h=8);
                translate([17.4,-4.6,0]) cylinder(d2=14, d1=16, h=8);
                translate([0,0,0]) cylinder(d1=20, d2=15, h=8);
            }
        }
        // Holes
        translate([2.5,-9.5,1.5]) cube([13.5,8,4.1], center=true);
        translate([2.5,-3,3]) cube([15,14,8],center=true);
        translate([-17.4,-4.6,-0.5]) cylinder(d=5.2,h=10);
        translate([17.4,-4.6,-0.5]) cylinder(d=5.2,h=10);
        
        translate([-17.4,-4.6,4]) cylinder(d1=5, d2=20,h=10);
        translate([17.4,-4.6,4]) cylinder(d1=5, d2=20,h=10);
        
        translate([-17.4,-4.6,-7]) cylinder(d=10.5,h=10);
        translate([17.4,-4.6,-7]) cylinder(d=10.5,h=10);
        
    }
}

module sensus620mount_bottom()
{
    difference()
    {
        // Solid
        union()
        {
            hull()
            {
                translate([-17.4,-4.6,0]) cylinder(d=16,h=3);
                translate([17.4,-4.6,0]) cylinder(d=16,h=3);
                translate([0,0,0]) cylinder(d=20,h=3);
            }
      
            translate([2.5,-1,3.5]) cube([13.4,10,6],center=true);

            translate([-17.4,-4.6,3]) cylinder(d=9.5,h=2.5);
            translate([17.4,-4.6,3]) cylinder(d=9.5,,h=2.5);
            }
        // Holes
        hull()
        {
            translate([2.5,0,0]) cube([7,5.1,0.1], center=true);      
            translate([2.4,0,7]) cube([6.7,5.3,0.1], center=true);
        }
        translate([2.5,-9.5,3.5]) cube([13.5,8,6.1], center=true);
        
        translate([-17.4,-4.6,-0.5]) cylinder(d=5.2,h=10);
        translate([17.4,-4.6,-0.5]) cylinder(d=5.2,h=10);
    }
 
}

translate([0,-13,8]) scale([1,-1,-1]) sensus620mount_top();
translate([0,13,0]) sensus620mount_bottom();

