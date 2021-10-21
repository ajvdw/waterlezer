/* Designed by A.J. v.d. Werken, Oct 2021    */
/* Case for WEMOS D1 ESP8266 incl shield     */  
/* Works with WATERLEZER (ESPHOME)           */

$fn=60;

module waterlezer_case_bottom()
{
    difference()
    {
        // solid
        union()
        {
            translate( [0.5,0.5,0]) cube( [54, 34, 6] ); 
            translate( [-1.5,11.5,0] ) cube( [3,12,3]);  
        }
        // holes
        translate( [2,2.25,3] ) cube( [47, 30.5, 12] );
        translate( [2,2.25,4.5] ) cube( [51, 30.5, 12] );
        translate( [2,3.5,0.8] ) cube( [47, 28, 12] );
        translate( [-0.5,11,3] ) cube( [3,13,8]);
        translate( [52.5,11.5,3.5] ) cube( [3,12,9]);   
    
        
    }
}

module waterlezer_case_top()
{
    difference()
    {
        // solid
        union()
        {
            hull()
            {
                translate([1.5,1.5,0]) cylinder( d=2.5, h=17 );
                translate([57.5,1.5,0]) cylinder( d=2.5, h=17 );            
                translate([57.5,37.5,0]) cylinder( d=2.5, h=17 );
                translate([1.5,37.5,0]) cylinder( d=2.5, h=17 );
            }
            translate([27.5,-2,0]) cylinder( d=10, h=17 );
            translate([27.5,41,0]) cylinder( d=10, h=17 );
           
        }
        // holes
        translate( [5,3.5,1.2] ) cube( [52, 32, 20] );
        translate( [2,2,11] ) cube( [55, 35, 20] );
        translate( [2,3.5,7.5] ) cube( [5.5, 32, 20] );
        
        translate( [7,2,7.5] ) cube( [46, 35, 20] );
        translate( [7,2,1.6] ) cube( [46, 35, 20] );
        
        translate( [-0.5,13,5] ) cube( [3,13,20]);
        translate( [56.5,13,6.5] ) cube( [3,13,20]);      
        translate([27.5,-2,-0.5]) cylinder( d=5, h=20 ); 
        translate([27.5,41,-0.5]) cylinder( d=5, h=20 ); 
        translate([27.5,41,-0.5]) cylinder( d1=8, d2=5, h=3 ); 
        translate([27.5,-2,-0.5]) cylinder( d1=8, d2=5, h=3 ); 
        
        for (i=[0:5], x=10 + i*5) 
        {
            translate( [x,10,-0.5] ) cube( [2,19,3]);            
        }

   }
}

translate( [0,-40,0] ) 
    waterlezer_case_top();
translate( [2.5,7,0] ) 
    waterlezer_case_bottom();