#include <iostream>
#include <string>
#include "gradeCalc.h"
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

//function prototypes
/*Make this into a menu driven program using vectors
	Add Assignments
	Edit Assignments
	Delete Assignments
	Display Grades
	Exit
The program will store the assignments in a single text file.
As such you will need to load all the data from the file
when the program begins and save all the assignments to the same
file when you exit.

For the edit functionality:
	Edit Assignments -->display a list of the assignments and allow the
	user to select which index to edit

Delete Assignments Functionality
	display a list of the assignments and allow the
	user to select which index to delete

*/



//******************************************************************************************//
//  This is your Homework   For Tuesday 11/24/2020                                          //
//  1: Write your menu function                                                             //
//  2: implement the add assignment functionality.  When the                                //
//     user chooses add assignment they may add as many assignments they wish.              //
//     use lines 61-68 to implement for Tuesday                                             //
//  3: use lines 70-74 to implement the display assignments functionality                   //
//                                                                                          //
//  On Tuesday we will ensure that we do not add two Assignments with the same name         //
//                                                                                          //
//******************************************************************************************//



//******************************************************************************************//
//                                                                                          //
//  This is your Homework   For Tuesday 12/01/2020                                          //
//  1: Edit display function as indicated in the display function below.                    //
//  2: Update all function prototypes and headers to pass the vector                        //
//     by reference	to all functions														//
//  3: Implement the edit assignment functionality as per the edit function pseudo          //
//      code listed below.														            //
//  4: implement the load data and save data functions.  When the menu is called            //
//     load the assignment records from assignments.dat file.  When the program exits       //
//     save all the assignments to assignments.dat file.  Use the file format               //
//     listed with the load and save data function pseudo code below.                       //
//  5: Modify the addAssignment() function to ensure that we do not add two                 //
//     Assignments with the same name.  Change the function name to add_Assignment          //
//     and pass the vector to the functions as a reference parameter                        //
//******************************************************************************************//



//an example of overloading
//void setAssignmentValues(Assignment&);  --  do not use: just an example
Assignment add_Assignment(vector<Assignment>& myAssignments);
void displayAssignment(Assignment& assignment);
void calc_Grade(Assignment[], int&);
double calcCategoryScore(Assignment myAssignments[], int& SIZE, string cat);
void mainMenu();
void addAssignment(vector<Assignment>& myCourseGrades);  //example of function overloading
//two functions with the same name but different parameter lists
void displayAssignment(vector<Assignment>& myCourseGrades);
//Prototypes for editAssignments, loadData, saveData functions
void loadData(vector<Assignment>& myCourses);
void saveData(vector<Assignment>& myCourses);

int main()
{
	const int SIZE = 3;  //the total number of assignments
	Assignment myAssignment[SIZE];

	//call the menu function
	mainMenu();

	return 0;
}


/*
This function creates an Assignment object, prompts the
user to enter the required Title, Category, and Score.  It
returns the object to the calling function.
*/

//Modify this functions as follows:
//Rename yo add_Assignment and pass the vector of 
//Assignments as a reference parameter.
//Ensure that a title is only added once
Assignment add_Assignment(vector<Assignment>& myAssignments)
{
	Assignment assignment;
	string input;  //gets input from the user
	double score;

	system("cls");
	cout << "\n\nConfiguring assignment:\nPlease enter the name of the assignment (nospaces): ";
	cin >> input;
	assignment.setTitle(input);
	//verify that the titled entered has not been used with another assignment. 
	//If it has, notify the user and ask to have the title re-entered.
	//validate Title
	for (int i = 0; i < myAssignments.size(); i++)
		if (myAssignments.at(i).getTitle() == input)
			cout << "Assignment Title already in use";


	for (int i = myAssignments.size() - 1; i >= 0; i--)
		cout << myAssignments.at(i).getScore() << endl;

	cin.ignore(100, '\n'); //flushes the buffer since working with strings
	cout << "\nPlease enter the category for the assignment (nospaces and lowercase):\nfinal || midterm || quiz || project || homework || ica "
		<< "\nEnter the category: ";
	cin >> input;
	//validate Category
	while (input != "final" && input != "midterm" && input != "quiz" && input != "project" && input != "homework" && input != "ica")
	{
		cout << "\nIncorrect.  Please try again: ";
		cin >> input;
	}
	assignment.setCategory(input);
	cin.ignore(100, '\n'); //flushes the buffer since working with strings
	cout << "\n\nPlease enter a score for this assignment between 0 and 100: ";
	cin >> score;
	//validate Score
	while (score < 0 || score >100)
	{
		cout << "\nIncorrect.  Please try again: ";
		cin >> score;
	}
	assignment.setScore(score);
	displayAssignment(assignment);
	system("pause");
	return assignment;
} //end of addAssignment function that returns an Assignment object

