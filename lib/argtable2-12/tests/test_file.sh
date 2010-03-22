#!/bin/sh

echo $0 TESTS BEGIN

#these tests should all return zero (parse succeeded)
./test_file --help || exit 1
./test_file       test_file.sh       test_file.sh   test_file.sh   .sh   || exit 1
./test_file     ./test_file.sh     ./test_file.sh   test_file.sh   .sh   || exit 1
./test_file   ././test_file.sh   ././test_file.sh   test_file.sh   .sh   || exit 1
./test_file ./././test_file.sh ./././test_file.sh   test_file.sh   .sh   || exit 1
./test_file       test_file          test_file      test_file      ''    || exit 1

#these tests should all return non-zero (parse failed)

./test_file && exit 1


echo "$0 TESTS PASSED"
echo "----------------------------------"
