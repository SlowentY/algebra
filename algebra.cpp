#include "algebra.h"

/* Realizations of main functions and classes */



/* cut_nulls(double*, std::string*, int n) delete all nulls at end of float numbers */

template <class T>
void AlgebraicEquation::viet(int n, T* rt, T* coef)
{
	switch(n)
        {
                 case 5:
                        coef[0]=1;
                        coef[1]= -(rt[0]+rt[1]+rt[2]+rt[3]+rt[4]);
                        coef[2]=rt[0]*rt[1] + rt[1]*rt[2] + rt[2]*rt[3] + rt[3]*rt[4] + rt[4]*rt[2] + rt[4]*rt[1] +rt[4]*rt[0] +
                        rt[3]*rt[1] + rt[3]*rt[0] + rt[2]*rt[0];
                        coef[3]= -(rt[0]*rt[1]*rt[2] + rt[1]*rt[2]*rt[3] + rt[2]*rt[3]*rt[4] + rt[0]*rt[2]*rt[3] + rt[0]*rt[2]*rt[4] +
                                rt[0]*rt[3]*rt[4] + rt[0]*rt[1]*rt[4] + rt[0]*rt[1]*rt[3] + rt[1]*rt[2]*rt[4] + rt[1]*rt[3]*rt[4]);
                        coef[4]=rt[0]*rt[1]*rt[2]*rt[3] + rt[1]*rt[2]*rt[3]*rt[4] + rt[0]*rt[2]*rt[3]*rt[4] + rt[0]*rt[1]*rt[2]*rt[4] +
                        rt[0]*rt[1]*rt[3]*rt[4];
                        coef[5]= -(rt[0]*rt[1]*rt[2]*rt[3]*rt[4]);
                        break;
                case 4:
                        coef[0]=1;
                        coef[1]= -(rt[0]+rt[1]+rt[2]+rt[3]);
                        coef[2]=rt[0]*rt[1] + rt[1]*rt[2] + rt[2]*rt[3] +
                                rt[3]*rt[1] + rt[3]*rt[0] + rt[2]*rt[0];
    	                coef[3]= -(rt[0]*rt[1]*rt[2] + rt[1]*rt[2]*rt[3] + rt[0]*rt[2]*rt[3]+
                                rt[0]*rt[1]*rt[3]);
    			coef[4]=rt[0]*rt[1]*rt[2]*rt[3];
                        break;
                case 3:
                        coef[0]=1;
                        coef[1]= -(rt[0]+rt[1]+rt[2]);
                        coef[2]=rt[0]*rt[1] + rt[1]*rt[2] + rt[0]*rt[2];
                        coef[3]= -(rt[0]*rt[1]*rt[2]);
                        break;
                case 2:
                        coef[0]=1;
                      	coef[1]= -(rt[0] + rt[1]);
			coef[2]= rt[0]*rt[1];
                        break;
		default:
                        std::cout << "please set supported pow (2 - 5)" << std::endl;
	}
}

void cut_nulls(double* v, std::string* str, int n)
{
                for(int i = 0; i < n; i++)
                {
                        str[i] = std::to_string(v[i]);
                        for(int j = str[i].length()-1; str[i][j] == '0'; j--)
                        {
                                if(str[i][j-1] == '.')
                                {
                                        break;
                                }
                                str[i][j] = '\0';
                        }
                }
}


/* Base equation class constructor */

Equation::Equation()
{
	rate = 0;
	form = "";
        mksec mks = std::chrono::duration_cast<mksec>(std::chrono::system_clock::now().time_since_epoch());
	seed = mks.count();
	rts = new std::vector<std::string>;
}

/* ... Destructor */

Equation::~Equation()
{
	delete rt_i;
	delete rt_d;
	delete rts;
}

/* Algebraic Equation */

AlgebraicEquation::AlgebraicEquation(int key)
{
	srand(seed);
	n_rt = 2 + rand() % 4;
	key_coef = key;

	rate = 10 + (n_rt-1)*10 + key_coef*n_rt*10;

	if(key_coef == INTEGER)
	{
		rt_i = new int[n_rt];
		coef_i = new int[n_rt+1];
	}
	if(key_coef == FLOAT)
	{
		rt_d = new double[n_rt];
		coef_d = new double[n_rt+1];
	}
}



AlgebraicEquation::AlgebraicEquation(int pow, int key)
{
	n_rt = pow;

	key_coef = key;
	
	rate = 10 + (n_rt-1)*10 + key_coef*n_rt*10;

	if(key_coef == INTEGER)
	{
		rt_i = new int[n_rt];
		coef_i = new int[n_rt+1];
	}
	if(key_coef == FLOAT)
	{
		rt_d = new double[n_rt];
		coef_d = new double[n_rt+1];
	}
}



