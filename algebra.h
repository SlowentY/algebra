#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cstring>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <cstdlib>
#include <chrono>


#define FLOAT 1
#define INTEGER 0

typedef std::chrono::duration<long long, std::ratio<1, 1000000>> mksec;

#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_


void cut_nulls(double *v, std::string* str, int n);

class Equation {
	protected:
		friend class Examenator;
		int rate;
		int n_rt;
		int* rt_i;
		double* rt_d;
		std::vector<std::string>* rts;
		long long seed;
		std::string form;
		int key_coef;
	public:
		Equation();
		~Equation();
		virtual void gen() = 0;
		void print();
		void print_roots();
};

class AlgebraicEquation final : public Equation{
        private:
                int *coef_i;
		double *coef_d;

		template <class T>
		void viet(int n, T* rt, T* coef);
        public:
                AlgebraicEquation(int key);
                AlgebraicEquation(int pow, int key);
		~AlgebraicEquation();
		void gen() override;	
};

class LinearEquation : public Equation
{
	private:
		int x, b;
		double xd, bd;
	public:
		LinearEquation(int key);
		void gen() override;
};

class Task {
	private:
		friend class Examenator;
		std::vector<Equation*> equations;
	public:
		Task();
		~Task();
		void insert(Equation* eq);
		void print_all();
};

class Player {
	private:
		int level;
		std::string name;

		int curr_exp;
		int next_lvl_exp;
	public:
		Player();
		~Player();
		void create();
		void save(std::string filename);
		void load(std::string filename);
		void up_exp(int upxp);
		void print_info();
		std::string send_command();
		int get_level();
};

class TaskGenerator {
        private:
                long long seed;
                int n_tasks;
        public:
                TaskGenerator(int n=5);
                ~TaskGenerator();
                void gen(Player* person, Task* task);
		void update_n(int n=5);
};


class Examenator {
	//ЭЭкзаменатор, ЭЭЭЭЭЭЭЭЭЭЭкзаменатор! Перезвони мне, передай привет.
	private:
		int upxp;
	public:
		Examenator();
		~Examenator();
		void exam(Player* p, Task* t);
};

class Commander {
	private:
		TaskGenerator* tg;
		Examenator* ex;
	public:
		Commander(TaskGenerator* t, Examenator* e);
		~Commander();
		int accept(Player* p, std::string comm);
};
#endif
