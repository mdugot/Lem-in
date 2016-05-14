# Lem-in
Lem-in simulates an anthill when several ants has to find their way out of the complex anthill.  
The Anthill is a graph where several rooms are connected.  
All the ants begins at the start-room and has to go to the end-room.  
They can go to a connected room instantly only if there is no other ants in this room.  
Each ants can move one time in one turn.  
The IA try to conduct all the ants at the end in the minimum number of turn.  
................................................................................  
This project is composed of three part :  
  
The script generator.rb that can generate an anthill and write it in stdout.  
It takes four arguments :  
the width, the height and the density of the anthill, then the number of ants.  
  
The programm lem-in, the AI solve the problem.  
It reads the anthill composition in stdin and write the solution in stdout.  
  
The script viewer.rb that shows a 2d animation of the solution.  
It reads the solution in stdin.  
Once launched, you can interact with it with the keyboard :  
SPACE : Start or pause  
N :  if in paused, display the next turn.  
UP/DOWN: change the speed.  
  
The scripts viewer.rb and generator.rb need a ruby interpretor.  
The script viewer.rb needs the gosu ruby library to be installed by gem.  

To use the three parts simultaneously, you can write this command :
> ruby generator.rb [WIDTH] [HEIGHT] [DENSITY] [NUMBER] | ./lem-in | ruby viewer.rb  

Or simply launch the script TRY_ME.sh that use predefined arguments for the generator.  
................................................................................
