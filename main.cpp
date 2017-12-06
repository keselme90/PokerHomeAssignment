#include <iostream>
#include <fstream>
#include <algorithm>
#include "Hand.h"
#include "PokerHandMapping.h"


/*Function that helps to sort the cards in a vector.
*/
bool sortFunc(const Card &firstCard,const Card &secondCard) {

	return CardMapping::mymap[firstCard.getRank()] < CardMapping::mymap[secondCard.getRank()];
}

/*Checks if the given vector represents Straight Hand in poker.
*/
bool checkIfStraight(std::vector<Card> vec) {

	std::sort(vec.begin(), vec.end(), sortFunc); // Sort the vector.
	if ((CardMapping::mymap[vec[1].getRank()] - CardMapping::mymap[vec[0].getRank()]) != 1) {

		if (vec[0].getRank() == 'A' && vec[1].getRank() != 'T')// check if Ace is first <- special case.
			return false;
	}
	for (int i = 2; i < vec.size(); i++) { // Check if the cards appear in non decreasing order
		if ((CardMapping::mymap[vec[i].getRank()] - CardMapping::mymap[vec[i - 1].getRank()]) != 1)
			return false;
	}
	return true;
}

/**
* Checks if the given vector represents Flush hand in poker.
*/
bool checkIfFlush(const std::vector<Card> &vec) {

	char suit = vec[0].getSuit();// Get the frist suit
	for (std::vector<Card>::const_iterator it = vec.begin() + 1; it != vec.end(); it++) { // Check if all suits are the same.

		if (it->getSuit() != suit)
			return false;
	}

	return true;
}

/**
* Function checks the given vector and returns the Poker Hand the vector represents.
*/
std::string checkWhatPokerHandThisIs(const std::vector<Card> &hand) {

	std::map<char, int> tempMap;//Create a map to count card appearances.

	for (int i = 0; i < hand.size(); i++) //Add each card to the map.
		tempMap[hand[i].getRank()] += 1;
	
	int pair = 0;
	int triple = 0;
	int quad = 0;

	for (std::map<char, int>::iterator it = tempMap.begin(); it != tempMap.end(); it++) {// Go through the map and count how many
																						// of each combination appear ( pair, triple, quad)
		
		if (it->second == 2)
			pair++;
		else if (it->second == 3)
			triple++;
		else if (it->second == 4)
			quad++;
	}

	if (pair == 0 && triple == 0 && quad == 0) {
		bool flush = checkIfFlush(hand);
		bool straight = checkIfStraight(hand);
		if (flush && straight)
			return "Straight Flush";
		else if (flush && !straight)
			return "Flush";
		else if (!flush && straight)
			return "Straight";
		else
			return "High Card";
	}
	if (pair == 1 && triple == 0)
		return "One Pair";
	if (pair == 2)
		return "Two Pair";
	if (triple == 1 && pair == 1)
		return "Full House";
	if (triple == 1 && pair == 0)
		return "3-of-a-Kind";
	if(quad == 1)
		return "4-of-a-Kind";

}

/**
* Function returns a vector of a possible legal card sequence.
*/
std::vector<Card> createHandVariation(const int &i, const int &j, const int &n, const int &m, const int &k, Hand &hand, const std::vector<Card> &board) {

	std::vector<Card> possibleVariationVector;
	possibleVariationVector.push_back(hand.getCard(i));
	possibleVariationVector.push_back(hand.getCard(j));
	possibleVariationVector.push_back(board[n]);
	possibleVariationVector.push_back(board[m]);
	possibleVariationVector.push_back(board[k]);

	return possibleVariationVector;
}

/**
* Function calcualtes and returns the sum of the card values in a given vector.
*/
int calculateSumOfCardInHand(const std::vector<Card> &vec) {
	 
	int sum = 0;
	for (std::vector<Card>::const_iterator it = vec.begin(); it != vec.end(); it++) 
		sum += (*it).getStrength();
	
	
	return sum;
}

