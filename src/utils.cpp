/*******************************/
/* utils.cpp */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#include <iostream>
#include <cmath>
#include <string>

#include "utils.h"
#include "metrics.h"

using namespace std;

template float eucl_distance(vector_item<int>&, vector_item<int>&);
template float cs_distance(vector_item<int>&, vector_item<int>&);
template float exchausting_s(dataset<int>&, vector_item<int>&, int);


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


int HC_get_parameters(int argc, char** argv, string& input_file, string& queryset_file, string& output_file, int& k, int& probes, int& M){
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
            case 'p':{ // number of probes parameter
                string par_str(argv[i]);
                if(par_str.compare("-probes")){
                    printf("Error in parameters. Unknown parameter given [%s]. Abort.\n", argv[i]);
                    return -5;
                }

                if(probes != -1){ // num of probes given twice
                    printf("Error in parameters! Number of probes [-probes] is given more than once! Abort.\n");
                    return -2;
                }

                if(!isNumber(argv[i + 1])){ // num of probes is not a number
                    printf("Error in parameters! Number of probes [-probes] given is not a number. Abort\n");
                    return -2;
                }

                probes = atoi(argv[i + 1]);
                if(probes <= 0){ // not positive non-zero number of probes given
                    printf("Error in parameters! Number of probes [-probes] is not a positive non-zero number. Abort\n");
                    return -2;
                }

                break;
            } // end case -d
            case 'M':{ // number of total points to be checked parameter
                if(M != -1){ // M given twice
                    printf("Error in parameters! Number of total points to be checked [-M] is given more than once! Abort.\n");
                    return -2;
                }

                if(!isNumber(argv[i + 1])){ // num of probes is not a number
                    printf("Error in parameters! Number of total points to be checked [-M] given is not a number. Abort\n");
                    return -2;
                }

                M = atoi(argv[i + 1]);
                if(M <= 0){ // not positive non-zero number of M given
                    printf("Error in parameters! Number of total points to be checked [-M] is not a positive non-zero number. Abort\n");
                    return -2;
                }

                break;
            } // end case -M
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

void HC_printValidParameters(){
    cout << "\n*Execute again providing (optionally) the following parameters:" << endl;
    cout << "\t-d inputFile" << endl;
    cout << "\t-q queryFile" << endl;
    cout << "\t-o outputFile" << endl;
    cout << "\t-k K" << endl;
    cout << "\t-probes probes" << endl;
    cout << "\t-M M" << endl;
    cout << "-inputFile: Path to the dataset file" << endl;
    cout << "-queryFule: Path to the query file" << endl;
    cout << "-outputFile: Path to the output file" << endl;
    cout << "-K: Number of hash functions for each hash table, [>=1]" << endl;
    cout << "-probes: Number of neighbouring bucket to be checked, [>=1]" << endl;
    cout << "-M: Number of total points to be checked for a query, [>=1]" << endl;
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

int get_int_len(int num){
    int num_digits = 1; // digits of number
    while(num >= 0){	
		num_digits++;
       	num = num >> 1;
	}

    return num_digits;
}

int get_combinations(int a, int b){
    /* Computes comb(a,b) = a! / (b! * (a - b)!) */
    int diff = a - b;

    return ( get_factorial(a) / ( get_factorial(b) * get_factorial(diff)) );


}

int get_factorial(int num){
    int total = 1;
    for(int i = 2; i <= num; i++){
        total *= i;
    }

    return total;
}

int hamming_dist(int x, int y){
    int x_or = x ^ y; // keep different bits, they will be represented as 1

    int dist = 0; // hamming_distance
    while(x_or > 0){ // check all bits
        if((x_or | 1) == x_or) // if true, means the leftmost bit is 1, hence different
            dist++;
        x_or = x_or >> 1;
    }
    return dist;
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

/* Computes and returns the modulo of the given values a mod b */
long long int my_mod(int a, long int b){
	long long int res = a - ((floor( (long double)a / (long double)b) ) * b); 
    return res;
}

int get_metrics(string& metrics){
    if(metrics.empty()) // no definition, use euclidean
        return 0;

    if(metrics.find("euclidean") != string::npos) // euclidean is defined
        return 1;
    
    if(metrics.find("cosine") != string::npos) // cosine is defined
        return 2;

    return 0; // nothing was defined, use euclidean
}

double get_radius(std::string& radius){
    if(radius.compare(0, 9, "Radius: <")) // check if radius is given
        return -1;

    /* Extract radius */
    int pos1 = radius.find('<');
    int pos2 = radius.find('>');

    /* Keep the part enclosed in <> */
    string temp = radius.substr(pos1 + 1, pos2 - pos1 - 1);
    
    double result = 0.0;
    try{
        result = stod(temp);
    }catch(invalid_argument){
        cout << "Invalid radius was given. Radius won't be used at all!" << endl;
        return 0.0;
    }

    return result;
}

template <class T>
float eucl_distance(vector_item<T>& vec1, vector_item<T>& vec2){
	/* Compute sqrt((Sum((ai - bi)^2))), for all points */

    if(vec1.get_size() != vec2.get_size()){
		cout << "Invalid dimensions of vectors" << endl;
		exit(0);
	}

	float dist = 0.0;

	array<T, D>& arr1 = vec1.get_points();
	array<T, D>& arr2 = vec2.get_points();


	for(unsigned int i = 0; i < arr1.size(); i++)
		dist += pow(arr1[i] - arr2[i], 2);

	dist = sqrt(dist);

	return dist;
}

template <class T>
float cs_distance(vector_item<T>& vec1, vector_item<T>& vec2){
	/* Compute (1 - ((vec1 * vec2) / (||vec1||*||vec2||))) */
 	if(vec1.get_size() != vec2.get_size()){
		cout << "Invalid dimensions" << endl;
		exit(0);
	}

	float dist;
	float euc_dist = 0.0;
	float arr1_norm = 0.0;
	float arr2_norm = 0.0;

	array<T, D>& arr1 = vec1.get_points();
	array<T, D>& arr2 = vec2.get_points();


	for(unsigned int i = 0; i < arr1.size(); i++){
		euc_dist += (arr1[i] * arr2[i]); // vec1 & vec2
		arr1_norm += arr1[i] * arr1[i]; // ||vec1||
		arr2_norm += arr2[i] * arr2[i]; // ||vec2||
	}

	arr1_norm = sqrt(arr1_norm);
	arr2_norm = sqrt(arr2_norm);

	dist = euc_dist / (arr1_norm * arr2_norm);
	dist = 1 - dist;

	return dist;
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
            cout << "  0 Same files as before" << endl;
            cout << "  1 New Dataset" << endl;
            cout << "  2 New Query File" << endl;
            cout << "  3 New Output File" << endl;
            cout << "  4 New Dataset and Query File" << endl;
            cout << "  5 New Dataset and Output File" << endl;
            cout << "  6 New Query and Output File" << endl;
            cout << "  7 Entirely New Files" << endl;
            cout << "  8 I Changed My Mind. I Want To Exit\n" << endl;
            cout << "Note: If you use the same output file name, the previous one will be replaced!\n" << endl;
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
            return 8; // EXIT
        else
            cout << "Invalid input given. Try again." << endl;
    }
}

int in_set(unordered_set<string>& check_set, string& id){
    unordered_set<string>::iterator it;

    it = check_set.find(id);
    if(it == check_set.end()) // id does not exist
        return 0;
    else // id is in set
        return 1; 
}

template <class T>
float exchausting_s(dataset<T>& data_set, vector_item<T>& item, int metric){
    float min_dist = -1.0;
    float cur_dist = 0.0;

    int data_sz = data_set.get_counter();
    if(metric == 1){ // euclidean distance

        /* Check all items in dataset */
        for(int i = 0; i < data_sz; i++){
            vector_item<T>* current_item = data_set.get_item(i);
            cur_dist = eucl_distance(*current_item, item);

            /* keep distance, if smaller than the minimum */
            if(cur_dist <= min_dist || i == 0)
                min_dist = cur_dist;
        }
    }
    else if(metric == 2){ // cosine distance

        /* Check all items in dataset */
        for(int i = 0; i < data_sz; i++){
            vector_item<T>* current_item = data_set.get_item(i);
            cur_dist = cs_distance(*current_item, item);

            /* keep distance, if smaller than the minimum */
            if(cur_dist <= min_dist || i == 0)
                min_dist = cur_dist;
        }
    }
    return min_dist;
}