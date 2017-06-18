#include "InsertStatement.h"
#include <iostream>

using namespace std;

//InsertStatement::InsertStatement(Table* table, std::vector<Argument*> args) {
//	this->table = table;
//	this->args = vector<Argument*>(args);
//}

InsertStatement::InsertStatement(Table *table) {
	this->table = table;
}

void InsertStatement::add_argument(Argument *arg) {
	this->args.push_back(arg);
}

InsertStatement::~InsertStatement() {
	for (auto it = this->args.begin(); it != this->args.end(); it++)
		delete *it;
}

Table* InsertStatement::get_table() {
	return this->table;
}

void InsertStatement::print_arguments(std::ofstream* ofs, std::ofstream* ofl) {
	vector<string> sig_arr;
	for (auto it = this->args.begin(); it != this->args.end(); it++) {
		string arg_sig = (*it)->print();
		if (!arg_sig.empty()) {
			sig_arr.push_back(arg_sig);
		}
	}

	if (sig_arr.size() > 0) {
		(*ofs) << sig_arr[0];
		for (int i = 1; i < sig_arr.size(); i++) {
			(*ofs) << ", " << sig_arr[i];
		}
	}
}

void InsertStatement::print_full_signature(std::ofstream* ofs, std::ofstream* ofl) {
	vector<string> sig_arr;
	for (auto it = this->args.begin(); it != this->args.end(); it++) {
		string arg_sig = (*it)->signature();
		if (!arg_sig.empty()) {
			sig_arr.push_back(arg_sig);
		}
	}

	if (sig_arr.size() > 0) {
		(*ofs) << sig_arr[0];
		for (int i = 1; i < sig_arr.size(); i++) {
			(*ofs) << ", " << sig_arr[i];
		}
	}
}

void InsertStatement::print(ofstream* ofs, ofstream* ofl, string func_name) {
	this->get_table()->print(ofs, ofl);

	(*ofs) << "void " << func_name << "(";
	this->print_full_signature(ofs, ofl);
	(*ofs) << ") {" << endl;

	(*ofs) << "\t" << "struct " << this->get_table()->get_name() << "_struct* arg = malloc(sizeof(struct "
	       << this->get_table()->get_name() << "_struct));" << endl;

	for (int i = 0; i < this->get_table()->cols_size(); i++) {
		(*ofs) << "\t" << "arg->" << this->get_table()->cols_at(i)->get_name() << " = " << this->args[i]->print() << ";" << endl;
	}

	(*ofs) << "\t" << this->get_table()->get_name() << "_insert(arg);" << endl;

	(*ofs) << "}" << endl
	       << endl;
}