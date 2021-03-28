# Git学习报告

## 一、Git简介

Git是目前世界上最先进的分布式版本控制系统。Git可以记录提交文件每次的改动，而且可以让他人协作编辑，并且随时可以查看以前的版本。

关于分布式：分布式版本控制系统与集中式版本控制最大的区别是可以没有中央服务器，每个人电脑中都有完整的版本库，某台电脑数据损坏也不要紧，只需要拷贝一份其他人的版本库即可。不过分布式版本控制系统通常也有一台充当“中央服务器”的电脑，但这个服务器的作用仅仅是用来方便“交换”大家的修改，没有它大家也一样干活，只是交换修改不方便而已。

# 二、安装Git

linux系统上只需要输入

```
sudo apt-get install git
```

即可完成安装，之后，我们需要在自己的电脑上创建一个版本库，在主目录上创建git文件夹后使用git init变为git可以管理的仓库

```
git init
Initialized empty Git repository in /git/.git/
```

![QQ图片20210328031711](C:\Users\asus\Desktop\QQ图片20210328031711.png)

之后我们把刚刚编写的大数运算文件传输到该文件夹内，并尝试上传到版本库，使用git add命令提交到仓库

```
git add bigNumberCalculation//该命令执行后没有显示
```

然后使用命令`git commit`告诉Git，把文件提交到仓库

```
git commit -m "calculation"
```

`-m`后面输入的是本次提交的说明，可以输入任意内容，当然最好是有意义的，这样你就能从历史记录里方便地找到改动记录。成功后系统会告诉你文件被改动

注：一次实际上可以add多个文件，然后用commit统一提交上去

# 三、GitHub注册与使用

Git的实际情况往往是这样，找一台电脑充当服务器的角色，每天24小时开机，其他每个人都从这个“服务器”仓库克隆一份到自己的电脑上，并且各自把各自的提交推送到服务器仓库里，也从服务器仓库中拉取别人的提交。一般我们使用GitHub进行文件托管服务，就类似中央服务器。

（顺便一提，昨晚用电信的校园网始终上不去GitHub，改了dns也没用，最后发现手机热点能上得去，而且还比较流畅，感谢中国移动！）

## 3.1创建SSH

本地Git仓库和GitHub仓库之间的传输是通过SSH加密的，所以，需要一点设置：

```
ssh-keygen -t rsa -C "youremail@example.com"
```

一路默认值下来，再使用ls对文件进行查看，发现用户主目录里找到了`.ssh`目录，里面有`id_rsa`和`id_rsa.pub`两个文件，这两个就是SSH Key的秘钥对，`id_rsa`是私钥，不能泄露出去，`id_rsa.pub`是公钥，可以放心地告诉任何人。

## 3.2与GitHub关联

进入github后进入“Account settings”，“SSH Keys”页面，填上title之后，粘贴`id_rsa.pub`文件内的内容，点“Add Key”，就能看到已经添加的Key

为什么GitHub需要SSH Key呢？因为GitHub需要识别出你推送的提交确实是你推送的，而不是别人冒充的，而Git支持SSH协议，所以，GitHub只要知道了你的公钥，就可以确认只有你自己才能推送。

当然，GitHub允许你添加多个Key。假定你有若干电脑，使用key就可以在每台电脑上往GitHub推送了。

在GitHub上免费托管的Git仓库，任何人都可以看到（但只有你自己才能改）。所以，不要把敏感信息放进去。

如果你不想让别人看到Git库，有两个办法，一个是交点保护费，让GitHub把公开的仓库变成私有的，这样别人就看不见了（不可读更不可写）。另一个办法是自己动手，搭一个Git服务器，因为是你自己的Git服务器，所以别人也是看不见的。

## 3.3建立远程仓库

登陆GitHub，然后，在右上角找到“Create a new repository”按钮，创建一个新的仓库。

输入名字，下面的初始化选项似乎还需要额外设置，我选择了readme，并按照提示（这火狐没有自动翻译看着英文真累）更改了仓库目录，点击创建就可以创建远程仓库了，但这个仓库还是空的，我们还需要将自己刚刚创建的本地仓库与之关联，在本地仓库目录运行命令

```
git remote add origin git@github.com:gaolening/git.git
```

github.com:后面的内容记得要改成自己的Github用户名，然后使用push命令将本地内容推送

```
git push -u origin master
```

由于远程库是空的，第一次推送`master`分支时，加上了`-u`参数，Git不但会把本地的`master`分支内容推送的远程新的`master`分支，还会把本地的`master`分支和远程的`master`分支关联起来，在以后的推送或者拉取时就可以简化命令。

推送成功后就可以在GitHub上看到与本地仓库一样的内容![QQ图片20210328034303](C:\Users\asus\Desktop\QQ图片20210328034303.jpg)

远程库的删除：想删除远程库，可以用`git remote rm <name>`命令。使用前，建议先用`git remote -v`查看远程库信息，然后，根据名字删除

```
git remote rm origin
```

origin即为远程库默认名字，一般没必要修改，此处的“删除”其实是解除了本地和远程的绑定关系，并不是物理上删除了远程库。远程库本身并没有任何改动。要真正删除远程库，需要登录到GitHub，在后台页面找到删除按钮再删除。

## 3.4从远程库克隆

如果先创建了远程库或者需要用远程库中拷贝内容到本地，可以使用clone命令

```
git clone git@github.com:gaolening/git.git
```

然后进入git目录查看，就会出现相应远程库中的文件，此操作便于多人协同开发。

