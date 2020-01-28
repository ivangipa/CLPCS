# CLPCS
Algorithms for the Container Loading Problem with Complete Shipment constraint

Parameters:

-TL: time limit. We use 300+60p, being p the class of the instance

-I: file to read

-FO: file to write

-s: seed

-BA: set always as 1 (to use block generation)

-P: sets the maximum allowable lost of the blocks. Set 1 for BR1-7 instances and 0.98 for BR8-15

-VCS: to use VCS heuristic objective function, set always as 2.

-CS: to use the complete shipment constraint. Possible values:

      0: VNS without complete shipment
      
      1: 5.3 procedure
      
      2: 5.2 procedure
      
      3: 5.4 procedure
      
      4: 5.1 procedure
      
-PT X sets percentage as X% for the 5.4 procedure
