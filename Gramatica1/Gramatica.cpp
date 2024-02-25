#include "Gramatica.h"

Grammar::Grammar()
{

}

void Grammar::ReadGrammar()
{
	std::ifstream fin("file.in");
	if (!fin.is_open())
	{
		throw std::exception("Fisierul nu a putut fi deschis!\n");
		return;
	}
	else
	{
		int size;
		std::string element;
		fin >> size;
		for (int i = 0; i < size; i++) {
			fin >> element;
			m_neterminale.push_back(element);
		}

		fin >> size;
		for (int i = 0; i < size; i++) {
			fin >> element;
			m_terminale.push_back(element);
		}

		fin >> size;
		for (int i = 0; i < size; i++)
		{
			fin >> element;
			m_start = element;
		}

		fin >> size;
		for (int i = 0; i < size; i++)
		{
			std::string stanga, dreapta;
			fin >> stanga >> dreapta;
			m_productii.push_back(std::make_pair(stanga, dreapta));
		}
	}
}


void Grammar::PrintGrammar() const {

	std::cout << "VN: ";
	for (const std::string& vn : m_neterminale) {
		std::cout << vn << " ";
	}
	std::cout << "\nVT: ";
	for (const std::string& vt : m_terminale) {
		std::cout << vt << " ";
	}
	std::cout << "\nS: " << m_start << "\n";

	std::cout << "Productii (P):\n{\n";
	for (const std::pair<std::string, std::string>& prod : m_productii) {
		std::cout <<"  " <<prod.first << " -> " << prod.second << "\n";
	}
	std::cout << "}\n";
}


void Grammar::GetCompatibleProducts(std::vector<int>& compatibleProducts, const std::string& word)
{
	for (int i = 0; i < m_productii.size(); i++)
	{
		if (word.find(m_productii[i].first) != std::string::npos)
		{
			compatibleProducts.push_back(i);
		}
	}
}


void Grammar::SetProduction(std::string& word, int index) const
{
	auto iterator = word.find(m_productii[index].first);
	if (m_productii[index].second != m_lambda)
		word.replace(iterator, m_productii[index].second.size(), m_productii[index].second);
	else
		word.replace(iterator, m_productii[index].second.size(), "");
}


std::string Grammar::GenerateWord(bool showSteps)
{
	std::string word = m_start;
	std::vector<int> compatibleProducts;
	GetCompatibleProducts(compatibleProducts, word);
	if (showSteps)
		std::cout << m_start;
	while (!compatibleProducts.empty())
	{
		std::random_device random;
		std::mt19937 eng(random());
		std::uniform_int_distribution<> distr(0, compatibleProducts.size() - 1);
		int index = distr(eng);
		SetProduction(word, compatibleProducts[index]);
		if (showSteps)
		{
			std::cout << "->" << word;
		}
		compatibleProducts.clear();
		GetCompatibleProducts(compatibleProducts, word);
	}

	if (showSteps == true)
	{
		std::cout << "\n";
	}

	return word;
}


void Grammar::GenerateNWords(bool showSteps)
{
	int n;
	std::cout << "Alegeti n:";
	std::cin >> n;
	while (n)
	{
		std::string word = GenerateWord(false);
		if (m_cuvinteGenerate.empty())
		{
			if (!showSteps)
				std::cout << m_start;
			m_cuvinteGenerate.insert(word);
			if (!showSteps)
				std::cout << "->" << word << "\n";
			n--;
		}
		else
		{
			if (m_cuvinteGenerate.find(word) == m_cuvinteGenerate.end())
			{
				if (!showSteps)
					std::cout << m_start;
				m_cuvinteGenerate.insert(word);
				if (!showSteps)
					std::cout << "->" << word << "\n";
				n--;
			}
		}
	}
}


bool Grammar::VerifyGrammar()const
{
	if (TerminalIntersectedNonterminal() && SInNonterminal() && AtLeastOneNonterminal() && AtLeastOneProductionWithS() && VnVtElementsInProductions())
		return true;
	else
		false;
}


