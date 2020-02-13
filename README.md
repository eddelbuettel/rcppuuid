
<!-- README.md is generated from README.Rmd. Please edit that file -->

# RcppUUID

<!-- badges: start -->

[![GitLab CI Build
Status](https://gitlab.com/artemklevtsov/rcppuuid/badges/master/pipeline.svg)](https://gitlab.com/artemklevtsov/rcppuuid/pipelines)
[![AppVeyor Build
status](https://ci.appveyor.com/api/projects/status/if9qot73i61ts59y?svg=true)](https://ci.appveyor.com/project/artemklevtsov/rcppuuid)
[![Codecov Code
Coverage](https://codecov.io/gl/artemklevtsov/rcppuuid/branch/master/graph/badge.svg)](https://codecov.io/gl/artemklevtsov/rcppuuid)
[![CRAN
Status](http://www.r-pkg.org/badges/version/RcppUUID)](https://cran.r-project.org/package=RcppUUID)
[![License: GPL
v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

<!-- badges: end -->

R package to generate Universally Unique Identifiers (UUIDs).

## Installation

To install the package from the CRAN run the following command:

``` r
install.packages("RcppUUID", repos = "https://cloud.r-project.org/")
```

Also you could install the dev-version with the `install_gitlab()`
function from the `remotes` package:

``` r
remotes::install_gitlab("artemklevtsov/rcppuuid")
```

This package contains the compiled code, therefore you have to use the
[Rtools](https://cran.r-project.org/bin/windows/Rtools/) to install it
on Windows.

## Usage

Generate single UUID:

``` r
RcppUUID::uuid_generate(1)
#> [1] "463f2be4-d35a-4918-9cf0-202c6b80f256"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate(5)
#> [1] "fc4bf713-7ea7-418b-8050-deac2ff6eac8"
#> [2] "d2ba5e3b-2d65-4cad-a006-ed221cefca00"
#> [3] "59b5dc67-e617-42de-8b23-31be07e941cf"
#> [4] "33ad0521-0127-446a-8469-82e5b2442fcd"
#> [5] "5058e91e-ca1d-479f-9ecf-8e21e33565db"
```

Check uniques:

``` r
n <- 1000000
length(unique(RcppUUID::uuid_generate(n))) == n
#> [1] TRUE
```

## Benchmarking

``` r
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE),
  RcppUUID = RcppUUID::uuid_generate(1)
)
#> Unit: microseconds
#>      expr    min      lq     mean  median      uq      max neval cld
#>      uuid 14.808 15.4950 38.84707 15.8645 16.2765 2296.561   100   a
#>  RcppUUID 10.752 11.3085 12.63245 11.9840 12.4820   69.302   100   a
```

``` r
n <- 10000
microbenchmark::microbenchmark(
  uuid = replicate(n, uuid::UUIDgenerate(FALSE)),
  RcppUUID = RcppUUID::uuid_generate(n)
)
#> Unit: milliseconds
#>      expr       min        lq      mean    median        uq       max neval cld
#>      uuid 170.63409 186.62638 206.77789 194.16725 218.38896 398.37136   100   b
#>  RcppUUID  33.13655  33.62311  33.84627  33.82633  34.07119  34.54811   100  a
```

## Bug reports

Use the following command to go to the page for bug report submissions:

``` r
bug.report(package = "RcppUUID")
```

Before reporting a bug or submitting an issue, please do the following:

  - Make sure that you error or issue was not reported or discussed
    earlier. Please, use the search;
  - Check the news list of the current version. Some errors could be
    caused by the package changes. It could be done with `news(package =
    "RcppUUID", Version == packageVersion("RcppUUID"))` command;
  - Make a minimal reproducible example of the code that consistently
    causes the error;
  - Make sure that the error occurs during the execution of a function
    from the `RcppUUID` package, not from other packages;
  - Try to reproduce the error with the last development version of the
    package from the git repository.

Please attach traceback() and sessionInfo() output to bug report. It may
save a lot of time.

## License

The `RcppUUID` package is distributed under
[GPLv2](http://www.gnu.org/licenses/gpl-2.0.html) license.
