#ifndef SIM_BRANCHPREDICTOR_H
#define SIM_BRANCHPREDICTOR_H

#include <string>

class BranchPredictor {
private:
    unsigned int globalBHR=0;
    int* predictionTable;

    std::string branchPredictorType;
    double numOfTotalPredictions=0.0;
    double numOfMispredictions=0.0;
    double mispredictionRate=0.0;

public:
    explicit BranchPredictor(unsigned long int m);
    unsigned long int generateIndex(unsigned long int m,unsigned long int n,unsigned long int PC);
    bool predictBranchOutcome(unsigned long int index);
    void updateBranchOutcome(unsigned long int index,char actualOutcome);
    void updateGlobalBHR(char actualOutcome, unsigned int n);
    void checkPredictionOutcome(bool predictedOutcome,char actualOutcome);
    void displayResults(unsigned int m,unsigned int n);

    void setBranchPredictorType(const std::string &branchPredictorType);
};


#endif