bool Grammar::TerminalIntersectedNonterminal() const
{
	if (!m_neterminale.empty() && !m_terminale.empty() && !m_start.empty() && !m_productii.empty())
	{
		for (const std::string& vt : m_terminale) {
			if (IsNonterminal(vt))
			{
				std::cout << "Regula (1) nu este indeplinita. Exista intersectie intre Vn si Vt.";
				return false;
			}
		}
		for (const std::string& vn : m_neterminale)
		{
			if (IsTerminal(vn))
			{
				std::cout << "Regula (1) nu este indeplinita. Exista intersectie intre Vn si Vt.";
				return false;
			}
		}
	}
	return true;
}


bool Grammar::SInNonterminal() const
{
	if (!IsNonterminal(m_start))
	{
		std::cout << "Regula (2) nu este indeplinita. S nu este un neterminal.";
		return false;
	}
	return true;
}


bool Grammar::AtLeastOneNonterminal() const
{
	for (const std::pair<std::string, std::string>& productie : m_productii)
	{
		bool apartine = false;
		for (char c : productie.first)
		{
			if (IsNonterminal(std::string(1, c)))
			{
				apartine = true;
				break;
			}
		}
		if (!apartine)
		{
			std::cout << "Regula (3) nu este indeplinita. O regula nu contine cel putin un neterminal in membru stang .";
			return false;
		}
	}

	return true;
}


bool Grammar::AtLeastOneProductionWithS() const
{
	bool existaProductie = false;
	for (const std::pair<std::string, std::string>& productie : m_productii)
	{
		if (productie.first == m_start)
		{
			existaProductie = true;
			break;
		}
	}
	if (!existaProductie)
	{
		std::cout << "Regula (4) nu este indeplinita. Nu exista productie cu S in partea stanga.";
		return false;
	}
	return true;
}


bool Grammar::VnVtElementsInProductions() const
{
	for (const std::pair<std::string, std::string>& productie : m_productii)
	{
		bool apartineVt = false;
		bool apartineVn = false;
		for (char c : productie.second)
		{
			if (IsNonterminal(std::string(1, c)))
			{
				apartineVn = true;
			}
		}

		for (char c : productie.second)
		{
			if (IsTerminal(std::string(1, c)))
			{
				apartineVt = true;
			}
		}
		if (!apartineVn || !apartineVt)
		{
			std::cout << "Regula (5) nu este indeplinita. O productie contine un simbol invalid.";
			return false;
		}

		apartineVn = false;

		if (IsNonterminal(productie.first))
		{
			apartineVn = true;
			break;
		}
		if (!apartineVn)
		{
			std::cout << "Regula (5) nu este indeplinita. O productie contine un simbol invalid.";
			return false;
		}

	}
	return true;
}

bool Grammar::IsRegular() const
{
	for (const auto& prod : m_productii)
	{
		if (!(prod.first.size() == 1) || !(prod.second.size() <= 2))
			return false;
		if (!IsNonterminal(prod.first))
			return false;
		if (prod.second.size() == 1 && (!IsTerminal(prod.second) ))
		{
			std::cout << prod.first << "->" << prod.second << "\n";
			return false;
		}
		if (prod.second.size() == 2 && (!IsTerminal(std::string(1, prod.second[0])) || !IsNonterminal(std::string(1, prod.second[1]))))
			return false;
	}
	return true;
}

bool Grammar::IsTerminal(const std::string& symbol) const
{
	for (const auto& ter : m_terminale)
		if (ter == symbol)
		{
			return true;
		}
	return false;
}

bool Grammar::IsNonterminal(const std::string& symbol) const
{
	for (const auto& ter : m_neterminale)
		if (ter == symbol)
		{
			return true;
		}
	return false;
}

FiniteAutomaton Grammar::ConvertToAutomaton() const {
	std::set<char> states;
	std::set<char> alphabet;
	std::map<std::pair<char, char>, std::set<char>> transitions;
	char initial_state = m_start[0];
	std::set<char> final_states;
	char finalState = 'T';

	for (const auto& vn : m_neterminale) {
		states.insert(vn[0]);
	}

	for (const auto& vt : m_terminale) {
		alphabet.insert(vt[0]);
	}

	for (const auto& prod : m_productii) {
		char symbol = prod.second[0];

		transitions[{prod.first[0], symbol}].insert(prod.second.size() == 2 ? prod.second[1] : finalState);
	}
	states.insert(finalState);
	final_states.insert(finalState);

	return FiniteAutomaton(states, alphabet, transitions, initial_state, final_states);
}

