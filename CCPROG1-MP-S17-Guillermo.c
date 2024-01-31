/* 
	Description: A Text Based Game Based on Game of Thrones
	Programmed by:   Eugene Guillermo	S17
	Last Modified:	2/6/2022
	[Acknowledgements: https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20 https://www.geeksforgeeks.org/clear-console-c-language/ https://www.programmingsimplified.com/c/dos.h/sleep https://www.geeksforgeeks.org/c-fopen-function-with-examples/ https://www.geeksforgeeks.org/fprintf-in-c/ https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm https://www.tutorialspoint.com/c_standard_library/c_function_atof.htm]
*/

// Libraries Included
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

// Self-Defined Function Prototypes
int getRandomNumber (int nLow, int nUp);
int chooseTradingPartners (void);
void displayGoodsPricesAndQuant (int nPrices[8], int nItems[8]);
void displaySpecifications (int nDayCounter, float fGD, float fDebt, float fSavings, int nCurrCap, int nMaxCap);
void displayGoods (int nItems[8]);
float addInterest (float fInterestRate, float fGD);
void listPrices (int nCurrLoc, int nPrices[8]);
void printPartner (int nCurrLoc);
void displayHighScore(char cName[20], float fGD, float fSavings, float fDebt);
void actionBuy (float *fGD, int nMaxCap, int *nCurrCap, int nPrices[8], int nItems[8]);
void actionSell (float *fGD, int *nCurrCap, int nPrices[8], int nItems[8]);
void actionBank (float *fGD, float *fSavings, float *fDebt, int *nDayCounter, int *nCurrCap, int *nMaxCap, int *nCurrLoc, int nItems[8]);
void actionWheelhouse (int *nDayCounter, int *nMaxCap, int *nCurrLoc, float *fSavings, float *fDebt, float *fGD, int nPrices[8]);
int displayAndGetAction (float fGD, float fSavings, float fDebt, int nDayCounter, int nCurrCap, int nMaxCap, int nCurrLoc, int nItems[8], int nPrices[8]);
void displayCurrentHighScores(void);

