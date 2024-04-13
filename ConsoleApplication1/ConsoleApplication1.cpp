// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

class Neuron {
private:
    std::vector<std::vector<float>> weights;
    std::vector<float> output;
    std::string typeOfNormalisation;
    
    int bins;
    

public:
    Neuron(int Input, const std::string& typeOfNormalisation, int Bins, const std::vector<std::vector<float>>& weight)
        : typeOfNormalisation(typeOfNormalisation), bins(Bins) {
        if (weights.empty()) {
            for (int i = 0; i < bins; ++i) {
                std::vector<float> weightsNeur;
            
                for (int j = 0; j < Input; ++j) {
                    float w = static_cast<float>(std::rand()) / RAND_MAX * 2 - 1;
                    weightsNeur.push_back(w);
                
                }
               weights.push_back(weightsNeur); 
            
            }

        }
        else {
            //весов нету 
        }
    }
    int GetBins() {
        return bins;
    }
    void NormalisationRELU(std::vector<float>& x) const {
        for (auto& el : x) {
            el = std::max(0.0f, el);
        }
    }

    std::vector<float> softmax(const std::vector<float>& x) const {
        std::vector<float> result;
        float sum_exp = 0.0f;

        for (float val : x) {
            float exp_val = std::exp(val);
            result.push_back(exp_val);
            sum_exp += exp_val;
        }

        for (float& res : result) {
            res /= sum_exp;
        }

        return result;
    }


    std::vector<float> GetOutPut() const {
        return output;
    }

    std::vector<std::vector<float>> GetWeights() const {
        return weights;
    }

    
    std::vector<float> GetAnswer(vector<float>&input ) {
        int CountOfoperations = 0;
        output.clear();
        for (int i = 0; i < bins; ++i) {
            
            float sum = 0.0f;
            for (int j = 0; j < input.size(); ++j) {
                
                sum += input[j] * weights[i][j];

                //cout << weights[i][j] << "\n";
                CountOfoperations++;
               // cout << "операция " << CountOfoperations << "\n";

            }
            
            output.push_back(sum);
        }

        if (typeOfNormalisation == "RELU") {
            NormalisationRELU(output);
        }
        else if (typeOfNormalisation == "SOFTMAX") {
            output = softmax(output);
        }

        return output;
        }
        
    
    
};

struct Flower {
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    std::string species;
};





int main()
{

    string arrayOfOptions[3] = { "etosa", "ersicolor", "irginica"};
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    cout << "Hello World!\n\n\n\n\n ";

    std::vector<std::vector<std::vector<float>>> BestWeights;
    float BestMSE = 0;

    std::ifstream file("data.txt");

    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл." << std::endl;
        return 1;
    }

    std::vector<Flower> flowers;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Flower flower;
        char comma;
        if (iss >> flower.sepal_length >> comma >> flower.sepal_width >> comma >>
            flower.petal_length >> comma >> flower.petal_width >> comma >>
            flower.species) {
            flowers.push_back(flower);
        }
        else {
            std::cout << "Ошибка чтения строки: " << line << std::endl;
        }
    }

    file.close();


    
    for (const auto& flower : flowers) {
        std::cout << "Sepal Length: " << flower.sepal_length << ", "
            << "Sepal Width: " << flower.sepal_width << ", "
            << "Petal Length: " << flower.petal_length << ", "
            << "Petal Width: " << flower.petal_width << ", "
            << "Species: " << flower.species << std::endl;
    }
    cout << "flowers size" << flowers.size() << endl;
    cout << "Type operation Learning/Get Answer \n";
    string operation;
    cin >> operation;
    if (operation == "Learning" || operation == "1")
    {
        std::vector<vector<float>> undefinedVector;
        Neuron* firstLayer = new Neuron(4, "RELU", 10, undefinedVector);
        Neuron* LastLayer = new Neuron(firstLayer->GetBins(),"SOFTMAX", 3, undefinedVector);
        for (int numberofLearnings = 0; numberofLearnings < 100; ++numberofLearnings) {
            float crossEntropy =0;
            float error = 0;
            for (int i = 0; i < flowers.size(); ++i)

            {
                float PredValue = -1.0f; // Max
                float totalDelta;
                int rightIndexOfSpice = -1;
                int predIndex = -1;
                vector<float> Data = { flowers[i].petal_length, flowers[i].petal_width,flowers[i].sepal_length,flowers[i].sepal_width };
                vector<float> pred = firstLayer->GetAnswer(Data);
                vector<float>Neurons = LastLayer->GetAnswer(pred);

                for (int j = 0; j < arrayOfOptions->size(); ++j) {
                    if (arrayOfOptions[j] == flowers[i].species) {
                        rightIndexOfSpice = j;
                        //cout << arrayOfOptions[j] << endl;
                    }
                }

                for (int j = 0; j < LastLayer->GetOutPut().size(); ++j) {
                    if (LastLayer->GetOutPut()[j] > PredValue) {
                        PredValue = LastLayer->GetOutPut()[j];
                        predIndex = j;
                        
                    }

                }
               
                

               
               
               error += pow(Neurons[predIndex] - Neurons[rightIndexOfSpice], 2);
               
              
               // cout << firstLayer->GetWeights()[0].size() << "\t" << LastLayer->GetWeights()[0].size() << "\n";
                //cout << firstLayer->GetWeights().size() << "\t" << LastLayer->GetWeights().size() << "\n";








            }
                cout << "error: "<< error << endl;
        }
            while (true) {
                cout << "enter data \n";
                string inputString;
                cin >> inputString;
                std::vector<float> Data = { 5.4,3.4,1.5,0.4 };
                cout << "Enter right flower \n";
                string rightFlower = "etosa";
                //cin >> rightFlower;
                std::stringstream ss(inputString);
                std::string token;




                for (const auto element : Data) {
                    std::cout << element << "  ";
                }

                


            }

                delete firstLayer;
                delete LastLayer;
    return 0;

  }
   
}


