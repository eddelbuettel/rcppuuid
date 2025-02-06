
## RcppUUID -- Universally Unique Identifiers (UUIDs) versions 4, 5 and 7

[![CI](https://github.com/eddelbuettel/rcppuuid/workflows/ci/badge.svg)](https://github.com/eddelbuettel/rcppuuid/actions?query=workflow%3Aci)
[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![CRAN Status](https://www.r-pkg.org/badges/version/RcppUUID)](https://cran.r-project.org/package=RcppUUID)
[![r-universe](https://eddelbuettel.r-universe.dev/badges/RcppUUID)](https://eddelbuettel.r-universe.dev/rcppuuid)
[![Dependencies](https://tinyverse.netlify.app/badge/RcppUUID)](https://cran.r-project.org/package=RcppUUID)
[![Downloads](https://cranlogs.r-pkg.org/badges/RcppUUID?color=brightgreen)](https://www.r-pkg.org:443/pkg/RcppUUID)
[![Last Commit](https://img.shields.io/github/last-commit/eddelbuettel/rcppuuid)](https://github.com/eddelbuettel/rcppuuid)


### Usage

#### Generate version 4 UUIDs

Generate a single random UUID:

``` r
RcppUUID::uuid_generate_random()
#> [1] "95a0b90b-46bc-4e16-b41e-cb04bb53aa71"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate_random(5)
#> [1] "2d5caacd-7123-4072-b66f-74874f0424d9" "3c4f1e13-50af-46ab-a32a-f17cb1842875"
#> [3] "b0c0075d-f1fb-476c-9d27-0dd07c63ddef" "e6992ca8-7b32-45ab-9fa2-e11690c11c35"
#> [5] "4d9fce08-a71d-402f-9fa5-9e38fa136abb"
```

Check uniqueness for the uuids:

``` r
unique_n <- function(x) length(unique(x))
n <- 1000000
unique_n(RcppUUID::uuid_generate_random(n)) == n
#> [1] TRUE
```

Benchmarking:

Single UUID:

``` r
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE),
  RcppUUID = RcppUUID::uuid_generate_random()
)
#> Unit: microseconds
#>      expr  min    lq     mean median   uq      max neval
#>      uuid 3.05 3.165 19.24921   3.28 3.36 1594.021   100
#>  RcppUUID 2.04 2.075  2.36520   2.11 2.20   20.280   100
```

Multiple UUIDs:

``` r
n <- 10000
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE, n),
  RcppUUID = RcppUUID::uuid_generate_random(n)
)
#> Unit: milliseconds
#>      expr      min       lq     mean   median       uq      max neval
#>      uuid 25.47780 25.98014 29.13786 26.07774 26.19531 199.5827   100
#>  RcppUUID 12.76133 13.05205 17.27462 13.46904 13.69007 203.0705   100
```

#### Generate version 5 UUIDs

Generate version 5 UUIDs based on text input:

``` r
RcppUUID::uuid_generate_name(letters[1:5])
#> [1] "54a0a790-c611-5b5b-b50e-ff01490ecdfa" "d5080e36-1ba4-5cb3-861c-34b25868f7db"
#> [3] "33ed51b6-a330-5830-bda9-2bac09e15753" "b74b2afe-06d5-5fea-99cc-a7de0b492704"
#> [5] "8535136c-b0d3-5373-aa79-ab67d33a2a8e"
```

For the each unique input will be generated unique UUID. Check
uniqueness:

``` r
uuids <- replicate(10, RcppUUID::uuid_generate_name(letters))
length(unique(as.vector(uuids))) == length(letters)
#> [1] TRUE
```

#### Validate UUIDs

``` r
RcppUUID::uuid_validate(NA_character_)
#> [1] FALSE
RcppUUID::uuid_validate("")
#> [1] FALSE
RcppUUID::uuid_validate("not uuid")
#> [1] FALSE
RcppUUID::uuid_validate(RcppUUID::uuid_generate_random(5))
#> [1] TRUE TRUE TRUE TRUE TRUE
RcppUUID::uuid_validate(RcppUUID::uuid_generate_nil(5))
#> [1] TRUE TRUE TRUE TRUE TRUE
RcppUUID::uuid_validate(RcppUUID::uuid_generate_name(letters[1:5]))
#> [1] TRUE TRUE TRUE TRUE TRUE
```

#### Generate version 7 UUIDs

Generate version 7 UUIDs based on under underlying clock at a 100ns
granularity:

```r
> RcppUUID::uuid_generate_time()
[1] "0194d8f9-c2e7-71aa-801b-75ae7f44aa1d"
>
```

Or generate multiple:

```r
> RcppUUID::uuid_generate_time(5)
[1] "0194d8fa-7add-735c-805b-6bbf22b78b9e" "0194d8fa-7add-735e-8012-3e0e53895b19"
[3] "0194d8fa-7add-735e-81af-bc67bb435ade" "0194d8fa-7add-735e-82b1-405bf57963ad"
[5] "0194d8fa-7add-735f-801e-efe57078b2e7"
>
```

### Installation

To install the package from the CRAN run the following command:

``` r
install.packages("RcppUUID", repos = "https://cloud.r-project.org/")
```

Pre-releases can be installed from [r-universe](https://eddelbuettel.r-universe.dev/RcppUUID)
via

```r
repos <- c(ru = 'https://eddelbuettel.r-universe.dev', getOption("repos"))
install.packages('RcppUUID', repos = repos)
```

which provides binaries for several operating systems too.

One can install the development version with the `install_github()`
function from the `remotes` package:

``` r
remotes::install_github("eddelbuettel/rcppuuid")
```

This package contains the compiled code, therefore one has to use the
[Rtools](https://cran.r-project.org/bin/windows/Rtools/) to install it
on Windows.



### Bug reports

Use the following command to go to the page for bug report submissions:

``` r
bug.report(package = "RcppUUID")
```

Before reporting a bug or submitting an issue, please do the following:

- Make sure that you error or issue was not reported or discussed earlier so
  please, use the search function.
- Check the news list of the current version. Some errors could be caused by
  the package changes. It could be done with the `news(package = "RcppUUID",
  Version == packageVersion("RcppUUID"))` command.
- Make a minimal reproducible example of the code that consistently causes
  the error.
- Make sure that the error occurs during the execution of a function
  from the `RcppUUID` package, not from other packages.
- Try to reproduce the error with the last development version of the
  package from the git repository.

Please attach `traceback()` and `sessionInfo()` output to bug report. It may
save a lot of time.

### License

The `RcppUUID` package is distributed under the
[GPLv2](http://www.gnu.org/licenses/gpl-2.0.html) license.

### Author

The package was written by [Artem Klevtsov](https://github.com/artemklevtsov)
and maintained in [this GitLab
repo](https://gitlab.com/artemklevtsov/rcppuuid) for releases 1.0.0 to 1.1.1.

Starting with release 1.1.2, the package in this repository is now maintained
by [Dirk Eddelbuettel](https://github.com/eddelbuettel).