int main (void)
{
	// Initialize the variables
	
	// Integer Variables and Arrays
	int 	nPrices[8],		// Array of prices in the order of the items
			nCurrLoc,		// Current location or trading partner (9 for quitting)
			nDayCounter,	// Number of days left
			nCurrCap,		// Current capacity of the warehouse
			nMaxCap,		// Maximum capacity of the warehouse
			nItems[8],		// Array of number of items owned in the order of the items
			nCount;			// Counter variable for for loops, while loops, and others
			
	// Float Variables
	float	fGD,			// Golden Dragons owned by user
			fDebt,			// Debt owed by user to the iron bank
			fSavings;		// Savings owned by user in the iron bank
	
	// Character Variables
	char	cAChoice, 		// Action Choice
			cKeyPressed,   	// Key Pressed by user
			cName[20],	   	// Name inputted by user
			cAgree;		   	// If user agrees (y or n)
	
	// Intro strings
	char cPremise[500] = "After being handed the Iron Throne, King Bran of House Stark, decided to devise a strategic plan to improve the economic growth of the Six Kingdoms.\nThe Royal Treasury currently has 2,000 Golden Dragons (GD) only.\nTo accomplish this task, he instructed his Hand, Lord Tyrion Lannister, and his Master of Coin, Lord Bronn of the Blackwater, to go to trade with other kingdoms in Westeros and other free cities in Essos.\n\0 ";
	char cInstructions[500] = ", you must grow the money or Golden Dragons.\n Use the wheelhouse to go to different trading partners.\n You will, however, lose a day each time you use the wheelhouse.\n You can also use the help of the Iron Bank to grow your money.\n However, keep in mind to sell all items by the end of the game since they won't be counted in the score.\n Use arrow keys and the enter button to navigate through the game.\n\0";
	
	// Set starting specifications
	nDayCounter = 15;
	fGD = 2000.0;
	fDebt = fSavings = nCurrCap = 0.0;
	nMaxCap = 50;
	nItems[0] = nItems[1] = nItems[2] = nItems[3] = nItems[4] = nItems[5] = nItems[6] = nItems[7] = 0;
	
	// Get rid of trash values
	nPrices[0] = nPrices[1] = nPrices[2] = nPrices[3] = nPrices[4] = nPrices[5] = nPrices[6] = nPrices[7] = 0;
	
	// Print fancy letters
	printf("   _____                .__    .__                __________                   __               __   \n  /     \\ _____    ____ |  |__ |__| ____   ____   \\______   \\_______  ____    |__| ____   _____/  |_ \n /  \\ /  \\\\__  \\ _/ ___\\|  |  \\|  |/    \\_/ __ \\   |     ___/\\_  __ \\/  _ \\   |  |/ __ \\_/ ___\\   __\\\n/    Y    \\/ __ \\\\  \\___|   Y  \\  |   |  \\  ___/   |    |     |  | \\(  <_> )  |  \\  ___/\\  \\___|  |  \n\\____|__  (____  /\\___  >___|  /__|___|  /\\___  >  |____|     |__|   \\____/\\__|  |\\___  >\\___  >__|  \n        \\/     \\/     \\/     \\/        \\/     \\/                          \\______|    \\/     \\/      \n\n\n");
	
	// Self credit
	printf("By Eugene Guillermo\n\n");
	
	// Display current high scores stored in a csv file (if none, it will display whitespaces.)
	displayCurrentHighScores();
	
	// Pause for user input
	/* (NOTE) Probably because of no echo if user presses more than once, it'll affect other getch() */
	printf("------------------------  Press any key once except Q to start. Press Q to quit.  ------------------------\n");
	cKeyPressed = getch();
	// Clear Screen
	system("cls");
	
	
	if (cKeyPressed != 'Q' && cKeyPressed != 'q')
	{		
		// Print one character at a time until null character is seen
		nCount = 0;
		while(cPremise[nCount] != '\0')
		{
			printf("%c", cPremise[nCount]);
			Sleep(15);
			nCount++;
		}
		
		// Pause for user input
		/* (NOTE) Probably because of no echo if user presses more than once, it'll affect other getch() */
		printf("------------------------  Press any key once except Q to start. Press Q to quit.  ------------------------\n");
		cKeyPressed = getch();
		// Clear Screen
		system("cls");
		
		// If user didn't want to quit
		if (cKeyPressed != 'Q' && cKeyPressed != 'q')
		{
			// Get name right
			cAgree = 'N';
			while (cAgree == 'N')
			{
				printf("Please enter your name. (Maximum of 19 characters.) ");
				scanf(" %[^\n]%*c", cName);
				
				// Repeat if user accidentally inputs wrong
				do
				{
					printf("You are ");
					for (nCount = 0; nCount < strlen(cName); nCount++)
					{
						printf("%c", cName[nCount]);
					}
					printf(", right?(Y or N) ");
					
					scanf(" %c", &cAgree);
					cAgree = toupper(cAgree);
				}
				while (cAgree != 'Y');
			}
			system("cls");
			
			// Print name
			for (nCount = 0; nCount < strlen(cName); nCount++)
			{
				printf("%c", cName[nCount]);
			}
			
			// Print one character at a time until null character is seen
			nCount = 0;
			while(cInstructions[nCount] != '\0')
			{
				printf("%c", cInstructions[nCount]);
				Sleep(15);
				nCount++;
			}
			
			// Pause for user input
			/* (NOTE) Probably because of no echo if user presses more than once, it'll affect other getch() */
			printf("------------------------  Press any key once except Q to start. Press Q to quit.  ------------------------\n");
			cKeyPressed = getch();
			// Clear screen
			system("cls");		
			
			// If user didn't want to quit
			if (cKeyPressed != 'Q' && cKeyPressed != 'q')
			{			
				// Let the player choose a trading partner
				nCurrLoc = chooseTradingPartners();
								
				// Clear screen
				system("cls");
				
				// If user didn't want to quit
				if (nCurrLoc != 9)
				{
					// Get random prices based on trading partner
					listPrices (nCurrLoc, nPrices);
				
					while (nCurrLoc != 9 && nDayCounter)
					{
						// Display various things and ask user for his action
						cAChoice = displayAndGetAction (fGD, fSavings, fDebt, nDayCounter, nCurrCap, nMaxCap, nCurrLoc, nItems, nPrices);
						
						// Let player exit
						if (cAChoice == 'Q')
						{
							// Clear screen
							system("cls");
								
							// Display current progress so far
							printf ("______________________________________________\n\n");
							displaySpecifications (nDayCounter, fGD, fDebt, fSavings, nCurrCap, nMaxCap);
							displayGoods (nItems);
											
							// To end the do while loop
							nCurrLoc = 9;
						}
						
						// Buying goods
						if (cAChoice == 'B')
							actionBuy (&fGD, nMaxCap, &nCurrCap, nPrices, nItems);
						
						// Selling goods
						else if (cAChoice == 'S')
							actionSell (&fGD, &nCurrCap, nPrices, nItems);
						
						// Going to bank
						else if (cAChoice == 'I')
							actionBank (&fGD, &fSavings, &fDebt, &nDayCounter, &nCurrCap, &nMaxCap, &nCurrLoc, nItems);
			
						// Going to wheelhouse
						else if (cAChoice == 'W')
						{
							// If day isn't zero yet
							if (nDayCounter)
								actionWheelhouse (&nDayCounter, &nMaxCap, &nCurrLoc, &fSavings, &fDebt, &fGD, nPrices);
						}
					}		
				}
				
				// Display current progress so far
				system("cls");
				printf ("______________________________________________________________\n\n");
				displaySpecifications (nDayCounter, fGD, fDebt, fSavings, nCurrCap, nMaxCap);
				printf ("______________________________________________________________\n\n");
				displayGoods (nItems);
				printf ("______________________________________________________________\n\n");
				displayHighScore(cName, fGD, fSavings, fDebt);
			}
		}
		
	}
	
	// Print Fancy Letters
	printf("__________.__                   __     _____.___.              ___________            __________.__               .__                __________.__    .__         __________                  __              __   \n\\__    ___|  |__ _____    ____ |  | __ \\__  |   | ____  __ __  \\_   ________________  \\______   |  | _____  ___.__|__| ____   ____   \\__    ___|  |__ |__| ______ \\______   _______  ____    |__| ____  _____/  |_\n  |    |  |  |  \\\\__  \\  /    \\|  |/ /  /   |   |/  _ \\|  |  \\  |    __)/  _ \\_  __ \\  |     ___|  | \\__  \\<   |  |  |/    \\ / ___\\    |    |  |  |  \\|  |/  ___/  |     ___\\_  __ \\/  _ \\   |  _/ __ _/ ___\\   __\\\n  |    |  |   Y  \\/ __ \\|   |  |    <   \\____   (  <_> |  |  /  |     \\(  <_> |  | \\/  |    |   |  |__/ __ \\\\___  |  |   |  / /_/  >   |    |  |   Y  |  |\\___ \\   |    |    |  | \\(  <_> )  |  \\  ___\\  \\___|  |  \n  |____|  |___|  (____  |___|  |__|_ \\  / ______|\\____/|____/   \\___  / \\____/|__|     |____|   |____(____  / ____|__|___|  \\___  /    |____|  |___|  |__/____  >  |____|    |__|   \\____/\\__|  |\\___  \\___  |__|  \n               \\/     \\/     \\/     \\/  \\/                          \\/                                    \\/\\/            \\/_____/                  \\/        \\/                         \\______|    \\/    \\/      \n\n");
	
	// Wait for user input before exiting program
	printf("\n\n------------------------  Press any key once to continue to exit.  ------------------------\n");
	getch();
	
	return 0;

}

/* 
	This function generates a random number in certain boundaries
	Precondition: nLow and nUp should be positive values
	@param nLow is the lower bound of the random number
	@param nUp is the upper bound of the random number
	@return nRandNum price that was generated
*/

int getRandomNumber (int nLow, int nUp)
{
	// Initialize variable
	int nRandNum;
	
	// initialize a random sequence based on time
	srand(time(NULL));
		
	// generates a number between a lower bound and an upperbound
	nRandNum = rand() % (nUp - nLow + 1) + nLow;
		
	return nRandNum;

}

/* 
	This function simply displays the trading partners and returns the player's choice
		@return nChoice choice of the user
	*/
