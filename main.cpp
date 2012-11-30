/// main.cpp
/// this example shows how to use the C++ particle filter template

# include <iostream>
# include <fstream>
# include <cmath>
# include "pfilter.h"
# include "ran_generator.h"

const long double PI = 3.14159265359;

const long double alpha = 0.91;
const long double beta = 1.0;

typedef long double statetype; ///< variable type for state space
typedef long double obsvtype;  ///< variable type for observation space

long double f(statetype x1, statetype x2){ ///< pdf f(x1|x2)
    return exp(-0.5*pow((x1-alpha*x2),2));
}

long double g(statetype x, obsvtype y){ ///< pdf g(x|y)
    return 1/exp(x/2)*exp(-0.5*pow(y/beta/exp(x/2),2));
}

long double q(statetype x1, statetype x2, obsvtype y){ ///< pdf q(x1|x2,y)
    return exp(-0.5*pow((x1-alpha*x2),2));
}

long double q_sam(statetype x, obsvtype y){ ///< sampler, output ~ q(output|x,y)
    std::normal_distribution<long double> distribution(0,1);
    return distribution(ran_gen::getInstance().get_gen())+alpha*x;
}

int main(){
    pfilter<statetype,obsvtype> A(f,g,q,q_sam);
    std::ifstream in("data_y");
    std::ofstream on("data_xhat");
    in>>A;
    A.initialize(200);
    A.iterate();
    on<<A;
    return 0;
}
