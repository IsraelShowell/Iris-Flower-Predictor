/*
Israel Showell
Start Date: 2-9-2024
End Date: 2-13-2024
Project:
Predicting Iris Flowers

Version: 1.0.0

Description:
This program exercises Machine Learning by taking in values for a new Iris flower.
It uses data from the famous iris dataset, and then processes the new input.
Afterwards, it will show how confidient it is in its prediction, and then add the new flower in as the
type it is most sure that it is. 

NOTE:
The readability on this is pretty rough, this is intentional, 
as I was more focused on getting a working prototype than making 
it run as best it can.

I used the knowledge of C++ that I best was familar with to create this, 
but I plan on refactoring this code later on.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>
#include <cmath>

using namespace std;

//Global Variables
const int COL = 5;
const int COL2 = 4;
const long int PI = 3.14159265359;


//Function Prototypes

//Gets the samplemean
void samplemean(string arr[][COL], double numofflower, string type, double arr2[][COL2]);

//Gets the sample variance 
void samplevariance(string arr[][COL], double numofflower, string type, double arr2[][COL2]);

//Gets the standarddeviation
void standarddeviation(double arr2[][COL2]);

//Calculates the density function for my values
void densityfunction(double arr2[][COL2]);

//Calculates the likeihood of my values
void likeihood(double arr1[], double arr2[], double arr3[], double numofflower, double numofflower1, double numofflower2,double records);

//Program reports how confident it is
void confidence(double arr1[], double arr2[], double arr3[]);

int main()
{
    //Build the program using 2D arrays first
    //This will hold the data from the Iris Dataset
    string iris[151][COL];

    //Holds the input from the user, and the sample mean,
    //Sample variance, standard deviation, and the density functions
    double iris_predict[4][COL2];
    
    //Used to gather the data from the csv columns
    string data;
    string data2;
    string data3;
    string data4;
    string data5;

    //Keeps track of how many records we have
    int records = 0;

    //Keeps track of how many types of the flower are in the dataset
    double Iris_setosa = 0;
    double Iris_versicolor = 0;
    double Iris_virginica = 0;

    //Used to track the type of flower in the dataset
    string iris_s = "Iris-setosa";
    string iris_v = "Iris-versicolor";
    string iris_vir = "Iris-virginica";

    //Activates the files we use for this program
    ofstream numberofrecords;
    ifstream irisdataset;

    //Opens the files
    numberofrecords.open("numberofrecords.txt");
    irisdataset.open("OriginalIrisDataset.csv");

    //Checks how many records are in the CSV file.
    if (numberofrecords.is_open()) {
        while (getline(irisdataset, data)) {
            records++;
        }
    }
    //Adds the number of records to the text file.
    //This is for future development to make the code run faster
    numberofrecords << records;

    //Closes the files
    numberofrecords.close();
    irisdataset.close();
    
    //Reopens the CSV file to avoid errors
    irisdataset.open("OriginalIrisDataset.csv");

    //if (irisdataset.is_open()) {
    //Was causing extra errors

    //These loops read in the information from the csv file
    //and loads them into the iris array
        for (int i = 0; i < records; i++) {

            for (int j = 0; j < COL; j++) {
                //Reads the data from the CSV to the 2D array,
                //Which will serve as the "CSV" for the program
                getline(irisdataset, data, ',');

                iris[i][j] = data;

                j++;

                getline(irisdataset, data2, ',');

                iris[i][j] = data2;

                j++;

                getline(irisdataset, data3, ',');

                iris[i][j] = data3;

                j++;

                getline(irisdataset, data4, ',');

                iris[i][j] = data4;

                j++;

                getline(irisdataset, data5, '\n');

                iris[i][j] = data5;
                
                //Counts how many setosa, versicolor, and virginicas there are.
                if (data5 == "Iris-setosa") {
                    Iris_setosa++;
                }
                else if (data5 == "Iris-versicolor") {
                    Iris_versicolor++;
                }
                else if (data5 == "Iris-virginica") {
                    Iris_virginica++;
                }
            }
        }
    //}

    //Closes the file after copying the data
    irisdataset.close();

    //Used to hold the density calculations for each flower type
    double density_setosa[6];
    double density_ver[6];
    double density_vir[6];

    //Made a choice variable for later development 
    int choice = 0;

MENU:  do {

    choice = 0;
    cout << "Welcome to Israel's Iris Flower Predictor!" << endl;
    cout << "Number of detected records from CSV file: " << records << endl;
    cout << "Current number of Setosas: " << Iris_setosa << endl;
    cout << "Current number of Versicolors: " << Iris_versicolor << endl;
    cout << "Current number of Virginicas: " << Iris_virginica << endl;
    cout << "Please enter 1 to run the prediction program, or anything else to end the program!" << endl;
    
    cin >> choice;

    //Just to avoid input errors
    cin.ignore();

    if (choice == 1) {

        //Used for later in the program!
        double results[3];

        cout << "Please enter in the Iris Sepal Length: ";
        cin >> iris_predict[0][0];
        cout << "Please enter in the Iris Sepal Width: ";
        cin >> iris_predict[0][1];
        cout << "Please enter in the Iris Petal Length: ";
        cin >> iris_predict[0][2];
        cout << "Please enter in the Iris Petal Width: ";
        cin >> iris_predict[0][3];
        /*
        This checks the values for Iris setosas in the CSV File
        and stores the density functions in a 1D array for setosas
        */
        samplemean(iris, Iris_setosa, iris_s, iris_predict);

        samplevariance(iris, Iris_setosa, iris_s, iris_predict);

        standarddeviation(iris_predict);

        densityfunction(iris_predict);

        //Sends the data for the densities from the 2D array to the 1D array for simplicity
        for (int i = 0; i < 4; i++) {
            density_setosa[i] = iris_predict[3][i];
        }

        /*
        This checks the values for Iris Versicolor in the CSV File
        and stores the density functions in a 1D array for Versicolors
        */

        samplemean(iris, Iris_versicolor, iris_v, iris_predict);

        samplevariance(iris, Iris_versicolor, iris_v, iris_predict);

        standarddeviation(iris_predict);

        densityfunction(iris_predict);

        //Sends the data for the densities from the 2D array to the 1D array for simplicity
        for (int i = 0; i < 4; i++) {
            density_ver[i] = iris_predict[3][i];
        }

        /*
        This checks the values for Iris Virginicas in the CSV File
        and stores the density functions in a 1D array for virginicas
        */

        samplemean(iris, Iris_virginica, iris_vir, iris_predict);

        samplevariance(iris, Iris_virginica, iris_vir, iris_predict);

        standarddeviation(iris_predict);

        densityfunction(iris_predict);

        //Sends the data for the densities from the 2D array to the 1D array for simplicity
        for (int i = 0; i < 4; i++) {
            density_vir[i] = iris_predict[3][i];
        }

        //This takes the 1D arrays and sends them to the likeihood function
        //Where it will determine the likeihood of a function
        likeihood(density_setosa, density_ver, density_vir, Iris_setosa, Iris_versicolor, Iris_virginica, records);

        //This takes the 1D arrays and sends them to the confidence function
        //Where it will determine the likeihood of a function
        confidence(density_setosa, density_ver, density_vir);

        //Puts the confidence values in a secondary 1D array to finally send the output to the user
        results[0] = density_setosa[5];
        results[1] = density_ver[5];
        results[2] = density_vir[5];

        //Basic logic to check which flower type is most likely to
        //be the correct answer
        if (results[0] >= results[1] && results[0] >= results[2]) {
            cout << "The program has generated these results: " << endl;

            cout << results[0] << " is the how condifdent the program is that your entered flower is a Setosa." << endl;
            cout << results[1] << " is the how condifdent the program is that your entered flower is a Versicolor." << endl;
            cout << results[2] << " is the how condifdent the program is that your entered flower is a Virginica." << endl;

            cout << "Thus, your flower is most likely a Setosa!" << endl;
        }
        else if (results[1] >= results[0] && results[1] >= results[2]) {
            cout << "The program has generated these results: " << endl;

            cout << results[0] << " is the how condifdent the program is that your entered flower is a Setosa." << endl;
            cout << results[1] << " is the how condifdent the program is that your entered flower is a Versicolor." << endl;
            cout << results[2] << " is the how condifdent the program is that your entered flower is a Virginica." << endl;

            cout << "Thus, your flower is most likely a Versicolor!" << endl;
        }
        else {
            cout << "The program has generated these results: " << endl;

            cout << results[0] << " is the how condifdent the program is that your entered flower is a Setosa." << endl;
            cout << results[1] << " is the how condifdent the program is that your entered flower is a Versicolor." << endl;
            cout << results[2] << " is the how condifdent the program is that your entered flower is a Virginica." << endl;

            cout << "Thus, your flower is most likely a Virginica!" << endl;
        }

        //Adds an extra line to allow for user readability
        cout << endl;
        goto MENU;
    }
    

} while (choice == 1);

    /*Tests the output
    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < COL; j++) {
            cout << iris[i][j] << " ";
        }
        cout<<endl;
    }*/

    
    cout << "Have a great day!" << endl;

    //Something my computer likes to have
    system("PAUSE");
}

