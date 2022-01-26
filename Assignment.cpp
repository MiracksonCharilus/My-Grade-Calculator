#include <string>
#include "gradeCalc.h"

using namespace std;


Assignment::Assignment()
{
	title = "default";
	category = "default";
	score = -1.0;
}
Assignment::Assignment(string name, string cat, double points)
{
	setTitle(name);
	setCategory(cat);
	setScore(points);
}
void Assignment::setTitle(string name)
{
	title = name;
}
void Assignment::setCategory(string cat)
{
	category = cat;
}
void Assignment::setScore(double points)
{
	score = points;
}
string Assignment::getTitle()
{
	return title;
}
string Assignment::getCategory()
{
	return category;
}

double Assignment::getScore()
{
	return score;
}