### Description

Format text according to the given align mode written in C++

### Build

1. `mkdir build && cd build`
2. `cmake ..`
3. `make`
4. `make test`

For running the binary, `./formatter` and running the benchmark, `./benchmark`


#### Efficiency
Let's say that length of the total string = `N` and number of words = `W`

Time complexity = `O(W) + O(W)`
Space complexity = `O(W) + O(L)` where L = number of lines 

The approach uses `FormattedLine`. In the first iteration of words, For every formatted line, we keep track of `start_index`, `end_index`, `left_padding`, `right_padding` and with that information, during the second iteration, we construct the new formatted text

To measure some numbers, I created a benchmark tool and here are some numbers

```
Running benchmark: #0
TOTAL WORDS = 1000	COLUMN_WIDTH = 104	ALIGN_MODE = JUSTIFY
Time taken: 1277 us
Running benchmark: #1
TOTAL WORDS = 10000	COLUMN_WIDTH = 104	ALIGN_MODE = LEFT_ALIGN
Time taken: 6140 us
Running benchmark: #2
TOTAL WORDS = 100000	COLUMN_WIDTH = 104	ALIGN_MODE = JUSTIFY
Time taken: 83124 us
Running benchmark: #3
TOTAL WORDS = 1000000	COLUMN_WIDTH = 104	ALIGN_MODE = CENTER_ALIGN
Time taken: 612535 us
```
