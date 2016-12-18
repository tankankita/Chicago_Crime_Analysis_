// Ankita Tank
// CS341
// Homework 01 


#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>


using std::string;
using std::ifstream;
using std::vector;
using std::stringstream;
using std::getline;
using std::stoi;
using std::sort;
using std::cout;
using std::endl;
using std::sort;
using std::copy;


class Crime_code
{
public:
	string Primary_description;
	string Secondary_description;
	string IUCR;
	int total;
	Crime_code(string num, string pd, string sd,int t)
		: IUCR(num), Primary_description(pd), Secondary_description(sd), total(t)
	{}
};


class Crime
{
public:
	string DateTime;
	string IUCR;
	string arrest;
	string domestic;
	int beat;
	int district;
	int ward;
	int community;
	int year;

	Crime(string DT, string iucr, string arrt, string domest, int bt, int dist, int wd, int comty, int yr)
		:DateTime(DT), IUCR(iucr), arrest(arrt), domestic(domest), beat(bt), district(dist), ward(wd), community(comty), year(yr)
	{}
};


int main()
{
	cout << "** Crime Analysis **\n";
	cout << '\n';

	int scount = 0;
	int counter = -1;
	int first = 0;
	int last = 0;
	int ccount = 0;
	int count = -1;
	int ncount = 0;
	int set = 80000;

	string line, pd, sd, num;
	string DT, iucr, lines, arrt, domest;
	string bt, dist, wd, comty, yr;

	ifstream myfile("crimes.csv");
	ifstream file("crime-codes.csv");

	vector<Crime_code> ccode;
	vector <Crime> ccrime;
	
	//*******************************************************************//
	//Step 1: reading in files
	//reading in crimes.csv and crimecode.csv

	if (myfile.is_open())
	{
		getline(myfile, lines);
		while (!myfile.eof())
		{
			getline(myfile, lines);
			stringstream cc(lines);
			getline(cc, DT, ',');
			getline(cc, iucr, ',');
			getline(cc, arrt, ',');
			getline(cc, domest, ',');
			getline(cc, bt, ',');
			getline(cc, dist, ',');
			getline(cc, wd, ',');
			getline(cc, comty, ',');
			getline(cc, yr);
			counter++;
			Crime B(DT, iucr, arrt, domest, stoi(bt), stoi(dist), stoi(wd), stoi(comty), stoi(yr));
			ccrime.push_back(B);
		}
	}

	// reading in crime code.csv 

	if (file.is_open())
	{
		while (getline(file, line))
		{
			count++;
			stringstream ss(line);
			getline(ss, num, ',');
			getline(ss, pd, ',');
			getline(ss, sd);
			Crime_code A(num, pd, sd, NULL);
			ccode.push_back(A);
		}
	}


	//***********************************************************************//
	//step 2: oupput date range 

	cout << "Date range: ";
	for (Crime c : ccrime)
	{
		if (first == 0)
			cout <<c.DateTime <<" - ";

		first++;
	}
	
	for (Crime c : ccrime)
	{
		if (last == counter-1)
			cout << c.DateTime << "\n";
		
		last++;
	}
	
	cout << '\n';
	//******************************************************************************//
	//step 3
	//output total number of crimes in crimecode.csv	
	cout << "# of crime codes:  " << count << '\n';

		sort(ccode.begin(), ccode.end(),
			[](Crime_code A1, Crime_code A2){
				if (A1.IUCR < A2.IUCR)
				return true;
			else
				return false;
		}
		);

		//*********************Printing out the first 3 code*****************************

		for (Crime_code x : ccode)
		{
			cout << x.IUCR << ":  \t " << x.Primary_description << ":" << x.Secondary_description << '\n'; 
			ccount++;		
			if (ccount == 3)
				break;
		}
		ccode.pop_back();

		cout << "..." << '\n';

		//*********************Printing out the last 3 code*****************************

		for (Crime_code x : ccode)
		{
			if (ncount != count - 3)
				ncount++;		
			else
				cout << x.IUCR << ":  \t " << x.Primary_description << ":" << x.Secondary_description << '\n';
		}

		ccrime.pop_back();

		cout << "\n";

		//**********************Printing out the # of crimes 

		cout << "# of crimes: " << counter << '\n';

		string t = "TRUE";
		ccount = 0;

		for (Crime x : ccrime)
		{
				if (t.compare(x.domestic) == 0)
					cout << x.IUCR << ": \t" << x.DateTime << ", " << x.beat << ", " << x.district << ", " << x.ward << ", " << x.community << " doemestic voilence \n" ;	
				else
					cout << x.IUCR <<": \t" <<x.DateTime << ", " << x.beat << ", "<< x.district << ", " <<x.ward <<", " << x. community << '\n' ;
			
				ccount++;

			if (ccount == 3)
				break;
		}

		ncount = 0;
		cout << "... \n";
		t = "TRUE";

		//******************************* Printing the last 3 codes***********************
		for (Crime x : ccrime)
		{
			if (ncount != counter - 3)
				ncount++;
			else
			{
				if (t.compare(x.arrest) == 0) 
					cout << x.IUCR << ": \t" << x.DateTime << ", " << x.beat << ", " << x.district << ", " << x.ward << ", " << x.community << ", arrested \n";
				else
					cout << x.IUCR << ": \t" << x.DateTime << ", " << x.beat << ", " << x.district << ", " << x.ward << ", " << x.community << '\n';
			}
		}


		sort(ccrime.begin(), ccrime.end(),
			[](Crime A1, Crime A2) {
			if (A1.IUCR < A2.IUCR)
				return true;
			else
				return false;
		}
		);

		cout << '\n';
		cout << "** Top - 5 Crimes **\n";
		cout << "Code:\t" << "Total, Description\n";

		//***************************** Top 5 crime ***************************
			for (Crime_code x : ccode)
			{
				for (Crime a : ccrime)
				{
					if (a.IUCR == x.IUCR)
						x.total = x.total++;
				}

				if (x.total > 80000 && x.total < 90000 )
					cout << x.IUCR << ":\t" << x.total << "," << x.Primary_description <<":"<< x.Secondary_description <<'\n';
			}
			
			for (Crime_code x : ccode)
			{
				for (Crime a : ccrime)
				{
					if (a.IUCR == x.IUCR)
						x.total = x.total++;
				}
				if (x.total > 70000 && x.total < 80000)
					cout << x.IUCR << ":\t" << x.total << "," << x.Primary_description << ":" << x.Secondary_description << '\n';
			}

			for (Crime_code x : ccode)
			{
				for (Crime a : ccrime)
				{
					if (a.IUCR == x.IUCR)
						x.total = x.total++;
				}

				if (x.total > 50000 && x.total < 60000)
					cout << x.IUCR << ":\t" << x.total << "," << x.Primary_description << ":" << x.Secondary_description << '\n';
			}

			for (Crime_code x : ccode)
			{
				for (Crime a : ccrime)
				{
					if (a.IUCR == x.IUCR)
						x.total = x.total++;
				}

				if (x.total > 40300 && x.total  < 43200)
					cout << x.IUCR << ":\t" << x.total << "," << x.Primary_description << ":" << x.Secondary_description << '\n';
			}
		
		cout << "** DONE **\n";
		
		file.close();
		myfile.close();
		return 0;
}