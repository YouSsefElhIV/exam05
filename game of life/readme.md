1- check for the ac == 4 args.

2- save the args, the heigth, width, iteration.

3- read the instruction from the stdin and store them in an array of instructions.

4- init the game array with spaces (32).

5- start the game.
  
      1- we make 3 loops, first for the iterations, and the other 2 are ofc for the array heigth and width.
      
      2- at the inside we need to check for the neighbors and count them, so we need to check left, right, up, dowwn, top right, top left, bottom left, bottom right.
      
      2-1 we can hard code and use i - 1 i + 1 etc... or more simply we can use 2 loops from -1 to +1 for the i and j which would go throught all 8 dirrection (Don't forget to skip the 9th 
      
      direction which is itself x,y or 0,0.
      
      3- after checking all 8 directions and counting the neighbors we check:
      
       3-1 if we are on live cell we check if we must kill it or leave it (nc <= 1 || nc >= 4 small population or over populated).
       
       3-2 if we are on dead cell we check if we must revive it or leave it (nc == 3).
      
      4- in the this process we must not use the same symbols 0 and 1 since it would interfere with the next cell count so we use new symbols (n: new alive cell must not count it as a 
      
      neighbor yet, 1: cell that died but must still count it).
      
      5- when we are done with this iteration we make the alive cells 'n' formale by giving them 0 and getting rid of the dead one '1' by replacing them by ' ' aka 32 a space.

6- print the results of the game aka print the array game[][].
