#!/bin/sh
set -eu

BASE_DIR=$(CDPATH= cd -- "$(dirname "$0")" && pwd)

section() {
  printf "\n==============================\n"
  printf "%s\n" "$1"
  printf "==============================\n"
}

section "課題C1 一括回答"
printf "作業ディレクトリ: %s\n" "$BASE_DIR"

section "例題2: hello.c の出力"
cd "$BASE_DIR/basics"
gcc hello.c -o myhello
./myhello

section "例題3: repeat.c の出力"
gcc repeat.c -o myrepeat
printf "(1) ./myrepeat Hello World!\n"
./myrepeat Hello World!
printf "(2) ./myrepeat A B C\n"
./myrepeat A B C

section "例題4: functions.c の出力"
gcc functions.c -o myfunctions
./myfunctions

section "例題5: substitute.c の出力"
gcc substitute.c -o mysubstitute
./mysubstitute

section "例題6: malloc1.c 空欄と実行"
printf "空欄(1): (int *)malloc(sizeof(int) * n)\n"
gcc malloc1.c -o mymalloc1
./mymalloc1 10

section "例題7: read_array.c 空欄と実行"
printf "空欄(1): read_array(argv[1], n)\n"
printf "空欄(2): (int *)malloc(sizeof(int) * n)\n"
gcc read_array.c -o myread_array
./myread_array array.txt

section "基本問題1: test.c (入力27)"
cd "$BASE_DIR/test"
gcc test.c -o mytest
printf "27\n" | ./mytest

section "基本問題2: 各コマンドで作られるファイル"
cd "$BASE_DIR/make_test"
rm -f main.o interface.o arithmetic.o mytest
gcc -c main.c
printf "(1) gcc -c main.c -> main.o\n"
gcc -c interface.c
printf "(2) gcc -c interface.c -> interface.o\n"
gcc -c arithmetic.c
printf "(3) gcc -c arithmetic.c -> arithmetic.o\n"
gcc main.o interface.o arithmetic.o -o mytest
printf "(4) gcc main.o interface.o arithmetic.o -o mytest -> mytest\n"

section "基本問題3: make の出力(4行)"
make clean >/dev/null 2>&1 || true
make

section "基本問題4: 端末に入力する内容"
printf "(1) make\n"
printf "(2) make clean\n"
printf "(3) make interface.o\n"

section "基本問題5: make_array のmakefile内容と実行"
cd "$BASE_DIR/make_array"
printf "%s\n" "--- makefile ---"
cat makefile
make clean >/dev/null 2>&1 || true
make
./array_test array.txt

section "発展課題1: 最頻値"
cd "$BASE_DIR/advanced"
gcc occurrence.c -o occurrence
printf "サンプル array.txt の最頻値:\n"
./occurrence array.txt

section "後片付け"
rm -f "$BASE_DIR/basics/myhello" \
      "$BASE_DIR/basics/myrepeat" \
      "$BASE_DIR/basics/myfunctions" \
      "$BASE_DIR/basics/mysubstitute" \
      "$BASE_DIR/basics/mymalloc1" \
      "$BASE_DIR/basics/myread_array" \
      "$BASE_DIR/test/mytest" \
      "$BASE_DIR/advanced/occurrence"
cd "$BASE_DIR/make_test"
make clean >/dev/null 2>&1 || true
cd "$BASE_DIR/make_array"
make clean >/dev/null 2>&1 || true

section "完了"
printf "一括回答の生成が完了しました。\n"