// This functions displays a single assignment
void displayAssignment(Assignment& assignment)
{
	cout << "\n\nAssignment updated:\nTitle: " << assignment.getTitle() << " Category: " << assignment.getCategory()
		<< " Score: " << assignment.getScore() << "\n";

}


//Modify this calc_Grade function to make it behave
//the way you want it to.
void calc_Grade(Assignment myAssignments[], int& SIZE)
{
	double ClassScore = 0;

	//calculate Final
	ClassScore += FINAL * (calcCategoryScore(myAssignments, SIZE, "final"));
	ClassScore += MIDTERM * (calcCategoryScore(myAssignments, SIZE, "midterm"));
	ClassScore += QUIZ * (calcCategoryScore(myAssignments, SIZE, "quiz"));
	ClassScore += HOMEWORK * (calcCategoryScore(myAssignments, SIZE, "homework"));
	ClassScore += ICA * (calcCategoryScore(myAssignments, SIZE, "ica"));
	ClassScore += PROJECT * (calcCategoryScore(myAssignments, SIZE, "project"));
	cout << "The class score is " << ClassScore << ".  You earned a letter grade of ";
} //end of calc_Grade function

/*This function takes an array of assignments, the size of the array, and category
to sum and returns the average of the category.
*/
double calcCategoryScore(Assignment myAssignments[], int& SIZE, string cat)
{
	int numOfAssignments = 0; //the number of assignments in a category
	double assign_sum = 0;    //running total of scores for a category
	//double categoryScore;  //the score for each category

	for (int i = 0; i < SIZE; i++) {
		if (myAssignments[i].getCategory() == cat)
		{
			assign_sum += myAssignments[i].getScore();
			numOfAssignments++;
		}
	}
	return assign_sum / numOfAssignments;
} //end of calcCategoryScore function

//define your menu function here
/*
		For Tuesday 12/01/2020
		Modify this function to load the assignment.dat file when called
		and to save the data when exiting the functions
*/
void mainMenu()
{
	vector<Assignment> myCourseGrades;  //stores all the Assignment objects
	char choice = 'z';  //used to make a menu selection and to exit the program

	loadData(myCourseGrades);
	//loop the menu
	do
	{
		//display menu
		system("cls");
		cout << "\n1) Add Assignments"
			<< "\n2) Edit Assignments"
			<< "\n3) Delete Assignments"
			<< "\n4) Display Grades"
			<< "\n5) Exit"
			<< "\nPlease enter a choice: ";
		//take user input
		cin >> choice;
		//switch user input
		switch (choice)
		{
		case '1':
			addAssignment(myCourseGrades);
			break;
		case '2':

			break;
		case '3':

			break;
		case '4':
			displayAssignment(myCourseGrades);
			system("pause");
			break;
		case '5':
			system("cls");
			cout << "\n\n ...writing Assignments to file assignment.dat.\n";
			saveData(myCourseGrades);
			system("pause");
			break;
		default:
			cout << "\nInvalid selection.  Please try again.\n";
		}//end of switch

	} while (choice != '5');

}//end of mainMenu function

//define your add function here
void addAssignment(vector<Assignment>& myCourseGrades)
{
	char choice = 'z';
	//get the assignments from the user
	while (choice != 'n')
	{
		myCourseGrades.push_back(addAssignment());
		cout << "\nWould you like to add another assignment? (y/n): ";
		cin >> choice;
	}
}//end of addAssignment

//	Display vector of assignments.  Update this function as
//	indicated by the comments inside the function
/* Display assignments using this format
		 #	Title		Category		Score
		 ====================================
		 1) Hmk - ch01	homework		   99
		 2) Quiz_ch01	quiz			   99
		 ------------------------------------
*/
void displayAssignment(vector<Assignment>& myCourseGrades)
{
	string line1, line2;
	line1.append(48, '=');
	line2.append(48, '-');
	//clear the screen
	system("cls");
	//notifies user of the number of Assignments loaded into the system
	cout << "\n\n     There are " << myCourseGrades.size() << " assignments loaded. \n";
	//header line
	cout << "\n\n" << setw(5) << right << "#" << setw(2) << " "
		<< setw(20) << left << "Title"
		<< setw(15) << left << "Category"
		<< setw(6) << right << "Score";
	//line under header
	cout << "\n" << line1 << "\n";
	//display data
	for (int i = 0; i < myCourseGrades.size(); i++)
		cout << "\n" << setw(4) << right << i + 1 << ")" << setw(2) << " "
		<< setw(20) << left << myCourseGrades.at(i).getTitle()
		<< setw(15) << left << myCourseGrades.at(i).getCategory()
		<< setw(6) << right << myCourseGrades.at(i).getScore();
	//line after data
	cout << "\n" << line2 << "\n";

}



