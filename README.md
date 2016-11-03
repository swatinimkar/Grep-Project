# SNGREP
Swati Nimbolkar - 141603007

# Description
This is linux GREP command implementation in C.

I have included the following features of GREP in my project
- Search for entered string in file.
- Check the entered pattern in multiple files.
- Case insensitive search.
- Search entered pattern in file using regular expression.
- Search for full word in file.
- Invert Match.
- Display the lines which does not matches all the given pattern.
- Count number of matches.
- Show line number while displaying the output.
- Display only file names which matches the given pattern.
- Show the position of match in the line.
- Search pattern recursively into directory and sub-directory.
## Usage

```
sngrep [[arguments] pattern | FILE ] [FILES] ...
```

## Example

#### test.txt
```
THIS LINE IS THE 1ST UPPER CASE LINE IN THIS FILE.
this line is the 1st lower case line in this file.
This Line Has All Its First Character Of The Word With Upper Case.

Two lines above this line is empty.
And this is the last line.
```

#### Syntax
```
sngrep "string" filename
```

#### Command
```
sngrep "this" test.txt
```

#### Output
```
this line is the 1st lower case line in this file.
Two lines above this line is empty.
And this is the last line.
```
