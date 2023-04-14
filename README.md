### Description

Format text according to the given align mode written in C++

### Build

1. `mkdir build && cd build`
2. `cmake ..`
3. `make`
4. `make test`

For running the binary, `./formatter` and running the benchmark, `./benchmark`


### Misc

#### Correctness
I have tested the logic with various edge cases and also compared the output with google docs with alignment running over there and comparing to the program output

#### Input validation / Error handling
For ASCII, I also included numerics because they can be part of words ( eg. 1500s ) but will print an error to STDERR when we encounter non-alphanumeric or spaces. Same goes with words that are longer than column width

Note: Some confusion regarding ASCII which generally includes all chars from 0 - 255 but in the description, it was mentioned lowercase ASCII and uppercase ASCII. So I assumed that we just only alphanumerics. Anyways, if we want to change the condition, it's just one line change in `utils.hpp`

#### Efficiency
Let's say that length of the total string = `N` and number of words = `W`

Time complexity = `O(W) + O(W)`
Space complexity = `O(W) + O(L)` where L = number of lines 

My first approach was quite similar to the current one but instead of using `FormattedLine` struct which keeps track of indices, I was using temporary strings to format. Copying strings multiple times added complexity and made it `O(W^2)`

The optimised approach uses `FormattedLine`. In the first iteration of words, For every formatted line, we keep track of `start_index`, `end_index`, `left_padding`, `right_padding` and with that information, during the second iteration, we construct the new formatted text

To measure some numbers, I created a benchmark tool and here are some numbers

```
Running benchmark: #0
TOTAL WORDS = 1000	COLUMN_WIDTH = 104	ALIGN_MODE = CENTER_ALIGN
Time taken: 869 us
Running benchmark: #1
TOTAL WORDS = 10000	COLUMN_WIDTH = 104	ALIGN_MODE = CENTER_ALIGN
Time taken: 6027 us
Running benchmark: #2
TOTAL WORDS = 100000	COLUMN_WIDTH = 104	ALIGN_MODE = CENTER_ALIGN
Time taken: 57974 us
Running benchmark: #3
TOTAL WORDS = 1000000	COLUMN_WIDTH = 104	ALIGN_MODE = RIGHT_ALIGN
Time taken: 570537 us
```

#### Extensibility
All the padding logic is encapsulated under one under lambda function `construct`. If we want to add new align modes, we just need to add another `switch` case


#### Test Coverage and Code quality
No unused imports, confusing statements, sane variable namings were used. And to validate the correctness, test coverage was essential