#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

namespace bnu = boost::numeric::ublas;

namespace types {

enum placeholder {_ = -1};

using Lines  = std::vector<std::vector<int>>;
using Cell   = std::pair<int, int>;
using Matrix = bnu::matrix<int>;

}// EndOf namespace