//Calculates the sample mean for 
void samplemean(string arr[][COL], double numofflower, string type, double arr1[][COL2]) {
    double spmean = 0;

    double spmean2 = 0;

    double spmean3 = 0;

    double spmean4 = 0;
    
    double sum = 0;

    double sum2 = 0;

    double sum3 = 0;

    double sum4 = 0;

    for (int i = 0; i < 151; i++) {
        if (arr[i][4] == type) {
            sum += stod(arr[i][0]);
            
        }
    }
 

    for (int i = 0; i < 151; i++) {
        if (arr[i][4] == type) {
            sum2 += stod(arr[i][1]);
        }
    }

    for (int i = 0; i < 151; i++) {
        if (arr[i][4] == type) {
            sum3 += stod(arr[i][2]);
        }
    }

    for (int i = 0; i < 151; i++) {
        if (arr[i][4] == type) {
            sum4 += stod(arr[i][3]);
        }
    }

    spmean = (1.0 / numofflower) * (sum);
    spmean2 = (1.0 / numofflower) * (sum2);
    spmean3 = (1.0 / numofflower) * (sum3);
    spmean4 = (1.0 / numofflower) * (sum4);
    cout << sum << endl;
    cout << spmean << endl;

    arr1[1][0] = spmean;
    arr1[1][1] = spmean;
    arr1[1][2] = spmean;
    arr1[1][3] = spmean;

}

