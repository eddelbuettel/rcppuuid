
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

R package to generate Universally Unique Identifiers (UUIDs) version 4
and 5.

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

### Generate version 4 UUIDs

Generate single UUID:

``` r
RcppUUID::uuid_generate_random(1)
#> [1] "a56cd007-d384-444c-9cc0-5a8257ac3c49"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate_random(5)
#> [1] "a27dfb6e-e195-4479-9e98-f3102b2535bc" "08f60ac3-e0be-40b8-b540-eefcf05d3f4c" "ba40c747-c2e5-429d-b2b2-a835af0b74fc"
#> [4] "65fefc7b-0bae-4b96-89dc-4ae0afdc94a9" "0d495322-ef1f-4820-96cf-337e77782a34"
```

Check uniques:

``` r
n <- 1000000
length(unique(RcppUUID::uuid_generate_random(n))) == n
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
#>      expr    min      lq     mean  median     uq      max neval cld
#>      uuid 15.669 16.3065 36.42114 16.6275 17.101 1973.512   100   a
#>  RcppUUID  8.806  9.2210 14.12059 10.0010 10.717  250.013   100   a
```

Multiple UUIDs:

``` r
n <- 10000
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE, n),
  RcppUUID = RcppUUID::uuid_generate_random(n)
)
#> Unit: milliseconds
#>      expr       min        lq     mean   median        uq      max neval cld
#>      uuid 79.501951 81.613093 87.78974 84.14981 86.582511 229.6141   100   b
#>  RcppUUID  5.511901  6.392065 12.88998  6.91313  8.714627 308.0580   100  a
```

### Generate version 5 UUIDs

Generate version UUIDs based on the text input:

``` r
RcppUUID::uuid_generate_name(letters)
#>  [1] "54a0a790-c611-5b5b-b50e-ff01490ecdfa" "d5080e36-1ba4-5cb3-861c-34b25868f7db"
#>  [3] "33ed51b6-a330-5830-bda9-2bac09e15753" "b74b2afe-06d5-5fea-99cc-a7de0b492704"
#>  [5] "8535136c-b0d3-5373-aa79-ab67d33a2a8e" "3a876f3e-f633-5838-8e8d-85cbe7e4cfa0"
#>  [7] "dcc54724-2b68-59ea-aa01-a5eedebaca0a" "be34dbb0-a054-5d66-82cb-cda5da801ce1"
#>  [9] "3785df0a-16e9-5981-834c-b81e62d5b242" "77e622e0-aa2e-5aed-8b05-2e0c968b91ab"
#> [11] "e113dbba-7e25-50fd-86b4-1cd1a21c9844" "4eeb0331-584d-52d5-b466-7f1da8b50f01"
#> [13] "b9380571-a553-567e-87a2-c6961b93367f" "e3994dd9-a468-5724-85d9-08f4392e32bf"
#> [15] "dfeec8f2-ace7-57e9-8b74-1c8113a9232f" "a3406a87-1481-568c-9f64-55f36b24b02f"
#> [17] "4c93356e-1b15-50c2-aca3-4a58c1d143c4" "6356cad3-e13a-5db3-aae9-131b29997c99"
#> [19] "99f410c7-b96b-5a68-adaa-61224692decd" "246136f2-9721-5d5a-994a-ee3d1e6f9a4d"
#> [21] "9eb339b5-c976-5f06-a2cf-3e8240da4a0d" "0ad9fa60-82cb-57c1-bbae-0aa20605061e"
#> [23] "e76eef5d-bdfe-5727-a0f0-5a72649b0752" "456e503f-63e3-56c1-b807-4cd79bf8cc22"
#> [25] "d431692f-9a43-5034-bf6f-b3962773861a" "713d341e-51f1-5857-ab86-edef8fa5b522"
```

For the each unique input will be generated unique UUID. Check
uniqueness:

``` r
uuids <- replicate(10, RcppUUID::uuid_generate_name(letters))
length(unique(as.vector(uuids))) == length(letters)
#> [1] TRUE
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
