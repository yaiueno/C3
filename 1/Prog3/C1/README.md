# Prog3 C1 演習セット

OCRで抽出した課題C1（例題・基本問題・発展課題）の作業用ひな形です。

## ディレクトリ

- `basics/` 例題2〜7のプログラム
- `test/` 基本問題1
- `make_test/` 基本問題2〜4
- `make_array/` 基本問題5
- `advanced/` 発展課題1

## 補足

- PDF本文中で図として埋め込まれている箇所（例題1のディレクトリ図、例題8本文）は、抽出テキストでは欠落していました。
- 例題8に依存する `make_array/array_operations.c` は、問題文の指示に従い例題7相当の実装を入れています。

## 一括回答をPDF化する

1. 一括回答スクリプトを実行（必要なら）
	- `./answer_all.sh`
2. LaTeX/PDF生成スクリプトを実行
	- `python make_answer_pdf.py`

生成物:

- `c1_answers.log`（一括回答のログ）
- `c1_answers.tex`（LaTeXソース）
- `c1_answers.pdf`（提出用に見やすく整形したPDF）

PDFを作らずTeXだけ作る場合:

- `python make_answer_pdf.py --no-pdf`