/* Generate new algebraic equation*/

void AlgebraicEquation::gen()
{
	// set random seed
	srand(seed);

	// for integer coeficents
	if(key_coef == INTEGER)
	{	
		//generate roots
		for(int i = 0; i<n_rt; i++)
        	{
                	int r = rand() % 20 - 10;
                	rt_i[i] = r;
			rts->push_back(std::to_string(r));
        	}


		//viet formules foRound down value (function )
		//
		viet<int>(n_rt, rt_i, coef_i);


		//set form for printing equation
		for(int i = 0; i<(n_rt+1); i++)
	        {
                	if(i != n_rt)
        	        {
	                        if(coef_i[i] == 0)
                        	{}
                	        else
        	                {
	                                if(i == n_rt-1)
                                	{
                        	                form = form + ((form=="")?"":((coef_i[i]<0)?"":"+")) + std::to_string(coef_i[i]) + "x";
                	                }
        	                        else
	                                {
                                	        form = form + ((form=="")?"":((coef_i[i]<0)?"":"+")) + std::to_string(coef_i[i]) + "x^" +
                        	                std::to_string(n_rt-i);
                	                }
        	                }
	                }
                	else
        	        {
	                        if(coef_i[i] == 0)
                        	{
                	        }
        	                else
	                        {
                                	form = form + ((form=="")?"":((coef_i[i]<0)?"":"+")) + std::to_string(coef_i[i]);
                        	}
                	}
		}
		form = form+" = 0";
	}
	// for float coeficents
	else if(key_coef == FLOAT)
	{
		for(int i = 0; i<n_rt; i++)
        	{
			std::stringstream ss;
                	double r = ((double)(rand() % 2000 - 1000))/100;
                	rt_d[i] = r;
			ss << std::setprecision(15) << r;
			rts->push_back(ss.str());
			ss.str("");
 		}
	
		viet<double>(n_rt, rt_d, coef_d);

		std::string* str_f_coef = new std::string[n_rt+1];
		for(int i = 0; i < n_rt+1; i++)
		{
			std::stringstream ss;
			ss << std::setprecision(15) << coef_d[i];
			str_f_coef[i] = ss.str();
			ss.str("");
		}


		for(int i = 0; i<(n_rt+1); i++)
	        {
                	if(i != n_rt)
        	        {
	                        if(coef_d[i] == 0)
                        	{}
                	        else
        	                {
	                                if(i == n_rt-1)
                                	{
                        	                form = form + ((form=="")?"":((coef_d[i]<0)?"":"+")) + str_f_coef[i] + "x";
                	                }
        	                        else
	                                {
                                	        form = form + ((form=="")?"":((coef_d[i]<0)?"":"+")) + str_f_coef[i] + "x^" +
                        	                std::to_string(n_rt-i);
                	                }
        	                }
	                }
                	else
        	        {
	                        if(coef_d[i] == 0)
                        	{
                	        }
        	                else
	                        {
                                	form = form + ((form=="")?"":((coef_d[i]<0)?"":"+")) + str_f_coef[i];
                        	}
                	}
        	}
		form=form+" = 0";
	}

}


/* print algebraic equation */
void Equation::print()
{
	std::cout << "\n" << form << std::endl;
}


/* printing roots of algebraic equation */
void Equation::print_roots()
{	
	int i = 0;
	for(std::string rt : *rts)
	{
		i++;
		std::cout << "Root " << i << ":\t" << rt << std::endl;
	}

}


/* destructor */
AlgebraicEquation::~AlgebraicEquation()
{
	delete coef_i;
	delete coef_d;
}

LinearEquation::LinearEquation(int key)
{
	key_coef = key;

	rate = 10 + key_coef*15;
	n_rt = 1;

        if(key_coef == FLOAT)
        {
                rt_d = new double[n_rt];
        }
	else if(key_coef == INTEGER)
        {
                rt_i = new int[n_rt];
        }
}

void LinearEquation::gen()
{
	srand(seed);
	if(key_coef == INTEGER)
	{
		x = 0;

		while(x == 0)
		{
			x = rand() % 400 - 200;
		}

		b = rand() % 400 - 200;
		rt_i[0] = -b;
		b = x*b;
		rts->push_back(std::to_string(rt_i[0]));

		form = form + std::to_string(x) + "x" + ((b < 0) ? "" : "+") + std::to_string(b) + " = 0";
	}
	if(key_coef == FLOAT)
	{
		xd = 0.0;

		while(xd == 0.0)
		{
			xd = ((double)(rand() % 4000 - 2000))/100.0;
		}
		

        	bd = ((double)(rand() % 4000 - 2000))/100.0;
		rt_d[0] = -bd;
		bd = xd * bd;

		std::stringstream ss;

		ss << std::setprecision(15) << rt_d[0];

		rts->push_back(ss.str());

		ss.str("");

		ss << std::setprecision(15) << xd;

		form = form + ss.str() + "x";

		ss.str("");

		ss << std::setprecision(15) << bd;

		form = form + ((bd < 0) ? "" : "+") + ss.str() + " = 0";

		ss.str("");
	}
}

