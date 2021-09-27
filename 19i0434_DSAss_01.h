#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
string semsterArr[1780][15];

double** distances;

//Functions for my own help.
void collectSems();
bool isHighestSem(string, int);
int SemGreaterOrNot(string a, string b);
double** SortArr(double** arr, int n);


//***********************************************************************************//
//    ASSIGNMENT NO.1 --- DATA STRUCTURES ---  <Predict Your Data Structures Grade>  //
//              NAME : SOURAV MALANI												 //	
//              SECTION : A															 //
//              Roll #: i19-0434													 //
//																					 //			
//     NOTE:I've only implemented first 5 Functions. <Rest are commented out,		 //
//              last five test cases while checking the assignment>                  //
//***********************************************************************************//

double** Load_Data(string path) {
	double **returnPtr,**returnPtr1,**returnPtr2;  //I've used these  3 ptrs instead of one just to ignore students with UK grade in DS.
	returnPtr =  new double* [1780];               //Otherwise one would have done the work.
	returnPtr1 = new double* [1780]; 
	returnPtr2 = new double* [1780]; 

	for (int row = 0; row < 1780; row++) { 
		returnPtr[row] = new double[17];
		returnPtr1[row] = new double[17];
		returnPtr2[row] = new double[17];
		for (int col = 0; col < 17; col++) {
			returnPtr[row][col] = 0;
			returnPtr1[row][col] = 0;
			returnPtr2[row][col] = 0;
		}
	}

	ifstream ip(path, ios::in);
	if (!ip.is_open()) std::cout << "error: file open" << '\n';

	string line, semster, cCode, Grade, gradePt, SGPA, CGPA, str, SrNo = "", privSrNo = "", warning, nextSrNo;
	double cgpa_I, warning_I, gradePt_I;

	getline(ip, line, '\n'); // skipping first line, which is of Titles.

	collectSems();
	int i = 0, sr = 0;
	while (!ip.eof()) {
		// get semster, which is at index 1
		getline(ip, SrNo, ','); //index 0
		sr = stoi(SrNo); //Converting SrNo to int.
		i = sr;
		getline(ip, semster, ',');

		if (semster == "unknown") {
			getline(ip, cCode, ','); // skip one word.
			getline(ip, line, ','); // skip one word.
			getline(ip, line, ','); // skip one word.
			getline(ip, Grade, ','); // skip one word.

			getline(ip, gradePt, ','); // skip one word.
			gradePt_I = stod(gradePt);
		}
		else {
			getline(ip, cCode, ','); //Course Code

			//Now skip 3 to get gradepoint
			getline(ip, str, ','); //Course Title
			getline(ip, str, ','); //Credit Hrs
			getline(ip, Grade, ','); //Grade

			if (Grade == "W") {
				getline(ip, line, '\n');
				continue;
			}

			getline(ip, gradePt, ','); //Grade Point
			gradePt_I = stod(gradePt);
			getline(ip, str, ','); //SGPA
			
	

			getline(ip, CGPA, ','); //CGPA
			cgpa_I = stod(CGPA);
			if (Grade == "F") { //if grade is F,don't count it.
				getline(ip, line, '\n');
				continue;
			}

			getline(ip, warning, '\n'); //warning
			warning_I = stod(warning);
			if (Grade != "F") {
				if (isHighestSem(semster, i)) {
					returnPtr[i][14] = cgpa_I;
					returnPtr[i][15] = warning_I;

				}
			}

		}

		if (cCode == "MT104") {
			returnPtr[i][0] = gradePt_I;
		}
		else if (cCode == "MT119") {
			returnPtr[i][1] = gradePt_I;
		}
		else if (cCode == "CS118") {
			returnPtr[i][2] = gradePt_I;
		}
		else if (cCode == "CL118") {
			returnPtr[i][3] = gradePt_I;
		}
		else if (cCode == "EE182") {
			returnPtr[i][4] = gradePt_I;
		}
		else if (cCode == "SL101") {
			returnPtr[i][5] = gradePt_I;
		}
		else if (cCode == "SS101") {
			returnPtr[i][6] = gradePt_I;
		}
		else if (cCode == "EE227") {
			returnPtr[i][7] = gradePt_I;
		}
		else if (cCode == "SS122") {
			returnPtr[i][8] = gradePt_I;
		}
		else if (cCode == "MT224") {
			returnPtr[i][9] = gradePt_I;
		}
		else if (cCode == "SS111") {
			returnPtr[i][10] = gradePt_I;
		}
		else if (cCode == "CS217") {
			returnPtr[i][11] = gradePt_I;
		}
		else if (cCode == "EL227") {
			returnPtr[i][12] = gradePt_I;
		}
		else if (cCode == "CL217") {
			returnPtr[i][13] = gradePt_I;
		}
		else if (cCode == "CS201") {
				returnPtr[i][16] = gradePt_I;
		}

		if (sr == 1779)
			break;
	}


	for (int row = 0; row < 1780; row++) { //Line 15
		if (returnPtr[row][16] == -1) 
			continue;
		for (int col = 0; col < 17; col++) {
			returnPtr1[row][col] = returnPtr[row][col];
		}
	}
	int k=-1, l=-1;
	for (i = 0; i < 1780; i++) {
		if (returnPtr1[i][0] != 0 && returnPtr1[i][4] != 0 && returnPtr1[i][16] != 0) { //If it is an zero row, then skip.
			k++;
		}
		for (int j = 0; j < 17; j++) {
			if (returnPtr1[i][0] != 0 && returnPtr1[i][4] != 0 && returnPtr1[i][16] != 0) {
				l++;
				returnPtr2[k][l] = returnPtr1[i][j];

			}
		}
		l = -1;
	}

	return returnPtr2;
}


