# CommonRepository

> A tiny starter to verify your ChatGPT ↔ GitHub connector.  
> 提供最小可读/可编译/可搜索（含 “TODO”）的仓库内容，方便做冒烟测试。

## 结构
```
.
├─ README.md
├─ LICENSE
├─ .gitignore
├─ .github/workflows/ci.yml
├─ include/
│  └─ demo.h
└─ src/
   ├─ main.c
   └─ demo.c
```

## 快速开始（网页端）
1. 在 GitHub 仓库页面点击 **Add file → Upload files**，把本 Zip 里所有文件拖进去。
2. 提交信息（commit message）可用：`init: starter + CI`。

## 快速开始（命令行）
```bash
git clone https://github.com/baozicn/CommonRepository.git
cd CommonRepository
# 把本压缩包解压覆盖到当前目录后：
git add -A
git commit -m "init: starter + CI"
git push
```

## 你可以对 ChatGPT 说（用于连接器测试）
- 读取 `baozicn/CommonRepository` 的 `README.md` 前 40 行
- 列出 `baozicn/CommonRepository` 最近 3 次 commit
- 在 `baozicn/CommonRepository` 中搜索包含 "TODO" 的文件路径列表

祝测试顺利！
