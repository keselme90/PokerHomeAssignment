#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Hand.h"

std::vector<Card> createHandVariation(const int i, const int j, const int n, const int m, const int k, Hand &hand, const std::vector<Card> &board) {

	std::vector<Card> tempVec;
	tempVec.push_back(hand.getCard(i));
	tempVec.push_back(hand.getCard(j));
	tempVec.push_back(board[n]);
	tempVec.push_back(board[m]);
	tempVec.push_back(board[k]);

	return tempVec;
}

std::string findLowWinner(Hand handA, Hand handB, std::vector<Card> board) {

	std::vector<std::vector<Card>> firstHandAllCombinations;
	std::vector<std::vector<Card>> secondHandAllCombinations;
	for (int i = 0; i < 4; i++) {

		
		for (int j = i + 1; j < 4; j++) {

			
			for (int n = 0; n < 3; n++) {
				
				
				for (int m = n + 1; m < 4; m++) {

					
					for (int k = m + 1; k < 5; k++) {
						
						/*std::vector<Card> tempVecHandA;
						tempVecHandA.push_back(handA.getCard(i));
						tempVecHandA.push_back(handA.getCard(j));
						tempVecHandA.push_back(board[n]);
						tempVecHandA.push_back(board[m]);
						tempVecHandA.push_back(board[k]);
						firstHandAllCombinations.push_back(tempVecHandA);*/
						firstHandAllCombinations.push_back(createHandVariation(i, j, m, n, k, handA, board));
						secondHandAllCombinations.push_back(createHandVariation(i, j, m, n, k, handB, board));
						/*std::vector<Card> tempVecHandB;
						tempVecHandB.push_back(handB.getCard(i));
						tempVecHandB.push_back(handB.getCard(j));
						tempVecHandB.push_back(board[n]);
						tempVecHandB.push_back(board[m]);
						tempVecHandB.push_back(board[k]);
						secondHandAllCombinations.push_back(tempVecHandA);*/
					}
				}
			}
		}
	}
	for (std::vector < std::vector<Card>>::iterator iter = firstHandAllCombinations.begin(); iter != firstHandAllCombinations.end(); iter++) {

		for (std::vector<Card>::iterator it = iter->begin(); it != iter->end(); it++)

			std::cout << it->toString() << " ";

		std::cout << std::endl;
	}
	return "Hello";
}

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

void setUpGame(std::string a, std::string b, std::string dealer) {

	
	Hand handA(a);
	Hand handB(b);

	std::vector<Card> boardVector;
	buildBoardCardsVector(boardVector, dealer);

	findLowWinner(handA, handB, boardVector);
}

void parseLine(std::string line) {
	
	std::string handA = line.substr(0,line.find(" "));
	

	line = line.substr(line.find(" ")+1);
	std::string handB = line.substr(0, line.find(" "));
	

	line = line.substr(line.find(" ") + 1);

	setUpGame(handA, handB, line);
}

int main(int argc, char *argv[]) {

	std:: ifstream inputFile;

	inputFile.open(argv[1]);
	if (inputFile.is_open()) {

		std::string line;
		while (getline(inputFile, line)) 
			parseLine(line);

		inputFile.close();
	}
	else
		std::cout << "Failure while openning the file" <<std::endl;
}