double** Distance(double* predictedArray, int predictedArraySize, double** data, int dataRows, int dataCols) {
	double val1,val2,new_val1,new_val2;
	stringstream tmp;

	distances = new double* [1780];
	for (int row = 0; row < 1780; row++) { 
		distances[row] = new double[2];
		for (int col = 0; col < 2; col++)
			distances[row][col] = 0.0;
	}
	double TOTAL= 0,temp = 0;
	for (int row = 0; row < 1780; row++) { 
		for (int col = 0; col < 14; col++) {

			//Rounding off to 3 digits.
			val1 = predictedArray[col];
			tmp << setprecision(3) << fixed << val1;
			new_val1 = stod(tmp.str());   // new_val = 3.143
			tmp.str(string());          // clear tmp for future use

			//Rounding off to 3 digits.
			val2 = data[row][col];
			tmp << setprecision(3) << fixed << val2;
			new_val2 = stod(tmp.str());   
			tmp.str(string());  // clear tmp for future use


     		temp = (new_val1 - new_val2);

			if (temp < 0) //if negative make positive.
				temp = temp * -1;
			if (col == 2 || col == 3 || col == 11 || col == 13) { //if it is a data structures course multiply with 1.5 to inrease weightage.
				temp = temp * 1.5;
			}
			TOTAL += temp;
			if (col == 13) {
				//ROUND OFF to 3 digits..
				val1 = TOTAL;
				tmp << setprecision(3) << fixed << val1;
				new_val1 = stod(tmp.str());   // new_val = 3.143
				tmp.str(string());          // clear tmp for future use

				TOTAL = new_val1;
				distances[row][0] = TOTAL; //distance
				distances[row][1] = data[row][16];

			}
		}
		TOTAL = 0;
	}
	
	return distances;
}


// Return the 1st k sorted distance with Grade point in Ascending order 
double** Sort_k_Dis(int k, double** distance, int distanceRows, int distanceCols) {

	double** temp_distances;
	temp_distances = new double *[distanceRows];
	for (int row = 0; row < distanceRows; row++) {
		temp_distances[row] = new double[distanceCols];
		for (int col = 0; col < distanceCols; col++)
			temp_distances[row][col] = 0.0;
	}


	for (int row = 0; row < distanceRows; row++) {
		temp_distances[row][0] = distance[row][0];
		temp_distances[row][1] = distance[row][1];
	}
	distances = SortArr(temp_distances, k+1);

	return distances;
}


//// Return the most frequent Grade in DS; You need to convert Grade point in Grade 
string Grade_Frequency(double** sortedklist, int sortedklistrows, int sortedklistcols) {
	string returnGrade = "";
	int topCount = 0, count,i,j;
	double topElement;

	for (i = 0; i < sortedklistrows+1; i++)
	{
		count = 0;
		for (j = 0; j < sortedklistrows+1; j++)
		{
			if (sortedklist[i][1] == sortedklist[j][1]) count++;
		}
		if (count > topCount)
		{
			topCount = count;
			topElement = sortedklist[i][1];
		}
	}

	if (topElement == 4)
		returnGrade = "A";
	else if (topElement == 3.67)
		returnGrade = "A-";
	else if (topElement == 3.33)
		returnGrade = "B+";
	else if(topElement == 3)
		returnGrade = "B+";
	else if (topElement == 2)
		returnGrade = "C";
	else if (topElement == 2.33)
		returnGrade = "C+";
	else if (topElement == 1)
		returnGrade = "D";
	else if (topElement == 0)
		returnGrade = "F";

	return returnGrade;
}




