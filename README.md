# duiduipeng
Find the best strategy for the DuiDuiPeng Game.

Definition:
- `num_buy` is the number of balls bought first time.
- `num_get` is the total number of balls get after the game.
- `num_current` is the total number of balls currently not used.
- `lucky_color` is selected, when the colar is lucky color, get one more ball.

Duiduipeng game:
- there are 10 kinds of the balls color, possibility of each one is 10%.
- place balls into the 3 * 3 grids until the grid is fully filled or `num_current==0`.
- check and update: 
  - `lucky_color` check: when got the the ball is `lucky_color`, add one more ball to `num_current`, **every lucky ball can be count once**.
  - `3 linked check`: if there are 3 balls with same color **continuously**, or in a **column**, or in the **diagnol** line, remove them and add 3 balls to `num_current`.
  - `2 same check`: if there are 2 balls with same, remove them and add one more to `num_current`.
  - `all different check`: if there are 9 balls in defferent color, remove them all and add 5 more to `num_current`.
  - `all clear check`: if all the balls in the grid are removed, them add 5 more to `num_current`. If the grid is cleared by `all different check`, then `all clear` will not be counted.


# Installation
Requirements:
- cmake >= 3.5 
- g++ or clang++ >= 11 

```bash
cmake -DCMAKE_BUILD_TYPE:STRING=Release -S. -Bbuild_cmake -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX # please select the proper the prefix path to install the program
cmake --build build_cmake --target duiduipeng
cmake --install build_cmake
```

# Usage

``` 
duiduipeng
    [-h --help]: show the help.
    [-n val]: the number of balls going to buy ( >= 1).
    [-t]: enter test mode, this will check all of the number to buy one buy one. If `-t` is set, `-n` will be overwritten (default: test [1-40]).
    [-tn val]: set the repeat number, as we are using Monte-Carlo method to simulate the problem ( >= 10, default 10,000).
```

# Results

## Test on [1 - 40]
```
duiduipeng -t 
=============
Test mode
Test every number test for 10000 times
Buy 1, average ratio: 1.120900, prices_per_ball: 0.892140
Buy 2, average ratio: 1.585000, prices_per_ball: 0.630915
Buy 3, average ratio: 1.367233, prices_per_ball: 0.731404
Buy 4, average ratio: 1.422050, prices_per_ball: 0.703210
Buy 5, average ratio: 1.464860, prices_per_ball: 0.682659
Buy 6, average ratio: 1.572267, prices_per_ball: 0.636024
Buy 7, average ratio: 1.659257, prices_per_ball: 0.602679
Buy 8, average ratio: 1.742675, prices_per_ball: 0.573830
Buy 9, average ratio: 1.829556, prices_per_ball: 0.546581
Buy 10, average ratio: 1.902180, prices_per_ball: 0.525713
Buy 11, average ratio: 1.964409, prices_per_ball: 0.509059
Buy 12, average ratio: 2.015542, prices_per_ball: 0.496145
Buy 13, average ratio: 2.066585, prices_per_ball: 0.483890
Buy 14, average ratio: 2.105143, prices_per_ball: 0.475027
Buy 15, average ratio: 2.136040, prices_per_ball: 0.468156
Buy 16, average ratio: 2.165825, prices_per_ball: 0.461718
Buy 17, average ratio: 2.192159, prices_per_ball: 0.456171
Buy 18, average ratio: 2.218228, prices_per_ball: 0.450810
Buy 19, average ratio: 2.241695, prices_per_ball: 0.446091
Buy 20, average ratio: 2.257210, prices_per_ball: 0.443025
Buy 21, average ratio: 2.277505, prices_per_ball: 0.439077
Buy 22, average ratio: 2.293255, prices_per_ball: 0.436062
Buy 23, average ratio: 2.308865, prices_per_ball: 0.433113
Buy 24, average ratio: 2.320962, prices_per_ball: 0.430856
Buy 25, average ratio: 2.333892, prices_per_ball: 0.428469
Buy 26, average ratio: 2.346019, prices_per_ball: 0.426254
Buy 27, average ratio: 2.357422, prices_per_ball: 0.424192
Buy 28, average ratio: 2.368454, prices_per_ball: 0.422216
Buy 29, average ratio: 2.372893, prices_per_ball: 0.421426
Buy 30, average ratio: 2.385287, prices_per_ball: 0.419237
Buy 31, average ratio: 2.391710, prices_per_ball: 0.418111
Buy 32, average ratio: 2.400428, prices_per_ball: 0.416592
Buy 33, average ratio: 2.404573, prices_per_ball: 0.415874
Buy 34, average ratio: 2.412600, prices_per_ball: 0.414491
Buy 35, average ratio: 2.421351, prices_per_ball: 0.412993
Buy 36, average ratio: 2.423217, prices_per_ball: 0.412675
Buy 37, average ratio: 2.428116, prices_per_ball: 0.411842
Buy 38, average ratio: 2.434345, prices_per_ball: 0.410788
Buy 39, average ratio: 2.441805, prices_per_ball: 0.409533
Buy 40, average ratio: 2.441363, prices_per_ball: 0.409607
```

## test on `num_buy = 10,000`

```
duiduipeng -n 10000
=============
Simu-mode
Buy 10000 balls
NUM_TEST_PER_NUMBER: 10000
Buy 10000, average ratio: 2.627779, prices_per_ball: 0.380549
```

## test on `num_buy = 100,000`

```
duiduipeng -n 100000 
=============
Simu-mode
Buy 100000 balls
NUM_TEST_PER_NUMBER: 10000
Buy 100000, average ratio: 2.628646, prices_per_ball: 0.380424
```

## Conclusion

- More balls bought at the first time, the better expectations can be. Finally the results converges to `2.628646`, which means that if you will get `2.628646 * N` with buying `N` balls.
- For small numbers, `num_buy = 2` is best and the expectation can be around `1.585`.