void samplevariance(string arr[][COL], double numofflower, string type, double arr1[][COL2]) {

    double variance = 0;
    double sum = 0;

    double variance2 = 0;
    double sum2 = 0;

    double variance3 = 0;
    double sum3 = 0;

    double variance4 = 0;
    double sum4 = 0;

    for (int i = 0; i < 151; i++) {
        if (arr[i][4] == type) {
            sum += pow((stod(arr[i][0]) - arr1[1][0]), 2);
        }
    }

    for (int i = 0; i < 151; i++) {
        if (arr[i][4] == type) {
            sum2 += pow((stod(arr[i][1]) - arr1[1][1]), 2);
        }
    }

    for (int i = 0; i < 151; i++) {
        if (arr[i][4] == type) {
            sum3 += pow((stod(arr[i][2]) - arr1[1][2]), 2);
        }
    }

    for (int i = 0; i < 151; i++) {
        if (arr[i][4] == type) {
            sum4 += pow((stod(arr[i][3]) - arr1[1][3]), 2);
        }
    }

    variance = (1.0 / (numofflower - 1)) * sum;

    cout << variance << endl;

    variance2 = (1.0 / (numofflower - 1)) * sum2;

    variance3 = (1.0 / (numofflower - 1)) * sum3;

    variance4 = (1.0 / (numofflower - 1)) * sum4;
    
    arr1[2][0] = variance;
    arr1[2][1] = variance2;
    arr1[2][2] = variance3;
    arr1[2][3] = variance4;

}

void standarddeviation(double arr1[][COL2]) {

    double stddev = sqrt(arr1[2][0]);

    double stddev2 = sqrt(arr1[2][1]);

    double stddev3 = sqrt(arr1[2][2]);

    double stddev4 = sqrt(arr1[2][3]);


    arr1[3][0] = stddev;

    cout << stddev << endl;

    arr1[3][1] = stddev2;
    
    arr1[3][2] = stddev3;
        
    arr1[3][3] = stddev4;

}

void densityfunction(double arr1[][COL2]) {

    double densityf = 0;

    double densityf2 = 0;

    double densityf3 = 0;

    double densityf4 = 0;

    densityf = pow((1.0 / (sqrt(2.0 * PI) * arr1[3][0])), exp(-1.0 * pow((arr1[0][0] - arr1[1][0]), 2.0) / (2.0 * pow(arr1[1][0], 2))));

    densityf2 = pow((1.0 / (sqrt(2.0 * PI) * arr1[3][1])), exp(-1.0 * pow((arr1[0][1] - arr1[1][1]), 2.0) / (2.0 * pow(arr1[1][1], 2))));

    densityf3 = pow((1.0 / (sqrt(2.0 * PI) * arr1[3][2])), exp(-1.0 * pow((arr1[0][2] - arr1[1][2]), 2.0) / (2.0 * pow(arr1[1][2], 2))));

    densityf4 = pow((1.0 / (sqrt(2.0 * PI) * arr1[3][3])), exp(-1.0 * pow((arr1[0][3] - arr1[1][3]), 2.0) / (2.0 * pow(arr1[1][3], 2))));

    arr1[3][0] = densityf;

    arr1[3][1] = densityf2;

    arr1[3][2] = densityf3;

    arr1[3][3] = densityf4;


}


void likeihood(double arr[], double arr2[], double arr3[], double setosa, double ver, double vir,double records) {

    //Likeihood of Setosa will be stored at the 5th spot in the array 
    arr[4] = arr[0] * arr[1] * arr[2] * arr[3] * (setosa / records);
    /*
       Debugging Statements
    cout << "Like: " << arr[0] << endl;
    cout << "Like: " << arr[1] << endl;
    cout << "Like: " << arr[2] << endl;
    cout << "Like: " << arr[3] << endl;
    cout << "Like: " << arr[4] << endl;
    
    */

    //Likeihood of Setosa will be stored at the 5th spot in the array
    arr2[4] = arr2[0] * arr2[1] * arr2[2] * arr2[3] * (ver / records);

    //Likeihood of Setosa will be stored at the 5th spot in the array
    arr3[4] = arr3[0] * arr3[1] * arr3[2] * arr3[3] * (vir / records);
    
}

void confidence(double arr[], double arr2[], double arr3[]) {

    //Probabiltes of Setosa will be stored at the end of the array
    arr[5] = arr[4]/ (arr[4] + arr2[4] + arr3[4]);

    //Likeihood of Setosa will be stored at the end of the array
    arr2[5] = arr2[4] / (arr2[4] + arr[4] + arr3[4]);

    //Likeihood of Setosa will be stored at the end of the array
    arr3[5] = arr3[4] / (arr3[4] + arr2[4] + arr[4]);


}