int chooseTradingPartners (void)
{
	// Initialize variable to be used
	int nChoice;
	char cKeyPressed;
	
	nChoice = 1;
	cKeyPressed = '0';	
	while (cKeyPressed != 13)
	{
		system("cls");
				
		printf ("--- TRADING PARTNERS ---\n");
		
		// Print trading partners with less than (<) and greater than (>) symbols to indicate choice
		if (nChoice == 1)
			printf("\t >Winterfell< \n");
		else
			printf("\t  Winterfell \n");
		
		if (nChoice == 2)
			printf("\t >Lys< \n");
		else
			printf("\t  Lys \n");
			
		if (nChoice == 3)
			printf("\t >Myr< \n");
		else
			printf("\t  Myr \n");
		
		if (nChoice == 4)
			printf("\t >Pentos< \n");
		else
			printf("\t  Pentos \n");
			
		if (nChoice == 5)
			printf("\t >Qohor< \n");
		else
			printf("\t  Qohor \n");
			
		if (nChoice == 6)
			printf("\t >Voltanis< \n");
		else
			printf("\t  Voltanis \n");
		
		if (nChoice == 7)
			printf("\t >Quit< \n\n");
		else
			printf("\t  Quit \n\n");
			
		cKeyPressed = getch();
		
		// Let user navigate through the choices using arrow keys but not let them out of bounds
		if(cKeyPressed == 72 && nChoice != 1)
			nChoice--;
		else if (cKeyPressed == 80 && nChoice != 7)
			nChoice++;
		
	}
	
	// Change 7 to 9 for quit
	if (nChoice == 7)
		nChoice = 9;
	
	// Return variable to be used in the main function
	return nChoice;	
}


/* 
	This function prints a table of the goods, their price, and amount currently owned.
	Precondition: Prices must be in order of the order of goods
	@param nPrices is the array of prices of the goods
	@param nItems is the array of items owned
*/
void displayGoodsPricesAndQuant (int nPrices[8], int nItems[8])
{
	// Print each line
	printf ("ITEM\t WARES AND GOODS\t \t \t SELLING/BUYING PRICE\t  Quantity Owned\n");
	printf ("[1] \t Sweet Beet \t \t \t \t \t %i\t\t\t%i\n", nPrices[0], nItems[0]);
	printf ("[2] \t Timber \t \t \t \t \t %i\t\t\t%i\n", nPrices[1], nItems[1]);
	printf ("[3] \t Intricate Lace \t \t \t \t %i\t\t\t%i\n", nPrices[2], nItems[2]);
	printf ("[4] \t Intoxicating Perfume \t \t \t \t %i\t\t\t%i\n", nPrices[3], nItems[3]);
	printf ("[5] \t Pale Amber Wine \t \t \t \t %i\t\t\t%i\n", nPrices[4], nItems[4]);
	printf ("[6] \t Myrish Eye \t \t \t \t \t %i\t\t\t%i\n", nPrices[5], nItems[5]);
	printf ("[7] \t Qohorik Tapestry \t \t \t \t %i\t\t\t%i\n", nPrices[6], nItems[6]);
	printf ("[8] \t Valyrian Steel \t \t \t \t %i\t\t\t%i\n", nPrices[7], nItems[7]);	
	
}

/* 
	This function simply displays the current specifications of the game
	@param nDayCounter is the current amount of days left
	@param fGD is the number of golden dragons
	@param fDebt is the amount of debt
	@param fSavings is the amount of savings
	@param nCurrCap is the current capacity
	@param nMaxCap is the amount of maximum capacity

*/
void displaySpecifications (int nDayCounter, float fGD, float fDebt, float fSavings, int nCurrCap, int nMaxCap)
{
	// Print specifics
	printf ("Days Remaining: \t %i Days \n", nDayCounter);
	printf ("GD: \t\t\t %.2f \n", fGD);
	printf ("Debt: \t\t\t %.2f \nSavings: \t\t %.2f \n", fDebt, fSavings);
	printf ("Capacity: \t\t %i / %i \n\n", nCurrCap ,nMaxCap);	
	
}


/*
	This function displays the amount of goods and the amount currently owned.
	Precondition: Items in array must be in order of the order of the specific items
	@param nItems[8] is the array of the number of goods.
*/
void displayGoods (int nItems[8])
{
	// Print item names and quantities
	printf ("ITEM\t WARES AND GOODS\t \t \t     Quantity\n");
	printf ("[1] \t Sweet Beet \t \t \t \t \t %i\n", nItems[0]);
	printf ("[2] \t Timber \t \t \t \t \t %i\n", nItems[1]);
	printf ("[3] \t Intricate Lace \t \t \t \t %i\n", nItems[2]);
	printf ("[4] \t Intoxicating Perfume \t \t \t \t %i\n", nItems[3]);
	printf ("[5] \t Pale Amber Wine \t \t \t \t %i\n", nItems[4]);
	printf ("[6] \t Myrish Eye \t \t \t \t \t %i\n", nItems[5]);
	printf ("[7] \t Qohorik Tapestry \t \t \t \t %i\n", nItems[6]);
	printf ("[8] \t Valyrian Steel \t \t \t \t %i\n", nItems[7]);
}

/*
	This function calculates how much interest is added and adds it to the money
	Precondition: Interest rate must be in decimal form. Both parameters must also be positive
	@param fInterestRate is the interest rate of the GDs shown
	@param fGD is the amount of GDs that are to be added with interest
	@return fGD is the amount of GDs with added interest
*/
float addInterest (float fInterestRate, float fGD)
{
	float fInterest;
	
	// Calculate for the interest
	fInterest = fInterestRate * fGD;
	
	// Add the interest to the amount of money
	fGD += fInterest;
	
	// Return the money with interest
	return fGD;
}