/*  EDIT ASSIGNMENT FUNCTION
	This function takes a vector of assignments as a reference parameter
	loop
		Clear the screen.
		Diplay the assignments
		Ask user to enter assignment number to edit, q to quit
		take use input
		if user enters q, end the function
		else
			ask user to choose to edit the Title, Category, or Score
			if user chooses Title
				Validate title is not already being used
				Assign the user input as the new title of the selected assignment
				state that title was updated.
			if user chooses Category
				assign the user input the new category of the selected assignment
				state that catgeory was updated
			if user chooses SCore
				assign the user input to the score of the selected assignment
				state that score was updated
*/
//Define edit assignment function here


/*
	loadData function.  Takes a vector of Assignments as a parameter.  Opens the
	data file assignment.dat.  Each line has title, category, and score separated
	by a space.  Creates an Assignment object, read the title, category, and score
	then add the object to the vector.
*/
//Define loadData function here
void loadData(vector<Assignment>& myCourses)
{
	ifstream inputFile;  //input stream for assignment.dat
	inputFile.open("assignment.dat");
	int count = 0; //counts number of Assignments added from the file
	string title, category; //Assignment Title or Category
	double score;  //Assignment score

	if (inputFile)
	{
		while (!inputFile.eof())
		{
			//reads a line, representing an Assignment object, from the file
			if (inputFile >> title >> category >> score)
			{	//creates a new Assignment object and adds it to the vector
				myCourses.push_back(Assignment(title, category, score));
				count++;
			}
			else if (count > 0)
				cout << "\n\n    ... " << count << " Assignments were loaded into the system.\n";
			else
				cout << "\n    ... No records found in file.  No data loaded.\n";
		}
		inputFile.close();
		system("pause");
	}
	else
	{
		system("cls"); //clear screen
		cout << " \n    ... File not found.  No data loaded.\n";
		system("pause");
	}

}

/*
	saveData function.  Takes a vector of Assignments as a parameter.  Opens the
	data file assignment.dat.  Write each Assignment object stored in the vector as
	a line of data in the order (title, category, score) separated by a space.

*/
//Define saveData function here
void saveData(vector<Assignment>& myCourses)
{
	ofstream outPutFile;
	outPutFile.open("assignment.dat");
	int i;
	if (myCourses.size() > 0)
	{
		for (i = 0; i < myCourses.size(); i++)
			outPutFile << myCourses.at(i).getTitle() << " "
			<< myCourses.at(i).getCategory() << " "
			<< myCourses.at(i).getScore() << "\n";
		cout << "\n\n    ..." << i << " Assignments were written to assignmemt.dat.  Closing file and exiting.\n";
	}
	else
		cout << "\n\n    There are no Assignments to write to file.  Closing file and exiting.\n";

	outPutFile.close();
}




////////////////////////////////////////////////////////////////////////////////////////////

/*               Do not use -- example of overloading
void setAssignmentValues(Assignment& assignment)
{
	string input;  //gets input from the user
	double score;

	system("cls");
	cout << "\n\nConfiguring assignment:\nPlease enter the name of the assignment (nospaces): ";
	cin >> input;
	assignment.setTitle(input);
	cin.ignore(100, '\n'); //flushes the buffer since working with strings
	cout << "\nPlease enter the category for the assignment (nospaces and lowercase):\nfinal || midterm || quiz || project || homework || ica "
		<< "\nEnter the category: ";
	cin >> input;
	//validate category
	while (input != "final" && input != "midterm" && input != "quiz" && input != "project" && input != "homework" && input != "ica")
	{
		cout << "\nIncorrect.  Please try again: ";
		cin >> input;
	}
	assignment.setCategory(input);
	cin.ignore(100, '\n'); //flushes the buffer since working with strings
	cout << "\n\nPlease enter a score for this assignment between 0 and 100: ";
	cin >> score;
	while (score < 0 || score >100)
	{
		cout << "\nIncorrect.  Please try again: ";
		cin >> score;
	}
	assignment.setScore(score);
	displayAssignment(assignment);
	system("pause");
}
*/