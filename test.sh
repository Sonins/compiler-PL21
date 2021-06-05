BUILD_DIR="build"
TEST_DIR="test"
COMPILER_NAME="compiler2021"

printf "test file: %s\n\n" $1

sh build.sh

./$BUILD_DIR/$COMPILER_NAME $TEST_DIR/$1
