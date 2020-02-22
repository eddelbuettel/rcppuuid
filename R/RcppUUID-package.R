#' @title Generating Universally Unique Identificators
#'
#' @description
#' Provides funstion to generating a vector of Universally Unique Identifiers
#' (UUID) version 4. Based on the sole C++ library <https://github.com/r-lyeh-archived/sole>.
#' Used the OpenMP library to improve performance.
#'
#' @name RcppUUID
#' @docType package
#'
#' @useDynLib RcppUUID, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#'
"_PACKAGE"
