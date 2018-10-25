/*******************************/
/* utils.cpp */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#include <iostream>
#include <cmath>
#include "utils.h"
#include "dataset.h"

using namespace std;

/*  All functions implementions that are defined in utils.h */

int get_parameters(int argc, char** argv, string& input_file, string& queryset_file, string& output_file, int& k, int& L){
    for (int i = 1; i < argc; i += 2){ // get all parameters
        char par; // parameter given
            
        par = argv[i][1]; // get parameter
        switch(par){
            case 'd':{ // input file provided
                if(!input_file.empty()){ // input file(dataset) is provided twice
                    printf("Error in parameters! Input file [-d] is given more than once! Abort.\n");
                    return -2;
                }

                input_file = argv[i + 1];
                break;
            } // end case -d
            case 'q':{ // query file parameter
                if(!queryset_file.empty()){ // port given twice
                    printf("Error in parameters! Query file [-q] is given more than once! Abort.\n");
                    return -2;
                }
                
                queryset_file = argv[i + 1];
                break;
            } // end case -q
            case 'o':{ // output file parameter
                if(!output_file.empty()){ // port given twice
                    printf("Error in parameters! Output file [-o] is given more than once! Abort.\n");
                    return -2;
                }

                output_file = argv[i + 1];
                break;
            } // end case -o
            case 'k':{ // number of hash functions parameter
                if(k != -1){ // num of hash functions given twice
                    printf("Error in parameters! Number of hash functions [-k] is given more than once! Abort.\n");
                    return -2;
                }

                if(!isNumber(argv[i + 1])){ // num of hash functions is not a number
                    printf("Error in parameters! Number of hash functions [-k] given is not a number. Abort\n");
                    return -2;
                }

                k = atoi(argv[i + 1]);
                if(k <= 0){ // not positive non-zero number of threads given
                    printf("Error in parameters! Number of hash functions [-k] is not a positive non-zero number. Abort\n");
                    return -2;
                }

                break;
            } // end case -k
            case 'L':{ // number of hash tables to be created parameter
                if(L != -1){ // num of hash tables given twice
                    printf("Error in parameters! Number of hash tables [-L] is given more than once! Abort.\n");
                    return -2;
                }

                if(!isNumber(argv[i + 1])){ // num of hash tables is not a number
                    printf("Error in parameters! Number of hash tables [-L] given is not a number. Abort\n");
                    return -2;
                }

                L = atoi(argv[i + 1]);
                if(L <= 0){ // not positive non-zero number of threads given
                    printf("Error in parameters! Number of hash functions [-L] is not a positive non-zero number. Abort\n");
                    return -2;
                }

                break;
            } // end case -d
            default:{
                printf("Error in parameters. Unknown parameter given [%s]. Abort.\n", argv[i]);
                return -5;
            }
        } // end switch
    } // end for
    return 0;
}

void printValidParameters(){
    cout << "\n*Execute again providing (optionally) the following parameters:" << endl;
    cout << "\t-d inputFile" << endl;
    cout << "\t-q queryFile" << endl;
    cout << "\t-o outputFile" << endl;
    cout << "\t-k K" << endl;
    cout << "\t-L L" << endl;
    cout << "-inputFile: Path to the dataset file" << endl;
    cout << "-queryFule: Path to the query file" << endl;
    cout << "-outputFile: Path to the output file" << endl;
    cout << "-K: Number of hash functions for each hash table, [>=1]" << endl;
    cout << "-L: Number of hash tables, [>=1]" << endl;
}


int isNumber(char* str){
    char* temp = str;
    char ch = *temp;
    if(ch == '-') // negative number is provided
        ch = *(++temp);
    while(ch != '\0'){
        if(ch >= 48 && ch <= 57){
            ch = *(++temp);
        }
        else{
            return 0;
        }
    }
    return 1;
}


/* Compute inner product of two vectors */
float vector_product(std::array<float, D>& vec1, std::array<int, D>& vec2){
    float product = 0.0;

    for(unsigned int i = 0; i < D; i++)
        product += vec1[i] * vec2[i];

    return product;
}

long long int h_concantenate(vector<int>& hs){
    /* Creates a string with the concatenated ints, and then it is */
    /* returned converted back to int.                             */

    string res_str("");
    for(unsigned int i = 0; i < hs.size(); i++)
        res_str += to_string(abs(hs[i]));


    return stoll(res_str);
}

/* Computes and returns the modulo of the ginen values a mod b */
long long int my_mod(int a, long int b){
	long long int res = a - ((floor( (long double)a / (long double)b) ) * b); 
    return res;
}

int get_metrics(string& metrics){
    if(metrics.empty()) // no definition -> use euclidean only
        return 0;

    if(metrics.find("euclidean") != string::npos) // euclidean is defined
        return 1;
    
    if(metrics.find("cosine") != string::npos) // cosine is defined
        return 2;

    return 0;
}

float get_radius(std::string& radius){
    if(radius.compare(0, 9, "Radius: <")) // check if radius is given
        return -1;

    int pos1 = radius.find('<');
    int pos2 = radius.find('>');

    string temp = radius.substr(pos1 + 1, pos2 - pos1 - 1);

    float result = stof(temp);

    return result;
}

int new_execution(ifstream& input, ifstream& query, ofstream& output){
    string choice;

    while(1){
        cout << "Would you like to continue(y or n): ";
        fflush(stdout);
        
        getline(cin, choice);
        fflush(stdin);

        if(!choice.compare("y") || !choice.compare("Y") || !choice.compare("yes") ){
            cout << "Please choose one of the following(select number):" << endl;
            cout << "0 Same files as before" << endl;
            cout << "1 New Dataset" << endl;
            cout << "2 New Query File" << endl;
            cout << "3 New Output File" << endl;
            cout << "4 New Dataset and Query File" << endl;
            cout << "5 New Dataset and Output File" << endl;
            cout << "6 New Query and Output File" << endl;
            cout << "7 Entirely New Files" << endl;
            cout << "8 I Changed My Mind. I Want To Exit\n" << endl;
            cout << "My choice: ";

            fflush(stdout);
            getline(cin, choice);
            fflush(stdin);

            if(!choice.compare("0")) // Use same files
                return 0;
            else if(!choice.compare("1")){ // diff input{
                input.close();
                return 1;
            }
            else if(!choice.compare("2")){ // diff query
                query.close();
                return 2;
            }
            else if(!choice.compare("3")){ // diff out
                output.close();
                return 3;
            }
            else if(!choice.compare("4")){ // diff in+q
                input.close();
                query.close();
                return 4;
            }
            else if(!choice.compare("5")){ // diff in+out
                input.close();
                output.close();
                return 5;
            }
            else if(!choice.compare("6")){ // diff q+out
                query.close();
                output.close();
                return 6;
            }
            else if(!choice.compare("7")){ // diff ALL
                input.close();
                query.close();
                output.close();
                return 7;
            }
            else if(!choice.compare("8")) // EXIT
                return 8;
            else
                cout << "Invalid input given. Try again." << endl;
        }
        if(!choice.compare("n") || !choice.compare("N") || !choice.compare("no") )
            return 8;
        else
            cout << "Invalid input given. Try again." << endl;
    }
}