/*
	This function simply places random prices into the array depending on the trading partner
	Precondition: Prices must be in order of the order of goods
	@param nCurrLoc is the current location or partner
	@param nPrices is the array of prices
*/
void listPrices (int nCurrLoc, int nPrices[8])
{
	// Making random prices depending on the current trading partner
	if (nCurrLoc == 1)
	{
		//Input random prices
		nPrices[0] = getRandomNumber(180, 200);
		nPrices[1] = getRandomNumber(200, 250);
		nPrices[2] = getRandomNumber(380, 400);
		nPrices[3] = getRandomNumber(480, 500);
		nPrices[4] = getRandomNumber(580, 600);
		nPrices[5] = getRandomNumber(680, 700);
		nPrices[6] = getRandomNumber(780, 800);
		nPrices[7] = getRandomNumber(880, 900);
	}
	else if (nCurrLoc == 2)
	{
		// Input random prices
		nPrices[0] = getRandomNumber(180, 200);
		nPrices[1] = getRandomNumber(280, 300);
		nPrices[2] = getRandomNumber(380, 400);
		nPrices[3] = getRandomNumber(400, 450);
		nPrices[4] = getRandomNumber(580, 600);
		nPrices[5] = getRandomNumber(680, 700);
		nPrices[6] = getRandomNumber(780, 800);
		nPrices[7] = getRandomNumber(880, 900);
	}
	
	else if (nCurrLoc == 3)
	{
		nPrices[0] = getRandomNumber(180, 200);
		nPrices[1] = getRandomNumber(280, 300);
		nPrices[2] = getRandomNumber(300, 350);
		nPrices[3] = getRandomNumber(480, 500);
		nPrices[4] = getRandomNumber(580, 600);
		nPrices[5] = getRandomNumber(600, 650);
		nPrices[6] = getRandomNumber(780, 800);
		nPrices[7] = getRandomNumber(880, 900);
	}
	
	else if (nCurrLoc == 4)
	{
		//Input random prices
		nPrices[0] = getRandomNumber(180, 200);
		nPrices[1] = getRandomNumber(280, 300);
		nPrices[2] = getRandomNumber(380, 400);
		nPrices[3] = getRandomNumber(480, 500);
		nPrices[4] = getRandomNumber(500, 550);
		nPrices[5] = getRandomNumber(680, 700);
		nPrices[6] = getRandomNumber(780, 800);
		nPrices[7] = getRandomNumber(880, 900);
	}
	
	else if (nCurrLoc == 5)
	{
		//Input random prices
		nPrices[0] = getRandomNumber(180, 200);
		nPrices[1] = getRandomNumber(280, 300);
		nPrices[2] = getRandomNumber(380, 400);
		nPrices[3] = getRandomNumber(480, 500);
		nPrices[4] = getRandomNumber(580, 600);
		nPrices[5] = getRandomNumber(680, 700);
		nPrices[6] = getRandomNumber(700, 750);
		nPrices[7] = getRandomNumber(800, 850);
	}
	
	else if (nCurrLoc == 6)
	{
		//Input random prices
		nPrices[0] = getRandomNumber(100, 150);
		nPrices[1] = getRandomNumber(280, 300);
		nPrices[2] = getRandomNumber(380, 400);
		nPrices[3] = getRandomNumber(480, 500);
		nPrices[4] = getRandomNumber(580, 600);
		nPrices[5] = getRandomNumber(680, 700);
		nPrices[6] = getRandomNumber(780, 800);
		nPrices[7] = getRandomNumber(880, 900);
	}
	
}

/*
	This function simply prints the current trading partner
	@param nCurrLoc is the current location or partner
*/
void printPartner (int nCurrLoc)
{
	// Print big fancy letters according to the trading partner
	if (nCurrLoc == 1)
		printf(" __      __.__        __                 _____      .__  .__   \n/  \\    /  \\__| _____/  |_  ____________/ ____\\____ |  | |  |  \n\\   \\/\\/   /  |/    \\   __\\/ __ \\_  __ \\   __\\/ __ \\|  | |  |  \n \\        /|  |   |  \\  | \\  ___/|  | \\/|  | \\  ___/|  |_|  |__\n  \\__/\\  / |__|___|  /__|  \\___  >__|   |__|  \\___  >____/____/\n       \\/          \\/          \\/                 \\/           \n\n");
	else if (nCurrLoc == 2)
		printf(".____                   \n|    |    ___.__. ______\n|    |   <   |  |/  ___/\n|    |___ \\___  |\\___ \\ \n|_______ \\/ ____/____  >\n        \\/\\/         \\/ \n\n");
	else if (nCurrLoc == 3)
		printf("  __  __            \n |  \\/  |           \n | \\  / |_   _ _ __ \n | |\\/| | | | | '__|\n | |  | | |_| | |   \n |_|  |_|\\__, |_|   \n          __/ |     \n         |___/      \n\n");
	else if (nCurrLoc == 4)
		printf("  _____           _            \n |  __ \\         | |           \n | |__) |__ _ __ | |_ ___  ___ \n |  ___/ _ \\ '_ \\| __/ _ \\/ __|\n | |  |  __/ | | | || (_) \\__ \\\n |_|   \\___|_| |_|\\__\\___/|___/\n\n\n");
	else if (nCurrLoc == 5)
		printf("   ____        _                \n  / __ \\      | |               \n | |  | | ___ | |__   ___  _ __ \n | |  | |/ _ \\| '_ \\ / _ \\| '__|\n | |__| | (_) | | | | (_) | |   \n  \\___\\_\\\\___/|_| |_|\\___/|_|   \n\n\n");
	else if (nCurrLoc == 6)
		printf(" __      __   _       _              _     \n \\ \\    / /  | |     | |            (_)    \n  \\ \\  / /__ | | __ _| |_ __ _ _ __  _ ___ \n   \\ \\/ / _ \\| |/ _` | __/ _` | '_ \\| / __|\n    \\  / (_) | | (_| | || (_| | | | | \\__ \\\n     \\/ \\___/|_|\\__,_|\\__\\__,_|_| |_|_|___/\n\n\n");
}



