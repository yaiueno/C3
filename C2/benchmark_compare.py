#!/usr/bin/env python3
import argparse
import json
import math
import multiprocessing
import statistics
import subprocess
import sys
import tempfile
import time
import webbrowser
from pathlib import Path


def ensure_binary(build_dir: Path, binary_name: str) -> Path:
    binary = build_dir / binary_name
    if binary.exists():
        return binary

    subprocess.run(["make", binary_name], cwd=build_dir, check=True)
    if not binary.exists():
        raise FileNotFoundError(f"{binary} が作成できませんでした")
    return binary


def write_random_array_c(path: Path, n: int, mywrite_bin: Path) -> None:
    """C の mywrite バイナリで乱数配列を生成"""
    with path.open("w", encoding="utf-8") as f:
        subprocess.run([str(mywrite_bin), str(n)], stdout=f, check=True, stderr=subprocess.DEVNULL)


def run_sort(binary: Path, input_file: Path) -> float:
    t0 = time.perf_counter()
    subprocess.run([str(binary), str(input_file)], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    t1 = time.perf_counter()
    return t1 - t0


def _run_one_trial(args_tuple):
    """各試行を実行（並列処理用）"""
    trial_id, n, selection_bin_str, insertion_bin_str, mywrite_bin_str = args_tuple
    
    selection_bin = Path(selection_bin_str)
    insertion_bin = Path(insertion_bin_str)
    mywrite_bin = Path(mywrite_bin_str)
    
    with tempfile.NamedTemporaryFile(mode='w', delete=False, suffix='.txt') as f:
        input_file = Path(f.name)
    
    try:
        write_random_array_c(input_file, n, mywrite_bin)
        
        selection_time = run_sort(selection_bin, input_file)
        insertion_time = run_sort(insertion_bin, input_file)
        
        return {
            "trial_id": trial_id,
            "selection_time": selection_time,
            "insertion_time": insertion_time,
        }
    finally:
        input_file.unlink(missing_ok=True)


def summarize(samples: list[float]) -> dict:
    if not samples:
        return {"count": 0, "mean_sec": math.nan, "variance_sec2": math.nan}

    return {
        "count": len(samples),
        "mean_sec": statistics.fmean(samples),
        "variance_sec2": statistics.pvariance(samples),
        "min_sec": min(samples),
        "max_sec": max(samples),
    }


def main() -> int:
    parser = argparse.ArgumentParser(
        description="selection_sort と insertion_sort の性能比較（平均・分散）[並列処理対応]"
    )
    parser.add_argument("--n", type=int, default=100_000, help="配列サイズ（デフォルト: 100000）")
    parser.add_argument("--trials", type=int, default=100, help="試行回数（デフォルト: 10）")
    parser.add_argument("--workers", type=int, default=None, help="並列処理ワーカー数（デフォルト: CPU数）")
    parser.add_argument(
        "--report-file",
        type=Path,
        default=Path("files") / "benchmark_report.txt",
        help="テキストレポート出力先",
    )
    parser.add_argument(
        "--json-file",
        type=Path,
        default=Path("files") / "benchmark_report.json",
        help="JSONレポート出力先",
    )

    args = parser.parse_args()

    repo_root = Path(__file__).resolve().parent
    selection_bin = ensure_binary(repo_root / "selection", "myselection_sort")
    insertion_bin = ensure_binary(repo_root / "insertion", "myinsertion_sort")
    mywrite_bin = repo_root / "files" / "mywrite"
    
    if not mywrite_bin.exists():
        raise FileNotFoundError(f"{mywrite_bin} が見つかりません。files/ ディレクトリで make してください")

    args.report_file.parent.mkdir(parents=True, exist_ok=True)
    args.json_file.parent.mkdir(parents=True, exist_ok=True)
    
    html_file = (args.report_file.parent / "benchmark_report.html").resolve()

    if args.workers is None:
        args.workers = multiprocessing.cpu_count()

    print(
        f"Benchmark start (parallel): n={args.n}, trials={args.trials}, "
        f"workers={args.workers}"
    )

    started = time.perf_counter()
    
    trial_args = [
        (trial_id, args.n, str(selection_bin), str(insertion_bin), str(mywrite_bin))
        for trial_id in range(args.trials)
    ]

    with multiprocessing.Pool(processes=args.workers) as pool:
        results = pool.map(_run_one_trial, trial_args)

    elapsed = time.perf_counter() - started

    selection_times = [r["selection_time"] for r in results]
    insertion_times = [r["insertion_time"] for r in results]

    selection_summary = summarize(selection_times)
    insertion_summary = summarize(insertion_times)

    ratio = selection_summary["mean_sec"] / insertion_summary["mean_sec"] if insertion_summary["mean_sec"] > 0 else math.inf

    result = {
        "config": {
            "n": args.n,
            "trials": args.trials,
            "workers": args.workers,
        },
        "selection_sort": selection_summary,
        "insertion_sort": insertion_summary,
        "mean_ratio_selection_over_insertion": ratio,
        "total_elapsed_sec": elapsed,
    }

    report_text = (
        "=== Sort Benchmark Report (Parallel with C random generation) ===\n"
        f"n = {args.n}\n"
        f"trials = {args.trials}\n"
        f"workers = {args.workers}\n"
        f"total elapsed = {elapsed:.3f} sec\n\n"
        "[selection_sort]\n"
        f"mean = {selection_summary['mean_sec']:.6f} sec\n"
        f"variance = {selection_summary['variance_sec2']:.6f} sec^2\n"
        f"min = {selection_summary['min_sec']:.6f} sec\n"
        f"max = {selection_summary['max_sec']:.6f} sec\n\n"
        "[insertion_sort]\n"
        f"mean = {insertion_summary['mean_sec']:.6f} sec\n"
        f"variance = {insertion_summary['variance_sec2']:.6f} sec^2\n"
        f"min = {insertion_summary['min_sec']:.6f} sec\n"
        f"max = {insertion_summary['max_sec']:.6f} sec\n\n"
        f"mean ratio (selection / insertion) = {ratio:.6f}\n"
    )

    args.report_file.write_text(report_text, encoding="utf-8")
    args.json_file.write_text(json.dumps(result, indent=2, ensure_ascii=False), encoding="utf-8")

    html_content = f"""<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ソート性能比較レポート</title>
    <style>
        body {{
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            margin: 20px;
            background-color: #f5f5f5;
        }}
        .container {{
            background-color: white;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            max-width: 900px;
            margin: 0 auto;
        }}
        h1 {{
            color: #333;
            border-bottom: 3px solid #007bff;
            padding-bottom: 10px;
        }}
        h2 {{
            color: #555;
            margin-top: 30px;
            border-left: 4px solid #007bff;
            padding-left: 15px;
        }}
        .config, .results {{
            background-color: #f9f9f9;
            padding: 15px;
            border-radius: 5px;
            margin: 15px 0;
        }}
        .metric {{
            display: inline-block;
            margin: 10px 20px 10px 0;
        }}
        .metric-label {{
            font-weight: bold;
            color: #333;
        }}
        .metric-value {{
            color: #007bff;
            font-size: 1.1em;
        }}
        .comparison {{
            background-color: #e8f4f8;
            padding: 15px;
            border-left: 4px solid #17a2b8;
            margin: 20px 0;
        }}
        .winner {{
            background-color: #d4edda;
            padding: 15px;
            border-left: 4px solid #28a745;
            margin: 20px 0;
            font-weight: bold;
        }}
        table {{
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }}
        th, td {{
            padding: 12px;
            text-align: left;
            border-bottom: 1px solid #ddd;
        }}
        th {{
            background-color: #007bff;
            color: white;
        }}
        tr:hover {{
            background-color: #f5f5f5;
        }}
        .footer {{
            margin-top: 30px;
            font-size: 0.9em;
            color: #666;
            text-align: center;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>🔬 ソート性能比較レポート</h1>
        
        <h2>📊 テスト条件</h2>
        <div class="config">
            <div class="metric">
                <span class="metric-label">配列サイズ:</span>
                <span class="metric-value">{args.n:,}</span>
            </div>
            <div class="metric">
                <span class="metric-label">試行回数:</span>
                <span class="metric-value">{args.trials}</span>
            </div>
            <div class="metric">
                <span class="metric-label">並列ワーカー:</span>
                <span class="metric-value">{args.workers}</span>
            </div>
            <div class="metric">
                <span class="metric-label">総実行時間:</span>
                <span class="metric-value">{elapsed:.3f} 秒</span>
            </div>
        </div>

        <h2>⏱️ 実行結果</h2>
        <table>
            <thead>
                <tr>
                    <th>ソート方式</th>
                    <th>平均時間 (秒)</th>
                    <th>分散 (秒²)</th>
                    <th>最小値 (秒)</th>
                    <th>最大値 (秒)</th>
                </tr>
            </thead>
            <tbody>
                <tr style="background-color: #ffe8e8;">
                    <td><strong>Selection Sort</strong></td>
                    <td>{selection_summary['mean_sec']:.6f}</td>
                    <td>{selection_summary['variance_sec2']:.6f}</td>
                    <td>{selection_summary['min_sec']:.6f}</td>
                    <td>{selection_summary['max_sec']:.6f}</td>
                </tr>
                <tr style="background-color: #e8f4ff;">
                    <td><strong>Insertion Sort</strong></td>
                    <td>{insertion_summary['mean_sec']:.6f}</td>
                    <td>{insertion_summary['variance_sec2']:.6f}</td>
                    <td>{insertion_summary['min_sec']:.6f}</td>
                    <td>{insertion_summary['max_sec']:.6f}</td>
                </tr>
            </tbody>
        </table>

        <h2>🏆 比較結果</h2>
        <div class="comparison">
            <p><strong>性能比率 (Selection / Insertion):</strong> <span style="font-size: 1.3em; color: #ff6b6b;">{ratio:.4f}x</span></p>
        </div>

        <div class="winner">
            ✅ <strong>Insertion Sort が {ratio:.2f}倍高速です</strong>
            <p style="margin: 10px 0 0 0; font-size: 0.95em;">
                Insertion Sort の平均実行時間が {insertion_summary['mean_sec']:.6f} 秒で、
                Selection Sort の {selection_summary['mean_sec']:.6f} 秒より高速です。
            </p>
        </div>

        <div class="footer">
            <p>生成日時: {time.strftime('%Y-%m-%d %H:%M:%S')}</p>
            <p>テキストレポート: <code>{args.report_file}</code></p>
            <p>JSONデータ: <code>{args.json_file}</code></p>
        </div>
    </div>
</body>
</html>
"""
    
    html_file.write_text(html_content, encoding="utf-8")

    print(report_text)
    print(f"text report: {args.report_file}")
    print(f"json report: {args.json_file}")
    print(f"html report: {html_file}")
    
    # ブラウザでHTMLレポートを開く
    webbrowser.open(html_file.as_uri())
    print(f"\nブラウザでレポートを開いています...")

    return 0


if __name__ == "__main__":
    sys.exit(main())
