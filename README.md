# fast_git_grep

## 概要
`fast_git_grep` は、GitLabの `@hashed` ディレクトリ構造下にある大量のベアリポジトリを対象に、全プロジェクト・全ブランチを横断して高速に文字列検索（`git grep`）を行うC++製コマンドラインツールです。

- GitLabサーバーの `git-data/repositories/@hashed/` 配下の全リポジトリを自動検出
- プロジェクト名DB（sqlite3）と連携し、リポジトリのパスからプロジェクト名を取得
- 検索対象ブランチの戦略（main, latest, all）を選択可能
- 並列/逐次検索の切り替えが可能
- 除外プロジェクト・除外ブランチのパターン指定が可能
- 進捗バー・詳細なデバッグ出力

## 構成

- `src/config/` ... 設定・定数・設定ファイルローダ
- `src/core/` ... 検索ロジック・リポジトリ/プロジェクト管理・grep実行
- `src/core/BranchSelector/` ... ブランチ選択戦略（main, latest, all）
- `src/core/SearchManager/` ... 並列/逐次検索マネージャ
- `src/util/` ... 進捗バー・エラー管理・引数パーサ
- `doc/class.puml` ... クラス図（PlantUML）

## 使い方

### ビルド

```sh
make rpm
```

### 実行例

```sh
sudo ./fast_git_grep <検索文字列> [--branch_strategy main|all|latest] [--parallel_strategy parallel|sequential] [--excluded_projects <pattern>] [--excluded_branches <pattern>] [--debug]
```

#### オプション
- `--branch_strategy` : 検索対象ブランチの戦略（main, all, latest）
- `--parallel_strategy` : 並列/逐次検索の切り替え
- `--excluded_projects` : 除外プロジェクト名パターン（正規表現）
- `--excluded_branches` : 除外ブランチ名パターン（正規表現）
- `--debug` : デバッグ出力
- `--help` : ヘルプ表示

### 設定ファイル
- `etc/ini.config` で各種パスやデフォルト値を指定可能
- プロジェクト名DBのパスやGitLabリポジトリルートもここで指定

### 検索対象
- GitLabの `@hashed` ディレクトリ配下の全ベアリポジトリ
- プロジェクト名DB（sqlite3）でパス→プロジェクト名を解決
- 除外パターンに一致しないプロジェクト・ブランチのみ対象

### 検索戦略
- main: mainブランチ優先、なければmaster
- all: すべてのブランチ
- latest: 最新コミットのブランチ(default)

### 並列実行
- デフォルトで全プロジェクトをスレッド並列で検索
- サーバー負荷を抑えたい場合は `--parallel_strategy sequential` を指定

## 開発・拡張
- クラス図は `doc/class.puml` を参照
- 1クラス1ヘッダ/実装ファイルで拡張しやすい構成
- 新しいブランチ戦略や検索戦略も容易に追加可能

## ライセンス
MIT License
