#include <iostream>

double count(double FirtsExamScore, double SecondExamScore) 
{
    double FirstExamScorePercent = (FirtsExamScore * 0.2);
    double SecondExamScorePrecent = (SecondExamScore * 0.2);
    double TotalScore = FirstExamScorePercent + SecondExamScorePrecent;
    return ( (85  -  TotalScore) * 100 ) / 60;
}

int main() 
{
    double FirtsExamScore{}, SecondExamScore{};

    std::cout << "Please input first exam score" << std::endl;
    std::cin >> FirtsExamScore;
    
    std::cout << "Please input second exam score" << std::endl;
    std::cin >> SecondExamScore;

    std::cout << "To pass second pool, you need to score >> " << count(FirtsExamScore, SecondExamScore) <<  " point" << std::endl;
    
    return 0;
}