/*
	This function simulates the user buying items
	Precondition: Prices must be in order of the order of goods
	@param *fGD is the pointer for the amount of Golden Dragons the user has currently
	@param nMaxCap is the maximum capacity of the wheelhouse
	@param *nCurrCap is the pointer for the current capacity of the wheelhouse
	@param nPrices is the array for the prices of the items
	@param nItems is the array for the number of items owned
*/
void actionBuy (float *fGD, int nMaxCap, int *nCurrCap, int nPrices[8], int nItems[8])
{
	// Initialize variable to be used
	int nItemQuant, nItem;
	char cKeyPressed;
	
	// Get item number
	nItem = 1;
	cKeyPressed = '0';
	while (cKeyPressed != 13)
	{
		system("cls");
		
		// Print letters and lines
		printf("________________________ \n__________              \n\\______   \\__ __ ___.__.\n |    |  _/  |  <   |  |\n |    |   \\  |  /\\___  |\n |______  /____/ / ____|\n        \\/       \\/     \n________________________ \n\n");
		printf("Current GDs: %.2f\n", *fGD);
		printf ("ITEM\t   WARES AND GOODS\t \t \t SELLING/BUYING PRICE\t  Quantity Owned\n");
		
		// Print items with less than (<), greater than (>), and equal (=) signs to indicate choice
		if (nItem == 1)
			printf ("[1] \t =>Sweet Beet<=\t \t \t \t \t %i\t\t\t%i\n", nPrices[0], nItems[0]);
		else
			printf ("[1] \t   Sweet Beet  \t \t \t \t \t %i\t\t\t%i\n", nPrices[0], nItems[0]);
			
		if (nItem == 2)
			printf ("[2] \t =>Timber<=\t \t \t \t \t %i\t\t\t%i\n", nPrices[1], nItems[1]);
		else
			printf ("[2] \t   Timber  \t \t \t \t \t %i\t\t\t%i\n", nPrices[1], nItems[1]);
			
		if (nItem == 3)
			printf ("[3] \t =>Intricate Lace<=\t \t \t \t %i\t\t\t%i\n", nPrices[2], nItems[2]);
		else
			printf ("[3] \t   Intricate Lace  \t \t \t \t %i\t\t\t%i\n", nPrices[2], nItems[2]);
			
		if (nItem == 4)
			printf ("[4] \t =>Intoxicating Perfume<=\t \t \t %i\t\t\t%i\n", nPrices[3], nItems[3]);
		else
			printf ("[4] \t   Intoxicating Perfume  \t \t \t %i\t\t\t%i\n", nPrices[3], nItems[3]);
		
		if (nItem == 5)
			printf ("[5] \t =>Pale Amber Wine<=\t \t \t \t %i\t\t\t%i\n", nPrices[4], nItems[4]);
		else
			printf ("[5] \t   Pale Amber Wine  \t \t \t \t %i\t\t\t%i\n", nPrices[4], nItems[4]);
		
		if (nItem == 6)
			printf ("[6] \t =>Myrish Eye<=\t \t \t \t \t %i\t\t\t%i\n", nPrices[5], nItems[5]);
		else
			printf ("[6] \t   Myrish Eye  \t \t \t \t \t %i\t\t\t%i\n", nPrices[5], nItems[5]);
		
		if (nItem == 7)
			printf ("[7] \t =>Qohorik Tapestry<=\t \t \t \t %i\t\t\t%i\n", nPrices[6], nItems[6]);
		else
			printf ("[7] \t   Qohorik Tapestry  \t \t \t \t %i\t\t\t%i\n", nPrices[6], nItems[6]);
		
		if (nItem == 8)
			printf ("[8] \t =>Valyrian Steel<=\t \t \t \t %i\t\t\t%i\n", nPrices[7], nItems[7]);
		else
			printf ("[8] \t   Valyrian Steel  \t \t \t \t %i\t\t\t%i\n", nPrices[7], nItems[7]);
			
		
		// Let user navigate through the choices using arrow keys but not let them out of bounds
		cKeyPressed = getch();
		if(cKeyPressed == 72 && nItem != 1)
			nItem--;
		else if (cKeyPressed == 80 && nItem != 8)
			nItem++;
	}
	
	// Let user know he isn't able buy any of the item he wants
	if (*fGD < nPrices[nItem - 1])
	{
		printf("You are unable to buy any quantities of this item with your current GD.\n");
	}
	else
	{
		// Get the quantity of the items
		printf("Specify the quantity through the use of up and down buttons.\n");
		nItemQuant = 1;
		cKeyPressed = '0';
		while (cKeyPressed != 13)
		{
			// Go back
			if (nItemQuant < 10)
				printf("\b");
			else if (nItemQuant < 100)
				printf("\b\b");
			else if (nItemQuant < 1000)
				printf("\b\b\b");
			
			printf("%i", nItemQuant);
				
			// Let user navigate through the choices using arrow keys but not let them out of bounds
			cKeyPressed = getch();
			if (cKeyPressed == 72 && (nItemQuant + 1) * nPrices[nItem - 1] <= *fGD && nItemQuant <= nMaxCap - *nCurrCap)
				nItemQuant++;
			else if (cKeyPressed == 80 && nItemQuant != 1)
				nItemQuant--;
		}
		
		// Deducting from current balance
		*fGD -= nPrices[nItem - 1] * nItemQuant;	

		// Including it in capacity
		*nCurrCap += nItemQuant;
	
		// Adding amount of items into the array
		nItems[nItem - 1] += nItemQuant;
	
		// Printing to note transaction has been completed
		printf ("\n--------TRANSACTION COMPLETE--------\n\n");
	}
	// Clear screen in a bit
	Sleep(2000);
	system("cls");

	
}

