#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoices{Stone = 1 , Paper = 2 , Scissors = 3};
enum enWinner{ Player = 1 , Computer = 2 , Draw = 3};

struct stRoundInfo
{
	short Round = 0;
	enGameChoices PlayerChoice;
	enGameChoices ComputerChoice;
	enWinner RoundWinner;
	string RoundWinnerName = "";
	 
};
struct stGameResult
{
	short Rounds = 0;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner; 
	string GameWinnerName = "";

};
int ReadHowManyRounds()
{
	short Round = 0;
	do
	{
		cout << "\a";
		cout << " enter how many round from 1/10 ?! : ";
		cin >> Round;
		cout << endl;

	} while (Round < 1 || Round > 10);
	return Round;
}
enGameChoices ReadPlayerChoice()
{
	short PlayerChoice = 0;
	do
	{
		cout << " enter your Choice : [1]:Stone , [2]:Paper , [3]:Scissors ?! : ";
		cin >> PlayerChoice;
		cout << endl;

	} while (PlayerChoice < 1 || PlayerChoice > 3);
	
	return (enGameChoices)PlayerChoice;
}
int RandomNumber(short From, short To)
{
	return rand() % (To - From + 1) + From;
}
enGameChoices GetComputerChoice()
{
	return (enGameChoices)RandomNumber(1, 3);
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice)
		return enWinner::Draw;

	switch (RoundInfo.ComputerChoice)
	{
	
	case enGameChoices::Paper:
		if (RoundInfo.PlayerChoice == enGameChoices::Stone)
			return enWinner::Computer;
		break;
	case enGameChoices::Scissors:
		if (RoundInfo.PlayerChoice == enGameChoices::Paper)
			return enWinner::Computer;
		break;
	case enGameChoices::Stone:
		if (RoundInfo.PlayerChoice == enGameChoices::Scissors)
			return enWinner::Computer;
		break;
	}

	return enWinner::Player;

}
enWinner WhoWonTheGame(short Player, short Computer)
{

	if (Player > Computer)
	{
		return enWinner::Player;
	}
	else if (Computer > Player)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::Draw;
	}
}
string WinnerName(enWinner Info)
{
	string arr[3] = { " Player " , " Computer " , " No Winner " };
	return arr[Info - 1];

}
string ChoicesName(enGameChoices Choices)
{
	string arr[3]{ " Stone " , " Paper " , " Scissors " };
	return arr[Choices - 1];

}
void PrintRoundInfo(stRoundInfo Round)
{
	cout << "_________Round [" << Round.Round << "] Result_________\n\n";
	cout << " Player Choice   : " << ChoicesName(Round.PlayerChoice) << endl;
	cout << " Computer Choice : " << ChoicesName(Round.ComputerChoice) << endl;
	cout << " Round Winner    : " << Round.RoundWinnerName << endl;
	cout << "___________________________________\n\n";

}
void SetScreenColour(stRoundInfo Info)
{
	if (Info.RoundWinner == enWinner::Player)
	{
		system("color 2f");
	}
	else if (Info.RoundWinner == enWinner::Computer)
	{
		system("color 4f");
		cout << "\a";

	}
	else
	{
		system("color 6f");
	}


}
stGameResult FillRoundInfo(short Rounds, short Player, short Computer, short Draw)
{
	stGameResult GameResult;

	GameResult.Rounds = Rounds;
	GameResult.PlayerWonTimes = Player;
	GameResult.ComputerWonTimes = Computer;
	GameResult.DrawTimes = Draw;
	GameResult.GameWinner = WhoWonTheGame(Player, Computer);
	GameResult.GameWinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}
string Tabs(short Num)
{
	string Space = "";
	for (short i = 1; i <= Num; i++)
	{
		Space += "\t";
	}
	return Space;
}
void ShowGameOver()
{
	cout << Tabs(4) << "_____________________________________________\n\n";
	cout << Tabs(4) << "             ++++ GAME OVER ++++                 \n";
	cout << Tabs(4) << "_____________________________________________\n\n";
}
void printGameResult(stGameResult GameResult)
{
	cout << Tabs(4) << "_______________[Game Result ]_________________\n\n";
	cout << Tabs(4) << " Game Rounds        : " << GameResult.Rounds << endl;
	cout << Tabs(4) << " Player Won Times   : " << GameResult.PlayerWonTimes << endl;
	cout << Tabs(4) << " Computer Won Times : " << GameResult.ComputerWonTimes << endl;
	cout << Tabs(4) << " Draw Times         : " << GameResult.DrawTimes << endl;
	cout << Tabs(4) << " Game Winner        : " << GameResult.GameWinnerName << endl;
	cout << Tabs(4) << "_______________________________________________\n\n";

}
stGameResult PlayGame(short HowManyRound) 
{
	stRoundInfo RoundInfo;
	short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

	for (short Round = 1; Round <= HowManyRound; Round++)
	{
		cout << "_________Round [" << Round << "] begins_________\n\n";
		RoundInfo.Round = Round;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
		RoundInfo.RoundWinnerName = WinnerName(RoundInfo.RoundWinner);

		SetScreenColour(RoundInfo);
		PrintRoundInfo(RoundInfo);

		if (RoundInfo.RoundWinner == enWinner::Player)
		{
			PlayerWonTimes++;
		}
		else if (RoundInfo.RoundWinner == enWinner::Computer)
		{
			ComputerWonTimes++;
		}
		else
		{
			DrawTimes++;
		}


	}

	return FillRoundInfo(HowManyRound, PlayerWonTimes, ComputerWonTimes, DrawTimes);
	
}
void SetScreen()
{
	system("cls");
	system("color 0f");
}
void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		SetScreen();
		stGameResult GameInfo = PlayGame(ReadHowManyRounds());
		ShowGameOver();
		printGameResult(GameInfo);

		cout << Tabs(4) << " do you wanna play again Y/N ?! : ";
		cin >> PlayAgain;
		cout << endl << endl;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}
int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;


}