/**
* Functions go through all possible variation of legal card sequences and returns the best possible.
*/
std::string findBestHandForHigh(const std::vector<std::vector<Card>> &allHands, int &totalBestHandCombinationValue, int &totalPlayerCardsSumValue) {

	std::string bestHandCombinationForHigh;
	for (std::vector < std::vector<Card>>::const_iterator iter = allHands.begin(); iter != allHands.end(); iter++) {// Go through all the possible
																											// vectors

		std::string pokerHandCombination = checkWhatPokerHandThisIs(*iter);//Check what Poker Hand representation each vector have.
		int currentBestCombinationHandValue = HandMapping::handMap[pokerHandCombination];//Evaluate the Poker Hand representation
		if (currentBestCombinationHandValue > totalBestHandCombinationValue) {//Check if it's better than previous value, change it if so.
			totalPlayerCardsSumValue = calculateSumOfCardInHand(*iter);//Calculate the actual sum the cards in vector
			totalBestHandCombinationValue = currentBestCombinationHandValue;
			bestHandCombinationForHigh = pokerHandCombination;
		}
		if (currentBestCombinationHandValue == totalBestHandCombinationValue) {//If the current Poker Hand is equal to previous best Poker Hand

			int localCardsSum = calculateSumOfCardInHand(*iter);//Calculate the current cards sum.
			if (localCardsSum > totalPlayerCardsSumValue)//Check if the current card sum is better than previous best card sum.
				totalPlayerCardsSumValue = localCardsSum;//change it if so.
		}
	}
	return bestHandCombinationForHigh;
}

/**
* Checks if the given vector has a representation that qualifies for Lo rules
*/
bool checkIfQualifiedForLow(const std::vector<Card> &vec) {

	std::map<char, int> tempMap;
	bool rankingFlag = false;
	bool uniquenessFlag = false;
	for (std::vector<Card>::const_iterator it = vec.begin(); it != vec.end(); it++) {
		if (CardMapping::mymap[(*it).getRank()] > 8)
			rankingFlag = true;
		if ((tempMap[(*it).getRank()] += 1) > 1)
			uniquenessFlag = true;
	}
	if (rankingFlag == true || uniquenessFlag == true)
		return false;
	
	return true;
}

/**
* Function goes through all possible legal variants and selects those that are suitable for Lo game, and chooses the best one.
*/
int findBestHandForLow(std::vector<std::vector<Card>> &allHands) {

	int cardValue = INT_MAX;
	for (std::vector < std::vector<Card>>::iterator iter = allHands.begin(); iter != allHands.end(); iter++) {//Go through all variants
		if (checkIfQualifiedForLow(*iter)) {//Check if vector is suitable for Lo rules.																
			int i = 0;
			int localValue = 0;
			sort(iter->begin(), iter->end(), sortFunc);//Sort each vector in non decreasing order.
			for (int i = iter->size() - 1; i >= 0; i--) {//Go through the vector
				
				localValue += CardMapping::mymap[(*iter)[i].getRank()];//Calculate the numeric value of the sequence.
				localValue *= 10;
			}
			localValue /= 10;
			if (localValue < cardValue) {//Check if hte current value is better than the previous one.
				cardValue = localValue;
				
			}
		}
	}
	return cardValue;
}

/**
* Function receives two values of each player and returns who has won the game of Lo.
*/
std::string getLowWinner(const int &firstPlayerValue, const int &secondPlayerValue) {

	if (firstPlayerValue == secondPlayerValue) {
		if (firstPlayerValue == INT_MAX)
			return "No hand qualified for Low";
		else {
			std::string s = std::to_string(firstPlayerValue);
			if (s[s.length() - 1] == '1')
				s[s.length() - 1] = 'A';
			return "No hand qualified for Low" + (std::string)"(" +s + ")";
		}
	}
	else {
		if (firstPlayerValue < secondPlayerValue) {
			std::string s = std::to_string(firstPlayerValue);
			if (s[s.length() - 1] == '1')
				s[s.length() - 1] = 'A';
			return "HandA wins Lo " + (std::string)"(" + s + ")";
		}
		else {
			std::string s = std::to_string(secondPlayerValue);
			if (s[s.length() - 1] == '1')
				s[s.length() - 1] = 'A';
			return "HandB wins Lo " + (std::string)"(" + s + ")";
		}
	}
	
}