/*
	This function simulates the user selling items
	Precondition: Prices must be in order of the order of goods
	@param *fGD is the pointer for the amount of Golden Dragons the user has currently
	@param *nCurrCap is the pointer for the current capacity of the wheelhouse
	@param nPrices is the array for the prices of the items
	@param nItems is the array for the number of items owned
*/
void actionSell (float *fGD, int *nCurrCap, int nPrices[8], int nItems[8])
{
	// Initialize variable to be used
	int nItemQuant, nItem;
	char cKeyPressed;
	
	// Get item number
	nItem = 1;
	cKeyPressed = '0';
	while (cKeyPressed != 13)
	{
		system("cls");
		
		// Print letters and lines
		printf("  _________      .__  .__   \n /   _____/ ____ |  | |  |  \n \\_____  \\_/ __ \\|  | |  |  \n /        \\  ___/|  |_|  |__\n/_______  /\\___  >____/____/\n        \\/     \\/           \n\n");
		printf("Current GDs: %.2f\n", *fGD);
		printf ("ITEM\t   WARES AND GOODS\t \t \t SELLING/BUYING PRICE\t  Quantity Owned\n");
		
		// Print items with less than (<), greater than (>), and equal (=) signs to indicate choice
		if (nItem == 1)
			printf ("[1] \t =>Sweet Beet<=\t \t \t \t \t %i\t\t\t%i\n", nPrices[0], nItems[0]);
		else
			printf ("[1] \t   Sweet Beet  \t \t \t \t \t %i\t\t\t%i\n", nPrices[0], nItems[0]);
			
		if (nItem == 2)
			printf ("[2] \t =>Timber<=\t \t \t \t \t %i\t\t\t%i\n", nPrices[1], nItems[1]);
		else
			printf ("[2] \t   Timber  \t \t \t \t \t %i\t\t\t%i\n", nPrices[1], nItems[1]);
			
		if (nItem == 3)
			printf ("[3] \t =>Intricate Lace<=\t \t \t \t %i\t\t\t%i\n", nPrices[2], nItems[2]);
		else
			printf ("[3] \t   Intricate Lace  \t \t \t \t %i\t\t\t%i\n", nPrices[2], nItems[2]);
			
		if (nItem == 4)
			printf ("[4] \t =>Intoxicating Perfume<=\t \t \t %i\t\t\t%i\n", nPrices[3], nItems[3]);
		else
			printf ("[4] \t   Intoxicating Perfume  \t \t \t %i\t\t\t%i\n", nPrices[3], nItems[3]);
		
		if (nItem == 5)
			printf ("[5] \t =>Pale Amber Wine<=\t \t \t \t %i\t\t\t%i\n", nPrices[4], nItems[4]);
		else
			printf ("[5] \t   Pale Amber Wine  \t \t \t \t %i\t\t\t%i\n", nPrices[4], nItems[4]);
		
		if (nItem == 6)
			printf ("[6] \t =>Myrish Eye<=\t \t \t \t \t %i\t\t\t%i\n", nPrices[5], nItems[5]);
		else
			printf ("[6] \t   Myrish Eye  \t \t \t \t \t %i\t\t\t%i\n", nPrices[5], nItems[5]);
		
		if (nItem == 7)
			printf ("[7] \t =>Qohorik Tapestry<=\t \t \t \t %i\t\t\t%i\n", nPrices[6], nItems[6]);
		else
			printf ("[7] \t   Qohorik Tapestry  \t \t \t \t %i\t\t\t%i\n", nPrices[6], nItems[6]);
		
		if (nItem == 8)
			printf ("[8] \t =>Valyrian Steel<=\t \t \t \t %i\t\t\t%i\n", nPrices[7], nItems[7]);
		else
			printf ("[8] \t   Valyrian Steel  \t \t \t \t %i\t\t\t%i\n", nPrices[7], nItems[7]);
			
		
		// Let user navigate through the choices using arrow keys but not let them out of bounds
		cKeyPressed = getch();
		if(cKeyPressed == 72 && nItem != 1)
			nItem--;
		else if (cKeyPressed == 80 && nItem != 8)
			nItem++;
	}
	
	// Letting user know he can't sell any of the item because he has none
	if (nItems[nItem - 1] == 0)
	{
		printf("You have none of the item in your wheelhouse.\n");
	}
	else
	{
		// Get the quantity of the items
		printf("Specify the quantity through the use of up and down buttons.\n");
		nItemQuant = 1;
		cKeyPressed = '0';
		while (cKeyPressed != 13)
		{
			// Go back
			if (nItemQuant < 10)
				printf("\b");
			else if (nItemQuant < 100)
				printf("\b\b");
			else if (nItemQuant < 1000)
				printf("\b\b\b");
			
			printf("%i", nItemQuant);
				
			// Let user navigate through the choices using arrow keys but not let them out of bounds
			cKeyPressed = getch();
			if (cKeyPressed == 72 && nItemQuant < nItems[nItem - 1])
				nItemQuant++;
			else if (cKeyPressed == 80 && nItemQuant != 1)
				nItemQuant--;
		}
		
		// Adding to current balance
		*fGD += nPrices[nItem - 1] * nItemQuant;
		
		// Removing from capacity
		*nCurrCap -= nItemQuant;
	
		// Deducting the amount of items into the array
		nItems[nItem - 1] -= nItemQuant;
	
		// Printing to note transaction has been completed
		printf ("\n--------TRANSACTION COMPLETE--------\n\n");
	}
	
	// Clear screen in a bit
	Sleep(2000);
	system("cls");
	
}

/*
	This function simulates the user using the bank
	Precondition: nItems must be in order of the order of goods
	@param *fGD is the pointer is the amount of Golden Dragons the user has currently
	@param *fSavings is the pointer is the savings the user saved in the bank
	@param *fDebt is the pointer is the debt the user owes to the bank
	@param *nDayCounter is the pointer for the counter of days remaining
	@param *nCurrCap is the pointer for the current capacity of the wheelhouse
	@param *nMaxCap is the pointer for the maximum capacity of the wheelhouse
	@param *CurrLoc is the pointer for the current trading partner
	@param nItems is the array of the amount of items currently owned
*/
void actionBank (float *fGD, float *fSavings, float *fDebt, int *nDayCounter, int *nCurrCap, int *nMaxCap, int *nCurrLoc, int nItems[8])
{
	int nChoice;
	char cKeyPressed;
	float fDep, fSav, fLoan, fPayBack;
	
	
	nChoice = 1;
	cKeyPressed = '0';	
	while (cKeyPressed != 13)
	{
		system("cls");
		
		// Print fancy big letters
		printf ("__________                __    \n\\______   \\_____    ____ |  | __\n |    |  _/\\__  \\  /    \\|  |/ /\n |    |   \\ / __ \\|   |  \\    < \n |______  /(____  /___|  /__|_ \\\n        \\/      \\/     \\/     \\/\n");		
		printf("Current GDs: %.2f\n Current Savings: %.2f\n Current Debt: %.2f\n\n", *fGD, *fSavings, *fDebt);
		
		// Print items with less than (<) and greater than (>) signs to indicate choice
		if (nChoice == 1)
			printf("\t>Deposit<\n");
		else
			printf("\t Deposit\n");
		
		if (nChoice == 2)
			printf("\t>Withdraw<\n");
		else
			printf("\t Withdraw\n");
			
		if (nChoice == 3)
			printf("\t>Get a Loan<\n");
		else
			printf("\t Get a Loan\n");
		
		if (nChoice == 4)
			printf("\t>Pay Back Debt<\n");
		else
			printf(" \t Pay Back Debt\n");
			
		if (nChoice == 5)
			printf("\t>Go Back<\n");
		else
			printf("\t Go Back\n");
			
		if (nChoice == 6)
			printf("\t>Quit<\n\n");
		else
			printf("\t Quit\n\n");
			
		cKeyPressed = getch();
		
		// Let user navigate through the choices using arrow keys but not let them out of bounds
		if(cKeyPressed == 72 && nChoice != 1)
			nChoice--;
		else if (cKeyPressed == 80 && nChoice != 7)
			nChoice++;
				
	}
	
	// Change 6 to 9 to let user quit
	if (nChoice == 6)
		nChoice = 9;
		
	// User chooses to deposit
	if (nChoice == 1)
	{
		// Indicate that the user chose to deposit
		printf ("_______________\nDeposit\n_______________\n\n");
		
		// Ask for amount to be deposited
		printf ("How much GDs would you like to deposit into the bank?\n");
		scanf (" %f", &fDep);
		
		// Transacting
		if (*fGD < fDep)
			printf ("Exiting transaction do to not enough GD\n\n");
		else
		{
			// Add savings from GD
			*fGD -= fDep;
			*fSavings += fDep;
		}
	}
	if (nChoice == 2)
	{
		// Indicate that the user chose to withdraw
		printf ("_______________\nWithdraw\n_______________\n\n");
		
		// Ask for amount to be withdrawn
		printf ("How much GDs would you like to withdraw from your savings?\n");
		scanf (" %f", &fSav);
		
		// Transacting
		if (fSav > *fSavings)
			printf ("Exiting transaction do to not enough savings\n\n");
		else
		{
			// Add GD from savings
			*fGD += fSav;
			*fSavings -= fSav;
		}
	}
	
	if (nChoice == 3)
	{
		// Indicate that the user chose to get a loan
		printf ("_______________\nLoan\n_______________\n\n");
		
		// Ask for amount to be lent
		printf ("How much GDs would you like to loan?\n");
		scanf (" %f", &fLoan);
		
		// Loan
		*fGD += fLoan;
		*fDebt += fLoan;
	}
	
	if (nChoice == 4)
	{
		// Indicate that the user chose to pay back debt
		printf ("_______________\nPay Back Debt\n_______________\n\n");
		
		// Ask for amount to be paid back
		printf ("How much GDs would you like to pay back?\n");
		scanf (" %f", &fPayBack);
		
		// Paying back
		if (fPayBack > *fDebt)
			printf ("Paying too much back. Please try again later.\n\n");
		else if (fPayBack > *fGD)
			printf ("Current amount of GDs too few to pay back.\n");
		else
		{
			// Giving back GD to bank to settle loan
			*fGD -= fPayBack;
			*fDebt -= fPayBack;
		}
		
	}
	
	// If User quits
	if (nChoice == 9)		
		// To end the do while loop
		*nCurrLoc = 9;
	else
	{
		// Clear screen in a bit
		Sleep(1000);
		system("cls");
	}
	
}