//double* all_means(double** Data, int dataRows, int dataCols) {
//}
//
//////	 calculate and return mean of all datapoints
//double* initia_k_Means(int k, double* allMeans, int allMeansSize) {
//
//}
// Return Mean of 1st 13 students and index of the array will be cluster number 
//// i-e , value in 0th index will be considered as the mean of cluster 0 ,  
//// value in 1st index will be considered as the mean of cluster 1.
//
//double* Dist(double* allMeans, int allMeansSize, double* clusterMeans, int clusterMeansSize);
//// Find the distance between mean of all datapoint and the mean of each cluster.  
//// Assign closest cluster to each datapoint
//// calculate new mean against each cluster 
//// Return Updated Mean 
//
//bool  Accuracy(double* oldClusterMeans, int oldClusterMeansSize, double* newClusterMeans, int newClusterMeansSize);
//// return True if both means are same otherwise return false 
//
//string Prediction(double newData, double* meansOfClustors, int meansOfClustorsSize);
//// Calculate the distance of upcoming datapoint with the whole cluster means
////  and convert the index of closest cluster mean into Grade and return it.
//











///////////////////////////////These Functions are for my own help.///////////////////////////////////////////

//This function takes semster and an SrNo as arguments and tells wether the 
//Specific semster provided is highest semster for the specific SrNo. (This is to find out the correct<latest> CGPA)
bool isHighestSem(string semster1, int srNo1) {
	bool flag = true;
	for (int j = 0; j < 10; j++) {
		if (semsterArr[srNo1][j] != "" || semsterArr[srNo1][j] != "Unknown") {
			if ((SemGreaterOrNot(semster1, semsterArr[srNo1][j])) == -1) // that means semster1 is greater.
				flag = false;
		}
	}
	return flag;
}


//This function finds out the greater semster of two semsters. (since i had to find the cgpa based on highest semster)
int SemGreaterOrNot(string a, string b) {

	string semsterList[] = { "Fall 2016","Fall 2017","Spring 2017","Fall 2018","Spring 2018", "Spring 2019" }; 	//Least to greatest.
	int num1 = 0, num2 = 0, i;

	for (i = 0; i < 6; i++) {
		if (semsterList[i] == a)
			num1 = i;
		if (semsterList[i] == b)
			num2 = i;
	}

	if (num1 == num2)
		return 0;
	else if (num1 > num2)
		return 1;
	else if (num1 < num2)
		return -1;
}

//This function only collects semsters and store it in a global array for latter use.
void collectSems() {
	string SrNo = "", line, semster;
	ifstream ip("students_dataset.csv", ios::in);
	int i = 0, j = 0, sr, count = 0, l = 0;
	if (!ip.is_open()) std::cout << "error: file open" << '\n';
	getline(ip, line, '\n'); // skipping first line, which is of Titles.

	for (int k = -1; i < 1768; ) {
		getline(ip, SrNo, ','); //index 0
		sr = stoi(SrNo); //Converting SrNo to int.      
		i = sr;
		getline(ip, semster, ',');
		
		if (i == (l + 1)) {
			k = 0;
		}
		else if (i == l && semster != "Unknown") {
			k++;
		}


		if (semster != "Unknown") {
			semsterArr[i][k] = semster;
		}
		l = i;
		getline(ip, semster, '\n');
	}
}

//This function sorts the array given as argument and return the sorted array.
double** SortArr(double **arr, int n){
	int i, j;
	double temp;
	for (i = 0; i < n; ++i){
		for (j = i + 1; j < n; ++j){
			if (arr[i][0] > arr[j][0]){

				//Distance
				temp = arr[i][0];
				arr[i][0] = arr[j][0];
				arr[j][0] = temp;

				//Grade Point
				temp = arr[i][1];
				arr[i][1] = arr[j][1];
				arr[j][1] = temp;

			}
		}
	}
	return arr;
}