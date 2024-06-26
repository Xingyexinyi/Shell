
# MyShell

MyShell 是一个用 C++ 实现的简单 Linux Shell 程序，支持命令输入、执行和显示执行结果的功能。该 Shell 还支持脚本编程、I/O 重定向和管道功能。

## 功能

1. **命令输入与执行**：可以输入和执行基本的 Linux 命令，并显示执行结果。
2. **脚本执行**：支持执行简单的 Shell 脚本。
3. **I/O 重定向和管道**：支持标准输入输出的重定向和管道操作。

## 文件结构

- `main.cpp`：主程序文件，包含主函数，负责启动 Shell 或执行脚本。
- `shell.h`：头文件，包含辅助功能的声明和必要的包含指令。
- `shell.cpp`：实现头文件中声明的函数，负责命令解析、执行和 Shell 逻辑。

## 编译和运行

### 编译

确保所有文件都在同一个目录下，然后使用以下命令编译程序：

```sh
g++ -o myshell main.cpp shell.cpp
```

### 运行

#### 交互式 Shell

运行以下命令启动交互式 Shell：

```sh
./myshell
```

启动后，您可以在提示符 `myshell>` 后输入 Linux 命令，并查看执行结果。

#### 执行脚本

运行以下命令执行 Shell 脚本文件：

```sh
./myshell script.sh
```

`script.sh` 是包含要执行命令的脚本文件。

## 使用示例

### 交互式 Shell 示例

```sh
myshell> ls -l
total 40
-rwxr-xr-x 1 user user 12345 Jun 26 10:00 myshell
-rw-r--r-- 1 user user  1234 Jun 26 10:00 script.sh
myshell> echo "Hello, World!"
Hello, World!
myshell> exit
```

### 脚本执行示例

假设 `script.sh` 文件内容如下：

```sh
echo "Running script..."
ls -l
echo "Script finished."
```

执行脚本：

```sh
./myshell script.sh
```

输出：

```sh
Running script...
total 40
-rwxr-xr-x 1 user user 12345 Jun 26 10:00 myshell
-rw-r--r-- 1 user user  1234 Jun 26 10:00 script.sh
Script finished.
```

### I/O 重定向和管道示例

```sh
myshell> echo "Hello, World!" > output.txt
myshell> cat < output.txt
Hello, World!
myshell> cat < output.txt | grep Hello
Hello, World!
```
