#include "wrap.h"
#include <boost/uuid.hpp>
#include <boost/uuid/time_generator.hpp> // gets v1, v6, v7
#include <boost/uuid/uuid_io.hpp>

#include <Rcpp.h>

//' @title Generate UUIDs Version 7
//'
//' @description
//' This function generates time-based uuids using operating system provided entropy. Note
//' that this requires Boost 1.86 or later.
//'
//' @param n Number of generated UUIDs.
//' @return Character vector with UUIDs generated under specification v7.
//'
//' @references
//' <https://www.boost.org/doc/libs/release/libs/uuid/>
//'
//' @examples
//' # generate random UUIDs
//' uuid_generate_time(2)
//'
//' @export
// [[Rcpp::export(rng=false)]]
Rcpp::StringVector uuid_generate_time(size_t n = 1)  {
    boost::uuids::time_generator_v7 gen;
    std::vector<std::string> res(n);
    for (size_t i = 0; i < n; i++) {
        res[i] = boost::uuids::to_string(gen());
    }
    return Rcpp::wrap(res);
}
