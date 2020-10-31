#include "algebra.h"

int main()
{
	std::string s;
	std::string s2;

	std::cout << "Welcome to ALGEBRA, a game for mathematicians.\n\n" << std::endl;
	std::cout << "Create or load players (command \"create\" and command \"load <file>\"): \n" << std::endl;
	std::cout << "preloader    #> ";
	std::getline(std::cin, s, '\n');

	char c[256];
	char* b;
	strcpy_s(c, s.c_str());

	b = strtok(c, " \n");
	if (b == nullptr)
	{
		std::cout << "null args" << std::endl;
		return -1;
	}

	s2 = b;
	Player* player = new Player();

	
	
	if(s2.compare("create") == 0)
	{
		player->create();
		while(strtok(NULL, " \n") != NULL)
		{}
	}
	else if(s2.compare("load") == 0)
	{
		b = strtok(NULL, " \n");
		if (b == nullptr)
		{
			std::cout << "null args" << std::endl;
			return -1;
		}
		else
		{
			s2 = b;
			player->load(s2);
		}
	}
	else 
	{
		return -1;
	}

	TaskGenerator* tg = new TaskGenerator();

	Examenator* ex = new Examenator();

	Commander* cm = new Commander(tg, ex);

	std::string str = "";

	int rtrn = 0;

	while(rtrn == 0)
	{
		str = player->send_command();

		rtrn = cm->accept(player, str);
	}	


	return 0;
}
