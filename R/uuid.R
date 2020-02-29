#' @title
#' Generate UUIDs
#'
#' @description
#' Function generates a set of Universally Unique Identifiers.
#' Supported version 4 and 5 UUIDs.
#'
#' @param n Number of generated UUIDs.
#' @param x Character vector.
#'
#' @return Character vector with UUIDs.
#'
#' @name uuid_generate
#'
#' @examples
#' # generate random UUIDs
#' uuid_generate_random(2)
#' # generate nil UUIDs
#' uuid_generate_nil(2)
#' # generate name UUIDs
#' uuid_generate_name(c("one", "two"))
#'
NULL
