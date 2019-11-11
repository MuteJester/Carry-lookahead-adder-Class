#include "CLA.h"

char full_adder::run_adder(char a, char b, char &carry_out, char carry_in) {
	int sum = (a - '0') + (b - '0') + (carry_in - '0');
	if (sum <= 9) {
		(carry_out) = '0';
		return sum + '0';
	}
	else {
		(carry_out) = '1';
		return (sum - 10) + '0';
	}
}

full_adder::full_adder() {
	a = b = sum = carry = '0';
	p_next = NULL;
}
full_adder::full_adder(char a, char b, char carry_in) {
	this->sum = run_adder(a, b, carry, carry_in);
}

CLA::CLA(string input_a, string input_b) {
	this->input_a = input_a;
	this->input_b = input_b;
	head = NULL;
	tail = NULL;
	length = 0;
}

CLA::CLA(string num_fac) {
	this->input_a = num_fac;
	this->input_b = "0";
	head = NULL;
	tail = NULL;
	length = 0;
}


void CLA::insert(char a, char b) {
	full_adder *nav = head;
	if (head == NULL) {
		head = new full_adder(a, b, '0');
		tail = head;
		length++;
	}
	else {
		tail->p_next = new full_adder(a, b, tail->carry);
		tail = tail->p_next;
		length++;
	}
}

int CLA::zero_at_start(string str) {
	int i, count = 0;
	for (i = 0; i < (int)str.length(); i++) {

		if (str[i] != '0') {
			break;
		}
		else {
			count++;
		}
	}
	return count;
}

void CLA::string_cut(int count) {
	int i, j = 0,len =strlen(output), zeros = zero_at_start(output);
	char *temp = (char*)malloc(len - zeros + 1);
	for (i = zeros; i < len; i++) {
		temp[j] = output[i];
		j++;
	}
	temp[j] = '\0';
	output = temp;
}

void CLA::cla_to_string() {
	char *out;
	int i, count = 0;
	full_adder *nav = head;
	if (tail->carry == '1') {
		i = length;
		out = (char*)malloc(length);
		while (nav) {

			if (nav->p_next == NULL && nav->carry == '1') {
				out[i] = nav->sum;
				i--;
				out[i] = '1';
				out[length+1] = '\0';
				output = out;
				break;
			}
			else {

				out[i] = nav->sum;
				i--;
				nav = nav->p_next;

			}
		}
		out[length + 1] = '\0';
	}
	else {
		i = length - 1;
		out = (char*)malloc(length + 1);
		while (nav) {

			if (nav->p_next == NULL && nav->carry == '1') {
				out[i] = nav->sum;
				i--;
				out[i] = '1';
				out[length + 1] = '\0';
				output = out;
				break;

			}
			else {

				out[i] = nav->sum;
				i--;
				nav = nav->p_next;

			}
		}
		out[length] = '\0';

	}

	count = zero_at_start(out);

	if (count == length) {
		out[0] = '0';
		out[1] = '\0';
		output = out;
	}
	else if (count != 0) {
		output = out;
		string_cut(count);
	}
	else {
		output = out;
	}
}

void CLA::add()
{


	int i, j, flag = 0;

	if (input_a.length() > input_b.length())
	{

		j = input_b.length() - 1;
		for (i = input_a.length() - 1; i >= 0; i--)
		{

			if (flag == 1) {
				insert(input_a[i], '0');
			}
			else {
				insert(input_a[i], input_b[j]);
				j--;
				if (j == -1) {
					flag = 1;
				}
			}

		}
		cla_to_string();

	}

	else if (input_b.length() > input_a.length())
	{
		j = input_a.length() - 1;
		for (i = input_b.length() - 1; i >= 0; i--)
		{

			if (flag == 1) {
				insert('0', input_b[i]);
			}
			else {
				insert(input_a[j], input_b[i]);
				j--;
				if (j == -1) {
					flag = 1;
				}
			}

		}
		cla_to_string();

	}

	else
	{
		for (i = input_a.length() - 1; i >= 0; i--) {
			insert(input_a[i], input_b[i]);
		}

		cla_to_string();
	}


}

void CLA::print() {
	cout << output;
}

int CLA::amount_of_digits(int num) {
	if (num == 0) {
		return num;
	}
	return 1 + amount_of_digits(num / 10);
}

char *CLA::int_to_str(int num) {
	int i, length = amount_of_digits(num), aux = 1;
	char *str = (char*)malloc(length + 1);
	for (i = 0; i < length - 1; i++) {
		aux *= 10;
	}
	for (i = 0; i < length; i++) {
		str[i] = ((num / aux) % 10) + '0';
		aux /= 10;
	}
	str[i] = '\0';
	return str;
}

int CLA::str_to_int() {
	int i, length =input_a.length(), aux = 1, res = 0;
	for (i = 0; i < length - 1; i++) {
		aux *= 10;
	}
	for (i = 0; i < length; i++) {
		res += (input_a[i] - '0')*aux;
		aux /= 10;
	}
	return res;
}

char *CLA::get_output() {
	return output;
}


void CLA::factorial_via_CLA() {
	int i, j;
	int time = str_to_int();
	string temp;
	temp.assign(input_a);
	for (j = time - 1; j > 1; j--) {
		input_b.assign(temp);

		for (i = 0; i < j - 1; i++) {
			add();

			print();
			cout << endl;

		}
		input_a = (string)get_output();
	}

}

void CLA::factorial_a() {
	factorial_via_CLA();
}
