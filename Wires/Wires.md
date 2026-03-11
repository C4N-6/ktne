# Wires

1. A wire module can have 3-6 wires on it.
2. Only the one correct wire needs to be cut to disarm the module.
3. Wire ordering begins with the first on the top.

## 3 Wires

| instruction     | cut wire |
| --------------- | -------- |
| 2 blue && 1 red | 2        |
| 0 red           | 2        |
| otherwise       | 3        |

## 4 Wires

| instruction          | cut wire |
| -------------------- | -------- |
| >=2 red && SN odd    | last red |
| last yellow && 0 red | 1        |
| 1 blue               | 1        |
| >=2 yellow           | 4        |
| otherwise            | 2        |

## 5 Wires

| instruction          | cut wire |
| -------------------- | -------- |
| last black && SN odd | 4        |
| 1 red && >=2 yellow  | 1        |
| 0 black              | 2        |
| otherwise            | 1        |

## 6 Wires

| instruction           | cut wire |
| --------------------- | -------- |
| 0 yellow && SN odd    | 3        |
| 1 yellow && ≥ 2 white | 4        |
| 0 red                 | 6        |
| otherwise             | 4        |
