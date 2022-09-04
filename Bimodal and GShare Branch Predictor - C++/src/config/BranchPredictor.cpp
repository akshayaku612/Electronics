#include "BranchPredictor.h"
#include "../util/csv_write.h"

#include <cmath>
#include <stdio.h>

BranchPredictor::BranchPredictor(unsigned long int m) {
    int length=(int)pow(2, m);
    predictionTable=new int[length];
    int *end= predictionTable+length;
    for (int *p=predictionTable; p != end; ++p) {
        *p=2;
    }
}

unsigned long int BranchPredictor::generateIndex(unsigned long int m,unsigned long int n,unsigned long int PC) {
    unsigned long int index,a;
    index=PC>>2;
    if (n!=0){
        a=((1 << (m-n)) - 1) & (index >> 0);
        globalBHR= (((1 << n) - 1) & (globalBHR >> 0));
        index= globalBHR^(index>>(m-n));
        index= (((1 << n) - 1) & (index >> 0));
        index=(index<<(m-n))|a;
    }
    else{
        index= (((1 << m) - 1) & (index >> 0));
    }
    return index;
}

bool BranchPredictor::predictBranchOutcome(unsigned long int index){
    int counter=*(predictionTable+index);
    if (counter>=2) return true;
    else return false;
}

void BranchPredictor::updateBranchOutcome(unsigned long int index,char actualOutcome){
    int *value=predictionTable+index;
    if ((actualOutcome=='t')&& (*value != 3)) {
        (*value)++;
    }
    if ((actualOutcome=='n')&& (*value != 0)) {
        (*value)--;
    }
}

void BranchPredictor::updateGlobalBHR(char actualOutcome, unsigned int n){
    if (actualOutcome=='t') {
        globalBHR=globalBHR>>1;
        globalBHR |= 1 << (n-1);
    }
    else {
        globalBHR=globalBHR>>1;
        globalBHR &= ~(1 << (n-1));
    }
}

void BranchPredictor::checkPredictionOutcome(bool predictedOutcome,char actualOutcome){
    if ((predictedOutcome && actualOutcome == 't')||(!predictedOutcome && actualOutcome=='n')){
        numOfTotalPredictions++;
    }
    else{
        numOfTotalPredictions++;
        numOfMispredictions++;
    }
}

void BranchPredictor::displayResults(unsigned int m,unsigned int n){
    int *end= predictionTable+(int)pow(2,m);
    unsigned int i=0;
    mispredictionRate= (numOfMispredictions / numOfTotalPredictions) * 100.0;

    printf("OUTPUT\n");
    fflush(stdout);
    printf(" number of predictions:       %.0lf\n", numOfTotalPredictions);
    fflush(stdout);
    printf(" number of mispredictions:    %.0lf\n",numOfMispredictions);
    fflush(stdout);
    printf(" misprediction rate:          %.2lf%%\n",mispredictionRate);
    fflush(stdout);
    printf("FINAL %s CONTENTS\n",branchPredictorType.c_str());
    fflush(stdout);
    for (int *p=predictionTable; p != end; ++p) {
        printf("%d  %d\n",i,*p);
        ++i;
    }
   // write_csv(m,n, mispredictionRate);
}

void BranchPredictor::setBranchPredictorType(const std::string &branchPredictorType) {
    BranchPredictor::branchPredictorType = branchPredictorType;
}