Task::Task()
{

}

Task::~Task()
{
	for(Equation* n : equations)
	{
		delete n;
	}
}

void Task::insert(Equation* eq)
{
	equations.push_back(eq);
}

void Task::print_all()
{
	for(Equation* n : equations)
	{
		n->print();
		#ifdef WITH_ANSWERS
			n->print_roots();
		#endif
	}
}

Player::Player()
{
	std::cout << "\nObject player was initialised." << std::endl;
}

Player::~Player()
{

}

void Player::create()
{
	std::cout << "Set player name: ";
	std::getline(std::cin, name, '\n');

	level = 1;
	curr_exp = 0;
	next_lvl_exp = level * 250;

	std::cout << "\nPlayer was created." << std::endl;
}

void Player::save(std::string filename)
{
	std::ofstream f(filename);

	std::string str = "";

	str = str + "NAME " + name + "\n";
	str = str + "LVL " + std::to_string(level) + "\n";
	str = str + "CXP " + std::to_string(curr_exp) + "\n";

	f.write(str.c_str(), str.length());
	f.close();

	std::cout << "\nGame was saved!" << std::endl;
}

void Player::load(std::string filename)
{
	std::fstream f(filename);
	
	std::string str = "";
	char c;

	while(!f.eof())
	{
		std::getline(f, str);
		std::istringstream is(str);

		std::getline(is, str, ' ');
		if(str.compare("NAME") == 0)
		{
			std::getline(is, str, ' ');
			name = str;
		}
		else if(str.compare("LVL") == 0)
		{
			std::getline(is, str, ' ');
			level = std::stoi(str);
		}
		else if(str.compare("CXP") == 0)
		{
			std::getline(is, str, ' ');
			curr_exp = std::stoi(str);
		}
	}
	next_lvl_exp = level*250;
	std::cout << "\nGame was loaded! Hello, " << name << "!!!" << std::endl;
}

void Player::up_exp(int upxp)
{
	curr_exp = curr_exp + upxp;
	if(curr_exp >= next_lvl_exp)
	{
		curr_exp = curr_exp - next_lvl_exp;
		level++;
		next_lvl_exp = next_lvl_exp * 2;

		std::cout << "LEVEL UP!!!" << std::endl;
	}
}

void Player::print_info()
{
	std::cout << "\nName: " << name << std::endl;
	std::cout << "Level: " << level << std::endl;
	std::cout << "XP: " << curr_exp << std::endl;
	std::cout << "XP for next level: " << next_lvl_exp << std::endl; 
}

std::string Player::send_command()
{
	std::string str;

	std::cout << "\n" << name << "@COMMANDER        #> ";
	std::getline(std::cin, str, '\n');
	return str;
}
int Player::get_level()
{
	return level;
}

TaskGenerator::TaskGenerator(int n)
{
	n_tasks = n;
        mksec mks = std::chrono::duration_cast<mksec>(std::chrono::system_clock::now().time_since_epoch());
        seed = mks.count();
}

TaskGenerator::~TaskGenerator()
{
	
}

