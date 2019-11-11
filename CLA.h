#pragma once
#include <iostream>
#include <string>
using namespace std;

class full_adder {
private:
	char run_adder(char a, char b, char &carry_out, char carry_in);
public:
	char a;
	char b;
	char sum;
	char carry;
	full_adder *p_next;

	full_adder();
	full_adder(char a, char b, char carry_in);

};

class CLA {
	full_adder *head;
	full_adder *tail;
	string input_a;
	string input_b;
	char *output;
	int length;
	void string_cut(int count);
	void cla_to_string();
	int zero_at_start(string str);
	int str_to_int();
	char *int_to_str(int num);
	int amount_of_digits(int num);
	void factorial_via_CLA();
public:
	CLA(string input_a, string input_b);
	CLA(string num_fac);
	void insert(char a, char b);
	void add();
	void print();
	char *get_output();
	void factorial_a();
	
};