/*
	This function manipulates some variables in preparation of the repetition in the loop in order to simulate wheelhouse using loops and not using break function
	Precondition: Prices must be in order of the order of goods
	@param *nDayCounter is the pointer for the counter for the days remaining
	@param *nMaxCap is the pointer for the maximum capacity of the wheelhouse
	@param *nCurrLoc is the pointer for the current trading partner
	@param *fSavings is the pointer for the amount of savings in the bank
	@param *fDebt is the pointer for the amount of savings
	@param *fGD is the pointer for the amount of GDs
	@param nPrices is the array of the prices of goods
*/
void actionWheelhouse (int *nDayCounter, int *nMaxCap, int *nCurrLoc, float *fSavings, float *fDebt, float *fGD, int nPrices[8])
{
	// Initialize variables
	int nUp, nCurrLoc2;
	char cUpChoice, cLocChoice;
	
	// Clear screen
	system("cls");
	
	// Print big fancy letters
	printf (" __      __.__                  .__  .__                                \n/  \\    /  \\  |__   ____   ____ |  | |  |__   ____  __ __  ______ ____  \n\\   \\/\\/   /  |  \\_/ __ \\_/ __ \\|  | |  |  \\ /  _ \\|  |  \\/  ___// __ \\ \n \\        /|   Y  \\  ___/\\  ___/|  |_|   Y  (  <_> )  |  /\\___ \\\\  ___/ \n  \\__/\\  / |___|  /\\___  >\\___  >____/___|  /\\____/|____//____  >\\___  >\n       \\/       \\/     \\/     \\/          \\/                  \\/     \\/ \n\n");
	
	
	// Lower the amount of days
	*nDayCounter -= 1;
	
	// Getting 10% of chance to upgrade the wheelhouse
	nUp = getRandomNumber(1,100);
	
	if (nUp >= 1 && nUp <= 10)
	{
		printf ("Would you like to upgrade the wheelhouse for 200 GDs (y/n)?");
		scanf (" %c", &cUpChoice);
		
		if (cUpChoice == 'y' || cUpChoice == 'Y')
		{
			*nMaxCap += 50;
			*fGD -= 200;
		}
	}

	// For checking if the user chose another partner
	nCurrLoc2 = *nCurrLoc;
	
	while (nCurrLoc2 == *nCurrLoc)
	{					
		*nCurrLoc = chooseTradingPartners();
		
		// If user still chose the same partner from where they came from
		if (*nCurrLoc == nCurrLoc2)
		{
			// Making sure that the user wanted to go back or not
			printf("Are you sure you want to go back to the same trading partner (y/n)? You will not lose a day if you do this\n");
			scanf(" %c", &cLocChoice);
			
			if (cLocChoice == 'y' || cLocChoice == 'Y')
			{
				// Giving back the day lost earlier
				(*nDayCounter)++;
				
				// Making sure to let the player go
				nCurrLoc2 = 0;
			}
		}
		else
		{
			// Interest for savings and debt
			*fSavings = addInterest (0.1, *fSavings);
			*fDebt = addInterest (0.05, *fDebt);
			
			// List new sets of prices for the new trading partner
			listPrices (*nCurrLoc, nPrices);
		}
	}
}