/**
* Function builds the vector of vectors for each player, that represents all possible legal combinations of card sequences.
* Then the function uses all the functions from above to see which player has a better hand.
*/
std::string findWinner(Hand &handA, Hand &handB, std::vector<Card> &board) {

	std::vector<std::vector<Card>> firstHandAllCombinations;// Matrix of combinations for player one.
	std::vector<std::vector<Card>> secondHandAllCombinations;//Matrix of combinations for player two.
	for (int i = 0; i < 4; i++) {

		for (int j = i + 1; j < 4; j++) {

			for (int n = 0; n < 3; n++) {
				
				for (int m = n + 1; m < 4; m++) {

					for (int k = m + 1; k < 5; k++) {
						
						firstHandAllCombinations.push_back(createHandVariation(i, j, n, m, k, handA, board));//Build all combinatios for player one
						secondHandAllCombinations.push_back(createHandVariation(i, j, n, m, k, handB, board));//Build all combinatins for player two
					}
				}
			}
		}
	}
	

	int firstPlayerCombinationValue = 0;
	int firstPlayerCardsSumValue = 0;
	std::string firstPlayerBestCombinationString = findBestHandForHigh(firstHandAllCombinations, firstPlayerCombinationValue, firstPlayerCardsSumValue);//Find best option for player one in Hi game.
	
	int secondPlayerCombinationValue = 0;
	int secondPlayerCardsSumValue = 0;
	std::string secondPlayerBEstCombinationString = findBestHandForHigh(secondHandAllCombinations, secondPlayerCombinationValue, secondPlayerCardsSumValue);//Find best option for player two in Hi game.
	
	int bestLowFirstHand = findBestHandForLow(firstHandAllCombinations);//Find best option for player one in Lo game.
	int bestLowSecondtHand = findBestHandForLow(secondHandAllCombinations);//Find best option for player two in Lo game.

	std::string lowWinner = getLowWinner(bestLowFirstHand, bestLowSecondtHand);//Decied who is the winner in the Lo Game.

	if (firstPlayerCombinationValue == secondPlayerCombinationValue) {//Deciedes who is the winner in the Hi Game.
		
		if (firstPlayerCardsSumValue > secondPlayerCardsSumValue)
			return "HandA wins Hi" + (std::string)" (" + firstPlayerBestCombinationString + "); " + lowWinner;
		else if (firstPlayerCardsSumValue < secondPlayerCardsSumValue)
			return "HandB wins Hi" + (std::string)" (" + secondPlayerBEstCombinationString + "); " + lowWinner;
		else
			return "Split pot Hi" + (std::string)" (" + firstPlayerBestCombinationString + "); " + lowWinner;
	}
	else
		return firstPlayerCombinationValue > secondPlayerCombinationValue ? "HandA wins Hi" + (std::string)" (" + firstPlayerBestCombinationString + "); " + lowWinner :
										  "HandB wins Hi" + (std::string)" (" + secondPlayerBEstCombinationString + "); " + lowWinner;
}

/**
* Parses the input string of the dealer and creates a vector of cards accordingly.
*/
void buildBoardCardsVector(std::vector<Card> &vec, std::string source) {

	source = source.substr(source.find(":") + 1);
	while (source.size() != 2) {

		Card card(source.substr(0, source.find("-")));
		vec.push_back(card);
		source = source.substr(source.find("-") + 1);
	}
	Card card(source);
	vec.push_back(card);
}

/**
* Receives raw input of strings, parses the input, creates the players and starts the match.
*/
std::string setUpGame(std::string firstPlayerHand, std::string secondPlayerHand, std::string dealer) {

	Hand handA(firstPlayerHand);
	Hand handB(secondPlayerHand);

	std::vector<Card> boardVector;
	buildBoardCardsVector(boardVector, dealer);//Creates vector of cards for the dealer.

	return findWinner(handA, handB, boardVector);// Returns who won in each round.
}

/**
* Receives the input from file as vector of strings, works with each string seperately
*/
void parseInput(std::vector<std::string> &input , char *&filePath) {
	
	std::vector<std::string> output;
	for (std::vector<std::string>::iterator it = input.begin(); it != input.end(); it++) {//For each string in the vector.

		std::string line = *it;

		std::string handA = line.substr(0, line.find(" "));


		line = line.substr(line.find(" ") + 1);
		std::string handB = line.substr(0, line.find(" "));


		line = line.substr(line.find(" ") + 1);

		std::string result = setUpGame(handA, handB, line);// Create a match between two players and the dealer.
		output.push_back(result);//Push the result of the match into the output vector
	}

	//When all input strings are processed
	std::ofstream outFile;
	outFile.open(filePath);
	if (outFile.is_open())//Open output file
	{
		for (int i = 0; i < input.size(); i++) {//For each string in output file.
			outFile << input[i] << "\n=> ";//Write the relevant input string to file
			outFile << output[i] << "\n";//Write the relevent output string to file.
			outFile << "\n";
		}
	}
	else
		std::cout << "Failure while openning the file" << std::endl;
	outFile.close();
	
}

int main(int argc, char *argv[]) {

	std::ifstream inputFile;
	
	std::vector<std::string> inputStrings;

	inputFile.open(argv[1]);
	if (inputFile.is_open()) {

		std::string line;
		while (getline(inputFile, line))
			inputStrings.push_back(line);
		parseInput(inputStrings, argv[2]);

	}
	else
		std::cout << "Failure while openning the file" << std::endl;

	inputFile.close();
}