#ifndef TypedefsH
    #define TypedefsH

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

namespace bnu = boost::numeric::ublas;

namespace types {

enum placeholder {_ = -1};
enum class DifficultyLevel {Easy, Medium, Hard};

using Lines  = std::vector<std::vector<int>>;
using Cell   = std::pair<int, int>;
using Matrix = bnu::matrix<int>;

}// EndOf namespace
#endif

