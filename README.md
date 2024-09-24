# snake_game

# Git 基本操作

`git clone`:克隆仓库

`git branch`:显示分支

`git pull`:获取远端更新

`git branch --set-upstream-to=<remote(远端名)>/<remote branch(分支名)>`: 创建本地和远端分支的关联关系

`git add .`:将当前目录下所有修改添加到暂存区

`git commit -m "修改了/添加/删除xxx"`: 提交修改

`git push`:推送到远端

`git pull <远端仓库名> <远端分支名>:<本地分支名> ` :

git pull origin main:main

## **分支和合并**

- `git branch`: 显示分支
- `git branch <name>`: 创建分支
- `git checkout -b <name>`: 创建分支并切换到该分支
  - 相当于 `git branch <name>; git checkout <name>`
- `git checkout -b <name> <remote>/<branch>` ; **创建一个追踪远端分支的分支**
  - ```Shell
    git checkout -b test01 origin/test01
    ```
- `git merge <revision>`: 合并到当前分支
- `git mergetool`: 使用工具来处理合并冲突
- `git rebase`: 将一系列补丁变基（rebase）为新的基线

## 你需要做什么

1. `git clone` 将仓库克隆下来

2. `git branch --set-upstream-to=<remote(远端名)>/<remote branch(分支名)>` 将本地main分支与远端对应分支关联，例如

   ```
   git branch --set-upstream-to=origin/zhou
   ```

3. 使用`git add .` 将修改添加到暂存区

4. 使用`git commit -m "xxx"`在本地提交修改

5. `git push origin HEAD:zhou `将本地修改推送到远端 **（在那之前一定要确保已经关联了正确的分支！)**

# 不要改其他地方的代码，只改你负责的部分！！

# 简历可以怎么写？

c语言 easyx Git团队协作 代码架构 OPP思想 visual studio 断点调试