/*
	This function displays the action screen and returns the choice the user made
	Precondition: Prices must be in order of the order of goods
	@param fGD is the amount of Golden Dragons the user has currently
	@param fSavings is the savings the user saved in the bank
	@param fDebt is the debt the user owes to the bank
	@param nDayCounter is the counter of days remaining
	@param nCurrCap is the current capacity of the wheelhouse
	@param nMaxCap is the maximum capacity of the wheelhouse
	@param nCurrLoc is the current trading partner
	@param nItems is the array of the amount of items currently owned
	@param nPrices is the array of the prices of each item
*/
int displayAndGetAction (float fGD, float fSavings, float fDebt, int nDayCounter, int nCurrCap, int nMaxCap, int nCurrLoc, int nItems[8], int nPrices[8])
{
	char cChoice, cKeyPressed;
	
	// Clear input
	fflush(stdin);
		
	cKeyPressed = '0';
	cChoice = 1;
	
	while (cKeyPressed != 13)
	{
		system("cls");
		
		// Display the partner
		printPartner(nCurrLoc);
		
		// Display prices and current quantities of goods owned
		printf("__________________________________________________________________________________________\n\n");
		displayGoodsPricesAndQuant(nPrices, nItems);				
		printf("__________________________________________________________________________________________\n\n");
		
		// Display current specifications
		displaySpecifications(nDayCounter, fGD, fDebt, fSavings, nCurrCap, nMaxCap);
		
		// Print choices
		if (cChoice == 1)
			printf(">Buy<      ");
		else
			printf(" Buy       ");
		
		if (cChoice == 2)
			printf(">Sell<        ");
		else
			printf(" Sell         ");
		
		if (cChoice == 3)
			printf(">Wheelhouse<     ");
		else
			printf(" Wheelhouse      ");
		
		if (cChoice == 4)
			printf(">Iron Bank<      ");
		else
			printf(" Iron Bank       ");
		
		if (cChoice == 5)
			printf(">Quit<\n");
		else
			printf(" Quit \n");
			
		cKeyPressed = getch();

		// Ask for the input for the trading partners and exit choices
		if(cKeyPressed == 75 && cChoice != 1)
			cChoice--;
		else if (cKeyPressed == 77 && cChoice != 5)
			cChoice++;
		
	}
	
	// Change 5 to Q for quit and other numbers for actions
	if (cChoice == 1)
		cChoice = 'B';
	else if (cChoice == 2)
		cChoice = 'S';
	else if (cChoice == 3)
		cChoice = 'W';
	else if (cChoice == 4)
		cChoice = 'I';
	else if (cChoice == 5)
		cChoice = 'Q';
	
	// Return variable to be used in the main function
	return cChoice;	
}

/*
	This function utilizes a csv file for keeping track of the high scores and calculates the user's score
	@param cName is the user's name
	@param fGD is the amount of Golden Dragons the user has currently
	@param fSavings is the savings the user saved in the bank
	@param fDebt is the debt the user owes to the bank
*/
void displayHighScore(char cName[20], float fGD, float fSavings, float fDebt)
{
	//Initialize variables
	float fScore, fFileHighScore[5], fCurrHighScore[5];
	FILE *fileHighScore;
	char cFileNames[5][21], cScores[5][20], cCurrName[5][21];
	int nCount, nFound, nFileNum = 0;
	
	// Calculate the score
	fScore = fGD + fSavings - fDebt;
	
	// Opens the file for reading without overwriting
	fileHighScore = fopen ("High Scores.csv", "r+");
	
	// Read 5 times from csv file
	for (nCount = 0; nCount < 5; nCount++)
	{
		if(fscanf (fileHighScore, " %[^,]%*c", cFileNames[nCount]) != EOF && fscanf (fileHighScore, " %[^,]%*c", cScores[nCount]) != EOF)
		{
			// Change to float
			fFileHighScore[nCount] = atof(cScores[nCount]);
			
			// Add number of names and high scores
			nFileNum++;
		}
	}
		
	// Close the .txt file
	fclose(fileHighScore);
	
	// Finding user's rank and updating it to the array of high scorers
	nFound = nCount = 0;
	while (nCount < nFileNum && !nFound)
	{
		if (fScore > fFileHighScore[nCount])
		{
			fCurrHighScore[nCount] = fScore;
			strcpy(cCurrName[nCount], cName);
			printf("Congratulations! %s, you are the new top %d.\n\n", cName, nCount + 1);
			nFileNum++;
			nFound = 1;
		}
		else
		{
			fCurrHighScore[nCount] = fFileHighScore[nCount];
			strcpy(cCurrName[nCount], cFileNames[nCount]);
		}
		nCount++;
	}
	
	if (!nFound)
	{
		if (nFileNum < 5)
		{
			fCurrHighScore[nCount] = fScore;
			strcpy (cCurrName[nCount], cName);
			printf("Congratulations! %s, you are the new top %d.\n\n", cName, nCount + 1);
			nFileNum++;
		}
		
	}
	else
	{
		while (nCount < nFileNum + 1 && nCount < 5)
		{
			fCurrHighScore[nCount] = fFileHighScore[nCount - 1];
			strcpy(cCurrName[nCount], cFileNames[nCount - 1]);
			nCount++;
		}
	}
	
	// Write new file or overwrite existing file
	fileHighScore = fopen ("High Scores.csv", "w+");
	
	// Print high scores and names to file for future references
	for (nCount = 0; nCount < 5 && nCount < nFileNum; nCount++)
	{
		fprintf(fileHighScore ,"%s,%f,", cCurrName[nCount], fCurrHighScore[nCount]);
	}
	
	fclose(fileHighScore);
}

/*
	This function displays the current high scores inside the csv file
*/
void displayCurrentHighScores(void)
{
	// Initialize variables
	FILE *fileHighScore;
	float fFileHighScore[5];
	char cFileNames[5][20], cScores[5][20];
	int nCount, nFileNum = 0;
	
	// Opens the file for reading without overwriting
	fileHighScore = fopen ("High Scores.csv", "r+");
	
	// Read from csv file five times
	for (nCount = 0; nCount < 5; nCount++)
	{
		if(fscanf (fileHighScore, " %[^,]%*c", cFileNames[nCount]) != EOF && fscanf (fileHighScore, " %[^,]%*c", cScores[nCount]) != EOF)
		{
			// Change to float
			fFileHighScore[nCount] = atof(cScores[nCount]);
			
			// Add number of names and high scores
			nFileNum++;
		}
	}
	
	// Close the .csv file
	fclose(fileHighScore);
	
	// Print a list of high scorers if there are
	if (nFileNum)
		printf("|TOP| \t NAME\t\t\t\t| SCORE       |\n");
	for (nCount = 0; nCount < nFileNum; nCount++)
	{
		if (strlen(cFileNames[nCount]) <= 5)
			printf("| %i |\t %s \t\t\t\t| %f |\n", nCount + 1, cFileNames[nCount], fFileHighScore[nCount]);
		else if (strlen(cFileNames[nCount]) <= 13)
			printf("| %i |\t %s \t\t\t| %f |\n", nCount + 1, cFileNames[nCount], fFileHighScore[nCount]);
		else if (strlen(cFileNames[nCount]) <= 19)
			printf("| %i |\t %s \t\t| %f |\n", nCount + 1, cFileNames[nCount], fFileHighScore[nCount]);
	}
	printf("\n\n");
}
