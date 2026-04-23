#!/usr/bin/env python3
from __future__ import annotations

import argparse
import datetime as dt
import re
import shutil
import subprocess
import sys
from pathlib import Path


def run_script(script_path: Path) -> str:
    result = subprocess.run(
        [str(script_path)],
        cwd=str(script_path.parent),
        text=True,
        capture_output=True,
        check=True,
    )
    return result.stdout


def parse_sections(raw_text: str) -> list[tuple[str, str]]:
    lines = raw_text.splitlines()
    sections: list[tuple[str, str]] = []
    i = 0

    def is_sep(line: str) -> bool:
        return bool(re.fullmatch(r"=+", line.strip()))

    while i < len(lines):
        if i + 2 < len(lines) and is_sep(lines[i]) and is_sep(lines[i + 2]):
            title = lines[i + 1].strip() or f"Section {len(sections) + 1}"
            i += 3
            body: list[str] = []
            while i < len(lines):
                if i + 2 < len(lines) and is_sep(lines[i]) and is_sep(lines[i + 2]):
                    break
                body.append(lines[i])
                i += 1
            sections.append((title, "\n".join(body).strip()))
        else:
            i += 1

    if not sections:
        return [("実行結果", raw_text.strip())]
    return sections


def escape_latex(text: str) -> str:
    table = {
        "\\": r"\textbackslash{}",
        "{": r"\{",
        "}": r"\}",
        "#": r"\#",
        "$": r"\$",
        "%": r"\%",
        "&": r"\&",
        "_": r"\_",
        "^": r"\^{}",
        "~": r"\~{}",
    }
    return "".join(table.get(ch, ch) for ch in text)


def build_tex(sections: list[tuple[str, str]]) -> str:
    now = dt.datetime.now().strftime("%Y-%m-%d %H:%M")

    blocks: list[str] = [
        r"\documentclass[uplatex,dvipdfmx,a4paper,11pt]{jsarticle}",
        r"\usepackage[margin=20mm]{geometry}",
        r"\usepackage{fancyvrb}",
        r"\usepackage[dvipdfmx]{hyperref}",
        r"\title{プログラミング演習III 課題C1 一括回答レポート}",
        rf"\date{{生成日時: {escape_latex(now)}}}",
        r"\begin{document}",
        r"\maketitle",
        r"\tableofcontents",
        r"\newpage",
    ]

    for title, body in sections:
        safe_title = escape_latex(title)
        blocks.append(rf"\section*{{{safe_title}}}")
        blocks.append(rf"\addcontentsline{{toc}}{{section}}{{{safe_title}}}")
        content = body if body else "(出力なし)"
        blocks.append(r"\begin{Verbatim}[fontsize=\small,frame=single]")
        blocks.append(content)
        blocks.append(r"\end{Verbatim}")

    blocks.append(r"\end{document}")
    blocks.append("")
    return "\n".join(blocks)


def compile_pdf(tex_path: Path) -> None:
    workdir = tex_path.parent
    stem = tex_path.stem

    if not shutil.which("uplatex"):
        raise RuntimeError("uplatex が見つかりません。TeX ファイルのみ生成しました。")
    if not shutil.which("dvipdfmx"):
        raise RuntimeError("dvipdfmx が見つかりません。TeX ファイルのみ生成しました。")

    cmd1 = ["uplatex", "-interaction=nonstopmode", "-halt-on-error", tex_path.name]
    cmd2 = ["uplatex", "-interaction=nonstopmode", "-halt-on-error", tex_path.name]
    cmd3 = ["dvipdfmx", f"{stem}.dvi"]

    for cmd in (cmd1, cmd2, cmd3):
        subprocess.run(cmd, cwd=str(workdir), check=True)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="answer_all.sh の出力を LaTeX/PDF レポート化します。"
    )
    parser.add_argument(
        "--script",
        type=Path,
        default=Path("answer_all.sh"),
        help="実行する一括回答スクリプト",
    )
    parser.add_argument(
        "--input-log",
        type=Path,
        default=None,
        help="既存ログを使う場合のファイルパス",
    )
    parser.add_argument(
        "--log",
        type=Path,
        default=Path("c1_answers.log"),
        help="生成・保存するログファイル名",
    )
    parser.add_argument(
        "--tex",
        type=Path,
        default=Path("c1_answers.tex"),
        help="生成するTeXファイル名",
    )
    parser.add_argument(
        "--no-pdf",
        action="store_true",
        help="PDF生成を行わずTeXまで生成する",
    )
    args = parser.parse_args()

    base_dir = Path(__file__).resolve().parent

    if args.input_log is not None:
        log_path = (base_dir / args.input_log).resolve()
        raw = log_path.read_text(encoding="utf-8")
    else:
        script_path = (base_dir / args.script).resolve()
        if not script_path.exists():
            raise FileNotFoundError(f"script not found: {script_path}")
        raw = run_script(script_path)
        (base_dir / args.log).write_text(raw, encoding="utf-8")

    sections = parse_sections(raw)
    tex_content = build_tex(sections)

    tex_path = (base_dir / args.tex).resolve()
    tex_path.write_text(tex_content, encoding="utf-8")
    print(f"[OK] TeX generated: {tex_path}")

    if args.no_pdf:
        print("[INFO] --no-pdf 指定のため PDF 生成はスキップしました。")
        return 0

    try:
        compile_pdf(tex_path)
    except Exception as exc:
        print(f"[WARN] PDF生成に失敗: {exc}")
        print("[INFO] TeXファイルは生成済みです。")
        return 1

    pdf_path = tex_path.with_suffix(".pdf")
    print(f"[OK] PDF generated: {pdf_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
