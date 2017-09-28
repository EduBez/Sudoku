#pragma once
#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace bnu = boost::numeric::ublas;

namespace types {

enum {_= -1};

using SingleCell  = std::vector<int>;
using MatrixCells = bnu::matrix<SingleCell>;

using MatrixRange = bnu::matrix_range<MatrixCells>;
using VectorRange = std::vector<MatrixRange>;

}// EndOf namespace

