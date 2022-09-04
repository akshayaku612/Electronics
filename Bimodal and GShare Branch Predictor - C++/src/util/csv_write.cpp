#include "csv_write.h"
#include <fstream>

void write_csv(unsigned long int m,unsigned long int n,double mispredictionRate) {
    std::ofstream myFile("test_validation_results/gshare_predictor_results/perl_results.csv",std::ios::app);
    myFile <<m<<","<<n<<","<<mispredictionRate<<"\n";
}
