#include "Gramatica.h"

int main()
{
	Grammar gramatica;
	gramatica.ReadGrammar();
	FiniteAutomaton automatfinit = gramatica.ConvertToAutomaton();

	int choose = 99999;
	if (!gramatica.VerifyGrammar() || !gramatica.IsRegular())
	{
		std::cout << "Gramatica incorecta sau neregulata!\n";
		return 0;
	}

	std::cout << "Gramatica este corecta si regulata!\n";
	while (choose != 0)
	{
		std::cout << "\nMENU\n";
		std::cout << "1.Afiseaza Gramatica:\n";
		std::cout << "2.Genererea de n cuvinte in Gramatica :\n";
		std::cout << "3.Obtinerea automatului echivalent si afisarea acestuia:\n";
		std::cout << "4.Verificare automaton:\n";
		std::cout << "5.Verificarea daca un cuvant este acceptat sau nu de automatul obtinut:\n";
		std::cout << "6.Generearea unui cuvant in G si verificarea daca este acceptat de automat:\n";
		std::cout << "7.Automatul este sau nu unul determinist:\n";
		std::cout << "Choose option:\n";
		std::cin >> choose;
		switch (choose)
		{
		case 1:
			gramatica.PrintGrammar();
			break;
		case 2:
			gramatica.GenerateNWords(false);
			break;
		case 3:
			automatfinit.PrintAutomaton();
			break;
		case 4:
		{
			if (automatfinit.VerifyAutomaton())
				std::cout << "Automatul este corect!\n";
			else
				std::cout << "Automatul nu este corect!\n";
		}
		break;
		case 5:
		{
			std::string word;
			std::cout << "Scrie un cuvant de la tastatura:\n";
			std::cin >> word;
			if (automatfinit.CheckWord(word) == true)
				std::cout << "Cuvantul este acceptat de catre automat\n";
			else std::cout << "Cuvantul nu este acceptat de catre automat\n"; 
		}
		break;
		case 6:
		{
			std::string word = gramatica.GenerateWord(true);
			std::cout << "Cuvantul generat este " << word << "\n";
			if (automatfinit.CheckWord(word) == true)
				std::cout << "Cuvantul este acceptat de catre automat\n";
			else std::cout << "Cuvantul nu este acceptat de catre automat\n";
		}
		break;
		case 7:
		{
			if (automatfinit.IsDeterministic())
				std::cout << "Automatul este determinist\n";
			else
				std::cout << "Automatul nu este determinist\n";
		}
		break;
		default:
			break;
		}
	}

	return 0;
}