## 四、相关操作

### 4.1版本回退

在git介绍时，我们已经提到过git可以方便地管理系统，提交git文件就相当于不断对游戏进行存档，随时可以回溯到以前的时间点。具体操作如下

可以使用git log命令查看之前提交过的文件版本 例

```
git log
commit 1094adb7b9b3807259d8cb349e7df1d4d6477073 (HEAD -> master)
Author: Michael Liao <askxuefeng@gmail.com>
Date:   Fri May 18 21:06:15 2018 +0800

    append GPL

commit e475afc93c209a690c39c13a46716e8fa000c366
Author: Michael Liao <askxuefeng@gmail.com>
Date:   Fri May 18 21:03:36 2018 +0800

    add distributed

commit eaadf4e385e865d25c48e7ca9c8395c3f7dfaef0
Author: Michael Liao <askxuefeng@gmail.com>
Date:   Fri May 18 20:59:18 2018 +0800

    wrote a readme file
```

可以加上`--pretty=oneline`参数：

```
git log --pretty=oneline
1094adb7b9b3807259d8cb349e7df1d4d6477073 (HEAD -> master) append GPL
e475afc93c209a690c39c13a46716e8fa000c366 add distributed
eaadf4e385e865d25c48e7ca9c8395c3f7dfaef0 wrote a readme file
```

注意：`commit id`（版本号）是一个SHA1计算出来的一个非常大的数字，用十六进制表示，每提交一个新版本，实际上Git就会把它们自动串成一条时间线。如果使用可视化工具查看Git历史，就可以更清楚地看到提交历史的时间线

当我们开始版本回退时，Git必须知道当前版本是哪个版本，在Git中，用`HEAD`表示当前版本，也就是最新的提交`1094adb...`（注意我的提交ID和你的肯定不一样），上一个版本就是`HEAD^`，上上一个版本就是`HEAD^^`，当然往上100个版本写100个`^`比较容易数不过来，所以写成`HEAD~100`。使用reset命令

```
git reset --hard HEAD^
HEAD is now at e475afc add distributed
```

那么是否还有方法回退到最新版本呢

```
git reset --hard 1094a			//1094a是版本号的前几位，git会自动进行寻找，但也不能只写一两位，避免多个文件无法确认
HEAD is now at 83b0afe append GPL
```

Git的版本回退速度非常快，因为Git在内部有个指向当前版本的`HEAD`指针，当你回退版本的时候，Git仅仅是把HEAD指向改变

但你回退到了某个版本，关掉了电脑，第二天早上就后悔了，想恢复到新版本怎么办？找不到新版本的`commit id`怎么办？Git提供了一个命令`git reflog`用来记录你的每一次命令

```
git reflog
e475afc HEAD@{1}: reset: moving to HEAD^
1094adb (HEAD -> master) HEAD@{2}: commit: append GPL
e475afc HEAD@{3}: commit: add distributed
eaadf4e HEAD@{4}: commit (initial): wrote a readme file
```

如此便能找到想要的版本号

### 4.2工作区与暂存区

#### 工作区（Working Directory）

就是你在电脑里能看到的目录，比如我的git文件夹就是一个工作区

#### 版本库（Repository）

工作区有一个隐藏目录`.git`，这个不算工作区，而是Git的版本库。

Git的版本库里存了很多东西，其中最重要的就是称为stage（或者叫index）的暂存区，还有Git为我们自动创建的第一个分支`master`，以及指向`master`的一个指针叫`HEAD`。

前面说了我们把文件往Git版本库里添加的时候，是分两步执行的：

第一步是用`git add`把文件添加进去，实际上就是把文件修改添加到暂存区；

第二步是用`git commit`提交更改，实际上就是把暂存区的所有内容提交到当前分支。

因为我们创建Git版本库时，Git自动为我们创建了唯一一个`master`分支，所以，现在，`git commit`就是往`master`分支上提交更改。

你可以简单理解为，需要提交的文件修改通通放到暂存区，然后，一次性提交暂存区的所有修改。

### 4.3撤销修改

`git checkout -- file`可以丢弃工作区的修改

命令`git checkout -- readme.txt`意思就是，把`readme.txt`文件在工作区的修改全部撤销，这里有两种情况：

一种是`readme.txt`自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态；

一种是`readme.txt`已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态。

总之，就是让这个文件回到最近一次`git commit`或`git add`时的状态。

但如果已经做了修改并提交到了暂存区呢？

用命令`git reset HEAD <file>`可以把暂存区的修改撤销掉（unstage），重新放回工作区：

```
git reset HEAD readme.txt
Unstaged changes after reset:
M	readme.txt
```

`git reset`命令既可以回退版本，也可以把暂存区的修改回退到工作区。当我们用`HEAD`时，表示最新的版本。

### 4.4删除文件

一般情况下，你通常直接在文件管理器中把没用的文件删了，或者用`rm`命令删了

```
rm test.txt
```

这个时候，Git知道你删除了文件，因此，工作区和版本库就不一致了，`git status`命令会立刻告诉你哪些文件被删除了

现在你有两个选择，一是确实要从版本库中删除该文件，那就用命令`git rm`删掉，并且`git commit`

另一种情况是删错了，因为版本库里还有呢，所以可以很轻松地把误删的文件恢复到最新版本

```
git checkout -- test.txt
```

`git checkout`其实是用版本库里的版本替换工作区的版本，无论工作区是修改还是删除，都可以“一键还原”。

注意：从来没有被添加到版本库就被删除的文件，是无法恢复的！