void TaskGenerator::gen(Player* player, Task* task)
{
	srand(seed);
	Equation* eq;

	for(int i = 0; i<n_tasks; i++)
	{
		int num = 1 + rand() % 10;

		switch(player->get_level())
		{
			case 1:
				eq = new LinearEquation(INTEGER);
				eq->gen();
				task->insert(eq);
				eq = nullptr;
				break;
			case 2:
				if(num == 1 || num == 2 || num == 3 || num == 6 || num == 7 || num == 8)
				{
					eq = new LinearEquation(INTEGER);
                                	eq->gen();
                                	task->insert(eq);
                                	eq = nullptr;
				}
				else if(num == 4 || num == 5 || num == 9 || num == 10)
				{
					eq = new LinearEquation(FLOAT);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
				}
				break;
			case 3:
				if(num == 1 || num == 2)
                                {
                                        eq = new LinearEquation(INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 4 || num == 5 || num == 9 || num == 10)
                                {
                                        eq = new LinearEquation(FLOAT);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
				else if(num == 6 || num == 3 || num == 7 || num == 8)
				{
					eq = new AlgebraicEquation(2, INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
				}
				break;
			case 4:
				if(num == 1)
                                {
                                        eq = new LinearEquation(INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 4 || num == 5)
                                {
                                        eq = new LinearEquation(FLOAT);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 6 || num == 3 || num == 7 || num == 8 || num == 2)
                                {
                                        eq = new AlgebraicEquation(2, INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
				else if(num == 10 || num == 9)
				{
					eq = new AlgebraicEquation(3, INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
				}
                                break;
			case 5:
				if(num == 1)
                                {
                                        eq = new LinearEquation(INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 4 || num == 5)
                                {
                                        eq = new LinearEquation(FLOAT);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 6 || num == 3 || num == 7 || num == 2)
                                {
                                        eq = new AlgebraicEquation(2, INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 10 || num == 9 || num ==8)
                                {
                                        eq = new AlgebraicEquation(3, INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                break;
			default:
				if(num == 1)
                                {
                                        eq = new LinearEquation(INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 4 || num == 5)
                                {
                                        eq = new LinearEquation(FLOAT);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 6 || num == 3 || num == 7 || num == 2)
                                {
                                        eq = new AlgebraicEquation(2, INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                else if(num == 10 || num == 9 || num ==8)
                                {
                                        eq = new AlgebraicEquation(3, INTEGER);
                                        eq->gen();
                                        task->insert(eq);
                                        eq = nullptr;
                                }
                                break;				
		}
	}
	std::cout << "\nTask was generated." << std::endl;
}

Examenator::Examenator()
{
	upxp = 0;
}

Examenator::~Examenator()
{

}

void Examenator::exam(Player* p, Task* t)
{
	for(Equation* e : t->equations)
	{
		e->print();
		std::cout << "\nEnter roots for this equation" << std::endl;
		
		std::string r;
		
		std::vector<std::string> r_a;

		int i = 0;
		while(e->rts->size() != 0)
		{
			std::cout << "Root " << i+1 << ": ";
			std::cin >> r;

			std::vector<std::string>::iterator it = e->rts->begin();
			while(i <= e->rts->size())
			{
				i++;
				bool a = false;
				for(std::string n : r_a)
				{
					if(r.compare(n) == 0 && n.compare(*it) != 0)
					{
						a = true;
					}
				}
				if(a)
				{
					std::cout << "This root is already entered!!!" << std::endl;
					a = false;
					break;
				}

				else if(r.compare(*it) == 0)
				{
					r_a.push_back(*it);
					e->rts->erase(it);
					if (it._Ptr == nullptr)
					{

					}
				}
				else
				{
					std::cout << "This root doesn't right!!!" << std::endl;
					break;
				}
				if (it._Ptr == nullptr)
				{
					++it;

				}
			}
			i = 0;
		}
			
		std::cout << "SUPER!!!" << std::endl;
		upxp = upxp + e->rate + p->get_level()*2;
	}

	std::cout << "\nTask completed!!!" << std::endl << "You gained " << upxp << " EXP" << std::endl;
	p->up_exp(upxp);

	upxp = 0;

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Commander::Commander(TaskGenerator* t, Examenator* e)
{
	ex = e;
	tg = t;
}

Commander::~Commander()
{

}

int Commander::accept(Player* p, std::string comm)
{
	const char *x = comm.c_str();
	char c[256];
	char** a;

	strcpy_s(c, x);

	std::string ncomm;

	char* bb = strtok(c, " \n");
	if (bb == nullptr)
	{
		std::cout << "null args" << std::endl;
	}
	else
	{
		ncomm = bb;
	}
	
	if (ncomm.compare("save") == 0)
	{
		bb = strtok(NULL, " \n");
		if (bb == nullptr)
		{
			std::cout << "null args" << std::endl;
		}
		else
		{
			ncomm = bb;
			p->save(ncomm);
		}
	}
	else if(ncomm.compare("load") == 0)
	{
		bb = strtok(NULL, " \n");
		if (bb == nullptr)
		{
			std::cout << "null args" << std::endl;
		}
		else
		{
			ncomm = bb;
			p->load(ncomm);
		}
	}
	else if(ncomm.compare("info") == 0)
	{
		p->print_info();
	}
	else if(ncomm.compare("play") == 0)
	{
		Task* task = new Task();
		tg->gen(p, task);
		ex->exam(p, task);
		delete task;
	}
	else if(ncomm.compare("exit") == 0)
	{
		std::cout << "\nExiting..." << std::endl;
		return -1;
	}
	else
	{
		std::cout << "\ncommand not found" << std::endl;
	}

	return 0;
}
