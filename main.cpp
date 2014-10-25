#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <gmpxx.h>
#include <vector>
#include <iostream>

using namespace std;

int k_chi = 10;

void print(mpz_t dividend, mpz_t divisor,  int d) {
    mpz_t quotient, quotient_to_print;
    mpz_t remainder;
    mpz_init(quotient);
    mpz_init(quotient_to_print);
    mpz_init(remainder);

    mpz_tdiv_qr(quotient, remainder, dividend, divisor);
    gmp_printf("%Zd", quotient);
    if(mpz_cmp_si(remainder,0) != 0){
        gmp_printf(".");
        mpz_abs(divisor,divisor);
        mpz_abs(remainder,remainder);
        int i;

        for(i=0;i<d && mpz_cmp_si(remainder,0) != 0;i++){
            mpz_mul_ui(remainder,remainder,10);  
            mpz_tdiv_qr(quotient, remainder, remainder, divisor);
            if( i == d-1 && mpz_cmp_si(quotient,0) == 0){
                break;
            }else{
                gmp_printf("%Zd", quotient);
            }
        }
    }
    gmp_printf("\n");
    return;
}

void init_chi(mpq_class ranges_chi[], mpq_class probabilities_chi[]){
    int i;
    mpz_class tmp;

    for (i = 0; i < k_chi; i++)
    {
        // liczymy licznik - i^2
        tmp = pow(i+1, 2);
        ranges_chi[i].get_num() = tmp;

        // licznik = ai - a(i-1)
        if (i == 0){
            tmp =  1;
        }else{
            tmp = ranges_chi[i].get_num() - ranges_chi[i-1].get_num();
        }
        probabilities_chi[i].get_num() = tmp;

        tmp =  100;
        ranges_chi[i].get_den() = tmp;
        probabilities_chi[i].get_den() = tmp;
    }
 

}

int calc_chi(mpq_class Y_chi[], mpq_class probabilities_chi[], int n, int d){
    mpz_class tmp_z; 
    mpq_class result, tmp_q, npi;


    for(int i=0;i < k_chi; i++){
        npi = n*probabilities_chi[i];
        tmp_q = Y_chi[i] - npi;
        tmp_q *= tmp_q;
        tmp_q /= npi;
        result += tmp_q;
    }

    print(result.get_num().get_mpz_t(), result.get_den().get_mpz_t(), d);
}

void process(int d){
    mpq_class in;
    mpq_class ranges_chi[k_chi];
    mpq_class probabilities_chi[k_chi];
    mpq_class Y_chi[k_chi];

    init_chi(ranges_chi, probabilities_chi);

    int n = 0;
    int i;

    while (gmp_scanf("%Zd/%Zd", in.get_num().get_mpz_t(), in.get_den().get_mpz_t()) > 0) {
        n++;

        // assignment to specific ranges for X^2
        for (i = 0; i < k_chi; i++)
        {
            if (in < ranges_chi[i] )
            {
                Y_chi[i] += 1;
                break;
            }
        }
 
    }

    calc_chi(Y_chi, probabilities_chi, n, d);

}

int main (int argc, char* argv[])
{
    if(argc == 2){ 
        int d = atoi(argv[1]);
        process(d);
    }else{
        printf("Wrong arguments count");
    }

    return 0;
}
