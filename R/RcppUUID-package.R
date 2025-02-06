#' @title Generating Universally Unique Identificators
#'
#' @description
#' Provides functions to generating a vector of Universally Unique Identifiers (UUID)
#' using the implementation from the Boost C++ library. Supports random (version 4), name (version 5)
#' and time-based (version 7) UUIDs. UUIDs generation is parallelized by OpenMP.
#'
#' @name RcppUUID
#' @docType package
#'
#' @useDynLib RcppUUID, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#'
"_PACKAGE"
