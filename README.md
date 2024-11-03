# My Shell Project

## Status
Completed with basic and additional features.

## Bugs
- Bug Title: Command Not Found Error on Certain Inputs

Description:
When executing commands that do not exist or are mistyped, the shell correctly displays a "command not found" error. However, if the user inputs a command followed by a redirection (e.g., mycommand > output.txt) where mycommand is not a valid command, the shell crashes instead of handling the error gracefully. This issue occurs because the error handling for the command execution does not account for the presence of redirection operators.

## Features Implemented
- **Version 01**: Basic shell with prompt display, command input, forking and execution.
- **Version 02**: Input/output redirection and pipe support.
- **Version 03**: Background process handling.
- **Version 04**: Command history management.
- **Version 05**: Built-in commands (cd, exit, jobs, kill, help).
- **Version 06**: Variable management (if applicable).

