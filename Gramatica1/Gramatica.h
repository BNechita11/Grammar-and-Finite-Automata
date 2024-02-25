#pragma once
#include<iostream>
#include<algorithm>
#include <vector>
#include<fstream>
#include<string>
#include<random>
#include<cstdlib>
#include<ctime>
#include <set>
#include<map>
#include "FiniteAutomaton.h"


class Grammar
{
public:
	Grammar();
	void ReadGrammar();
	void PrintGrammar()const;
	void GetCompatibleProducts(std::vector<int>& compatibleProducts,const std::string &start);
	void SetProduction(std::string& word, int index)const;
	std::string GenerateWord(bool showSteps);
	void GenerateNWords(bool showSteps);
	bool VerifyGrammar() const;
	bool TerminalIntersectedNonterminal() const;
	bool SInNonterminal() const;
	bool AtLeastOneNonterminal() const;
	bool AtLeastOneProductionWithS()const;
	bool VnVtElementsInProductions() const;
	bool IsRegular() const;
	bool IsTerminal(const std::string& symbol) const;
	bool IsNonterminal(const std::string& symbol) const;
	FiniteAutomaton ConvertToAutomaton() const;
	std::string getValueS() {
		return this->m_start;
	}
private:
	std::vector<std::string> m_neterminale;
	std::vector<std::string> m_terminale;
	std::string m_start;
	std::vector<std::pair<std::string, std::string>> m_productii;
	std::set<std::string> m_cuvinteGenerate;
	std::string m_lambda="~";
};

