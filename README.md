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

## 你需要做什么

1. `git clone` 将仓库克隆下来

2. `git branch --set-upstream-to=<remote(远端名)>/<remote branch(分支名)>` 将本地main分支与远端对应分支关联，例如

   ```
   git branch --set-upstream-to=origin/zhou
   ```

3. 使用`git add .` 将修改添加到暂存区

4. 使用`git commit -m "xxx"`在本地提交修改

5. `git push`将本地修改推送到远端 **（在那之前一定要确保已经关联了正确的分支！)**

# 不要改其他地方的代码，只改你负责的部分！！

