# regex pattern to validate
ptrn <- "[a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12}"


# test uuid_generate_random
expect_error(uuid_generate_random(NULL))
expect_error(uuid_generate_random(integer(0)))
# expect_error(uuid_generate_random(NA_integer_))
expect_error(uuid_generate_random(c(0, 0)))
expect_equal(uuid_generate_random(0), character(0))
expect_true(is.character(uuid_generate_random(1)))
expect_true(grepl(ptrn, uuid_generate_random(1)))
expect_equal(length(uuid_generate_random(1)), 1)
expect_equal(length(uuid_generate_random(5)), 5)
expect_equal(length(unique(uuid_generate_random(1000))), 1000)


# uuid_generate_nil
expect_error(uuid_generate_nil(NULL))
expect_error(uuid_generate_nil(integer(0)))
# expect_error(uuid_generate_nil(NA_integer_))
expect_error(uuid_generate_nil(c(0, 0)))
expect_equal(uuid_generate_nil(0), character(0))
expect_true(grepl(ptrn, uuid_generate_nil(1)))
expect_true(is.character(uuid_generate_nil(1)))
expect_equal(uuid_generate_nil(1), "00000000-0000-0000-0000-000000000000")
expect_equal(length(unique(uuid_generate_nil(100))), 1)


# test uuid_generate_name
expect_error(uuid_generate_name(NULL))
expect_error(uuid_generate_name(NA_integer_))
expect_error(uuid_generate_name(c(0, 0)))
expect_equal(uuid_generate_name(character(0)), character(0))
expect_true(grepl(ptrn, uuid_generate_name("a")))
expect_equal(uuid_generate_name(""), "00000000-0000-0000-0000-000000000000")
expect_equal(length(uuid_generate_name(letters)), length(letters))
expect_equal(length(unique(uuid_generate_name(letters))), length(letters))
