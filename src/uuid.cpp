#include <Rcpp.h>
#include <uuid.h>

std::mt19937 init_rng() {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size>{};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);
  return generator;
}


//' @title
//' Generate UUID
//'
//' @description
//' Function generates a new Universally Unique Identifier.
//'
//' @param n Number of generated UUIDs.
//'
//' @return Character vector with UUIDs.
//'
//' @export
//'
//' @examples
//' uuid_generate(5)
//'
// [[Rcpp::export]]
Rcpp::StringVector uuid_generate(size_t n = 1) {
  Rcpp::StringVector res = Rcpp::no_init(n);
  // auto uuid_gen = uuids::uuid_system_generator{};
  auto rng = init_rng();
  auto uuid_gen = uuids::uuid_random_generator{rng};
  for (size_t i = 0; i < n; ++i) {
    uuids::uuid guid = uuid_gen();
    res[i] = uuids::to_string(guid);
  }
  return res;
}


//' @title
//' Validate UUID
//'
//' @description
//' Function validate a Universally Unique Identifiers.
//'
//' @param x Character vector with UUIDs.
//'
//' @return Loical vector.
//'
//' @export
//'
//' @examples
//' uuid_validate(uuid_generate(5))
//'
// [[Rcpp::export]]
Rcpp::LogicalVector uuid_validate(Rcpp::StringVector x) {
  size_t n = x.size();
  Rcpp::LogicalVector res = Rcpp::no_init(n);
  for (size_t i = 0; i < n; ++i) {
    if (x[i].empty() || Rcpp::StringVector::is_na(x[i])) {
      res[i] = NA_LOGICAL;
    } else {
      res[i] = uuids::uuid::is_valid_uuid(std::string(x[i]));
    }
  }
  return res;
}
