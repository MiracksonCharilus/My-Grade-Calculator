#pragma once
#include <string>
using namespace std;

const double FINAL = .2;
const double MIDTERM = .2;
const double QUIZ = .1;
const double HOMEWORK = .1;
const double ICA = .2;
const double PROJECT = .2;

class Assignment {
private:
	string title;
	string category;
	double score;

public:


	Assignment();
	Assignment(string, string, double);
	void setTitle(string);
	void setCategory(string);
	void setScore(double);
	string getTitle();
	string getCategory();
	double getScore();

};