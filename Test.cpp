#include "doctest.h"
#include "Board.hpp"
using namespace ariel;

using namespace std;
ariel::Board board;

TEST_CASE("good input")
{
    board.post(0, 0, Direction::Horizontal, "aaa");
    CHECK(board.read(0, 0, Direction::Horizontal, 1) == "a");
    CHECK(board.read(0, 0, Direction::Horizontal, 2) == "aa");
    CHECK(board.read(0, 0, Direction::Horizontal, 3) == "aaa");

    board.post(1, 0, Direction::Vertical, "bbb");
    CHECK(board.read(1, 0, Direction::Vertical, 1) == "b");
    CHECK(board.read(1, 0, Direction::Vertical, 2) == "bb");
    CHECK(board.read(0, 0, Direction::Vertical, 3) == "bbb");

    // check if board ad made far and board resized
    board.post(100, 200, Direction::Horizontal, "aaa");
    CHECK(board.read(100, 200, Direction::Horizontal, 1) == "a");
    CHECK(board.read(100, 200, Direction::Horizontal, 2) == "aa");
    CHECK(board.read(100, 200, Direction::Horizontal, 3) == "aaa");

    board.post(101, 200, Direction::Vertical, "bbb");
    CHECK(board.read(101, 200, Direction::Vertical, 1) == "b");
    CHECK(board.read(101, 200, Direction::Vertical, 2) == "bb");
    CHECK(board.read(101, 200, Direction::Vertical, 3) == "bbb");
}

TEST_CASE("goes over another ad")
{
    CHECK_THROWS(board.post(0, 0, Direction::Horizontal, "b")); // check if replacement throwed
    // CHECK_THROWS(board.post(0, 0, Direction::Horizontal, "b")); // maybe check if theres at least 1 space between ads
}

TEST_CASE("bad length")
{
    CHECK(board.read(0, 0, Direction::Horizontal, 4) == "baa-"); // gets an empty line after baa read {baa-} length is 4 instead of 3
    CHECK_THROWS(board.read(0, 0, Direction::Horizontal, 1000)); // too long
}

TEST_CASE("bad line numbers")
{
    // CHECK_THROWS(board.post(-1, -1, Direction::Horizontal, "a"));  // negative numbers
    // CHECK_THROWS(board.post(-1, 0, Direction::Horizontal, "a"));
    // CHECK_THROWS(board.post(0, -1, Direction::Horizontal, "a"));

    CHECK_THROWS(board.post('a', 'a', Direction::Horizontal, "a")); // chars
    CHECK_THROWS(board.read(300, 400, Direction::Vertical, 4));     // empty
    CHECK_THROWS(board.read(1000, 1000, Direction::Vertical, 4));   // empty in bigger size after resize
}

TEST_CASE("bad direction")
{
    //CHECK_THROWS(board.post(0, 0, Direction::up, "a"));
}

TEST_CASE("bad message")
{
    CHECK_THROWS(board.post(1, 1, Direction::Horizontal, " ")); // empty
    CHECK_THROWS(board.post(1, 1, Direction::Horizontal, "-")); // our empty sign
}
