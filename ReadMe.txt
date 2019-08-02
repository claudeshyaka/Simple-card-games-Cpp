	************************************
	Multiple Card Games
	************************************
	
	****
	GOAL
	****
	
	This project is intended to combine and extend your use of C++ language features from the previous labs, 
	and to give you more experience programming with the C++ STL. 
	To do this, you will extend your C++ programs from the previous labs to 
		(1) add a new game (Seven Card Stud) in addition to the Five Card Draw game from lab 3 
			(which you will enhance in this lab), 
		(2) manage different numbers and kinds of player turns in the two games, 
		(3) find the highest ranking combination of cards for each player in each of those games 
			and rank the players accordingly, and (4) add features to both games so that players 
			win or lose chips in each round of play
	
	
	********
	OVERVIEW
	********
		*****************
		PROGRAM EXECUTION
		*****************
			Follow the instructions below to execution this program:
				1. run cmd.exe
				2. navigate to the executable file, which is usually <program_name.exe>
				3. Enter the program name followed by the input file.
					eg. >CSE332_lab3.exe [game_name] [player 1 name] [player 2 name] ...
	
		*******************
		PROGRAM DESCRIPTION
		*******************
	
			This is a C++ program that implements a FiveCardDraw porker game.
			
			->	NOTE: The software was developed in visual studio 2017.
	
	**************
	CODE STRUCTURE
	**************
		There are eight files that are used in this program.
			
			1. card.h - declares the card struct.
			
			2. card.c - defines of the Card struct.
												
			3. Deck.h - declares the deck class
			
			4. Deck.cpp - defines the deck class.
			
			5. Hand.h - declares the hand class.
			
			6. Hand.cpp - defines the hand class.
			
			7. Player.h - declares the player class.
			
			8. Player.cpp - defines the players class.
			
			9. Game.h - declares the game abstract class.
			
			10. Game.cpp - defines the game abstract class.
			
			11. FiveCardDraw.h - declares a FiveCardDraw class which is a derived class of the game class.
			
			12. FiveCardDraw.cpp - defines a FiveCardDraw class which is a derived class of the game class.
			
			13. SevenCardDraw.h - declares a SevenCardDraw class which is a derived class of the game class.
			
			14. SevenCardDraw.cpp - defines a SevenCardDraw class which is a derived class of the game class.
												
			15. CSE332_lab3.h - contains enumerators of return values, an enumerator of command argument, enumerator of
								the number of messages that will be passed in the PrintUsage function, and enumerators of
								exceptions.
			
			16. CSE332_lab3.cpp - contains the main function and 									
							 - PrintUsage - Takes a C-style string, a C++ string arguments and and integer, then returns an integer.
											This function printout a usage message.
	
	************
	TEST VECTORS
	************	
		*******
		Test 1: >CSE332_lab3.exe Fivecarddraw claude dave
		*******
			Welcome!
			This collection of card games contains two poker games.
			You can choose:
			-> FiveCardDraw
			-> SevenCardStud
			Wrong game name.
			Program should be run with the name of a game followed by the names of two or more players.
			eg. Usage: CSE332_lab4.exe <game_name> <player 1> <player 2> ...
			List of games
			-> FiveCardDraw
			-> SevenCardStud
			
		*******
		Test 2: >CSE332_lab3.exe FiveCardDraw
		*******	
			Welcome!
			This collection of card games contains two poker games.
			You can choose:
			-> FiveCardDraw
			-> SevenCardStud
			Too few arguments.
			Program should be run with the name of a game followed by the names of two or more players.
			eg. Usage: CSE332_lab4.exe <game_name> <player 1> <player 2> ...
			
		*******
		Test 3: >CSE332_lab3.exe FiveCardDraw claude dave
		*******
			This test vector was too long large to copy in this file. Please run the program to test.
			
		*******
		Test 4: >CSE332_lab3.exe SevenCardDraw claude dave
		*******
			This test vector was too long large to copy in this file. Please run the program to test.

	*********
	ERROR LOG
	*********
		No Errors detected after build.
		The program does have some runtime errors. More testing would need to be done to
		confirm this and resolve all runtime errors.
			
	*******
	SUMMARY
	*******
		Based on the test vectors we have generated above the program behaves partially as expected.
		They could be some bugs in this program.
		In addition this lab contain some code that was used in previous labs.
	

	