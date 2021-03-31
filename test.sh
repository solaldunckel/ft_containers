# DEFINES

COMPILER="clang++"
CFLAGS="-Wall -Wextra -Werror -std=c++98 -fsanitize=address"
INCLUDES="-I containers/ -I utils/ -I tests/"
DEFINE="-DNAMESPACE="

#vector map stack queue)

TEST_FOLDER="tests/"
OUTPUT_FOLDER="output/"

NAMESPACES=(std ft)

if [[ ("$#" > 0) ]]
then
  CONTAINERS=()
  for var in "$@"
  do
    CONTAINERS+=($var)
  done
else
  CONTAINERS=(list stack queue vector map)
fi

mkdir -p $OUTPUT_FOLDER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

OK="printf(\"$GREEN\" '[OK]' \"$RESET\"))"
KO="printf(\"$RED\" '[KO]' \"$RESET\"))"

for container in "${CONTAINERS[@]}"
do
  OUTPUT=()
  DIFF=()

  echo "\t--> $(echo $container | tr a-z A-Z) <--\n"

  CONTAINERS_TESTS=($(ls $TEST_FOLDER${container}/*.cpp))

  for test in "${CONTAINERS_TESTS[@]}"
  do
    TEST_NAME=$(basename $test .cpp)

    for namespace in "${NAMESPACES[@]}"
    do
      OUTPUT="${namespace}_${container}_${TEST_NAME}" # ft_list

      $COMPILER $CFLAGS $INCLUDES $DEFINE${namespace} -o $OUTPUT_FOLDER"$OUTPUT.out" $test

      ./$OUTPUT_FOLDER"$OUTPUT.out" > $OUTPUT_FOLDER"$OUTPUT.txt"

      rm -rf $OUTPUT_FOLDER"$OUTPUT.out"

      OUTPUT+=("$OUTPUT.out")
      DIFF+=("$OUTPUT.txt")
    done

    TEST=$(diff $OUTPUT_FOLDER${DIFF[0]} $OUTPUT_FOLDER${DIFF[1]});

    if [[ $TEST ]]
    then
      printf "%-13s : [$BOLDRED%s$RESET]\n" "$TEST_NAME" "✗"
    else
      printf "%-13s : [$BOLDGREEN%s$RESET]\n" "$TEST_NAME" "✓"
    fi
  done
  echo
done

rm -rf $OUTPUT_FOLDER