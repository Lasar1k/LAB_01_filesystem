// Copyright 2021 Lasar1k <alf.ivan2002@gmail.com>

#include <stdexcept>

#include <gtest/gtest.h>

#include <searcher.hpp>

TEST(Example, EmptyTest) {
    EXPECT_THROW(example(), std::runtime_error);
}
