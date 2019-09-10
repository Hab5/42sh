<img src="screenshots/screenshot.png" width="400" height="450">

# 42sh
42sh is a complete shell coded from scratch with a couple friend from the 42 school in Paris.  
It is written in "pure" C, we strictly limited our use of libraries (still allowing ourselves to use `malloc()`, `free()`, `dup2()` and rewrote everything that can reasonably be rewritten (90% of the standard libraries, including `printf` and such)  
*NO LEAKS, NO CRASHES*, seriously.

# Usage :
`git clone https://github.com/Hab5/42sh.git && cd 42sh && make && ./42sh`
You can use `--ast` or `-a` (e.g `./42sh --ast`) to display the AST (Abstract Syntax Tree) of your commands.  
(see above screenshot)

# Objectives:

- Advanced line edition with the [Termcaps Library](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html).
- Lexical analysis ("Lexing")
- Semantic analysis ("Parsing")
- Abstract Syntax Tree ("AST") population.
- AST Interpretation.
- Environment management.
- PATH management.
- Management of processes and their interactions.
- Terminal management.
- File descriptors management.

## Features

- Command execution
- Line edition with the [Termcaps Library](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html) (see `Bindings`)
- Job control: `jobs`, `fg`, `bg` and `&`.
- Redirections: `>`, `>>`, `<`, `<<`, `>&`, `<&`, `>&-` and `<&-`.
- Command delimitors: `;`, `|`.
- Logical operators: `|`, `||`, and `&&`.
- POSIX compliant builtins:
  - `cd`
  - `echo`
  - `type`
  - `exit`
  - `alias`
  - `hash`
  - `fc`
- Non-POSIX compliant builtins:
 - `test` with flags: `-b`, `-c`, `-d`, `-e`, `-f`, `-g`, `-L`, `-p`, `-r`, `-S`, `-s`, `-u`, `-w`, `-x`, `-z`, `=`, `!=`, `-eq`, `-ne`, `-ge`, `-lt`, `-le` and `!`.
- Signal handling (all of them).
- Inhibition: `'`, `"` and `\` alongside reprompt (+heredoc): 
    ```
    $> echo 'Hello,\
    backslash> World
    quote> ' "!
    dquote> "

    Hello,
    World!
    ```
- Internal shell variables management:
  - `set`
  - `export`
  - `<key>=<value>`
  - `unset`
- Advanced variables, tilde, and parameters [expansion](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02).
- History expansion: `!!`, `!-number`, `!number`, `!word`.
- History management: persistant history, iterative search, filtering (no doubles, `fc -s`, and similarly dangerous commands)

# Bindings

|Binding                         |Effect                        |
|--------------------------------|-----------------------------:|
|`Left/Right`                    |**Move the cursor**               |
|`PgUp/PgDown`                   |**Move the cursor to the next/previous word of the input**|
|`Home/End`                      |**Move the cursor to the the beginning/end of the input**|
|`Backspace`                     |**Delete the previous character from the input**|
|`Delete`                        |**Delete the next character from the input**|
|`Up/Down`                       |**Travel in the history**|
|`Shift+Left/Right`              |**Selection**|
|`Alt+X`                         |**Cut the selection**|
|`Alt+C`                         |**Copy the selection**|
|`Alt+V`                         |**Paste the selection**|
|`Ctrl+R`                        |**Iterative search in the history**|
|`Ctrl+C`                        |**Discard the current input and prompt on a new line**|
|`Ctrl+D`                        |**Exit**|

# Cloc (Count Line Of Code):

```
334 text files.
334 unique files.
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C                              322           1944           3977          14481
C/C++ Header                     9            342            408           1145
make                             2             62             47            400
Markdown                         1             11              0             39
-------------------------------------------------------------------------------
SUM:                           334           2359           4432          16065
-------------------------------------------------------------------------------
```
