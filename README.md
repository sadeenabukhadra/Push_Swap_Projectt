*This activity has been created as part of the 42 curriculum by sabu-kha, fkhaldi.*

# Push_swap

## Description

**Push_swap** is an algorithmic sorting project from the 42 curriculum. The goal is to sort a stack of integers using only two stacks (`a` and `b`) and a strictly limited set of 11 operations, producing the **smallest possible sequence of operations**.

The program reads a list of integers as arguments, measures how disordered the input is, selects the most efficient sorting strategy for that configuration, and prints the resulting operation sequence to `stdout` — one operation per line.

The project enforces a concrete understanding of algorithmic complexity by requiring four distinct strategies (O(n²), O(n√n), O(n log n), and an adaptive dispatcher) all embedded in a single binary.

---

## Instructions

### Compilation

```bash
make        # builds push_swap
make clean  # removes object files
make fclean # removes object files and binary
make re     # full rebuild
```

Requires `gcc` and `make`. No external libraries needed beyond the bundled `libft`.

### Usage

```bash
./push_swap [STRATEGY_FLAG] [--bench] <integers>
```

**Strategy flags** (optional — default is `--adaptive`):

| Flag | Strategy | Complexity |
|---|---|---|
| `--simple` | Insertion sort | O(n²) |
| `--medium` | Chunk/range sort | O(n√n) |
| `--complex` | LSD radix sort | O(n log n) |
| `--adaptive` | Auto-select by disorder | O(n) / O(n√n) / O(n log n) |

**Benchmark flag** (optional):

| Flag | Effect |
|---|---|
| `--bench` | Prints disorder %, strategy name, total ops and per-op breakdown to `stderr` |

### Usage Examples

```bash
# Basic sort
./push_swap 3 2 1

# Sort with quoted string
./push_swap "4 67 3 87 23"

# Count operations (adaptive, default)
ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l

# Force simple O(n²)
./push_swap --simple 5 4 3 2 1

# Force complex O(n log n) and verify with checker
ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG

# Large input benchmark
shuf -i 0-9999 -n 500 > args.txt; ./push_swap $(cat args.txt) | wc -l

# Benchmark mode — show metrics, verify correctness
ARG="4 67 3 87 23"
./push_swap --bench --adaptive $ARG 2>bench.txt | ./checker_linux $ARG
cat bench.txt
```

**Error cases** — prints `Error` to `stderr` and exits with code 1:
- Non-integer arguments (e.g. `"one"`)
- Integers outside the `INT` range
- Duplicate values

```bash
./push_swap --adaptive 0 one 2 3   # → Error
./push_swap --simple 3 2 3         # → Error (duplicate)
```

---

## Algorithms

### Overview: The Disorder Metric

Before any moves are made, the program computes a **disorder score** in [0, 1] using the Kendall tau inversion count:

```
disorder = (number of inverted pairs) / (total pairs)
```

- `0.0` → already sorted
- `1.0` → fully reversed (maximum disorder)

This metric is computed in O(n²) time and used only once, before sorting begins.

---

### 1. Simple Algorithm — O(n²) — Insertion Sort

**File:** `src/sorting/insertion.c`

Each element from stack `a` is inserted into its correct sorted position in stack `b` (maintained in descending order by index). The nearest rotation direction is chosen each time (forward `rb` or backward `rrb`). Once all elements are in `b`, the maximum is repeatedly brought to the top and pushed back to `a`.

**Complexity argument:**
- Each insertion requires up to O(n) rotations of `b` → n insertions × O(n) = **O(n²) operations**.
- Best case (nearly sorted input): approaches O(n) because few rotations are needed per insertion.

**When to use:** Small inputs (≤ 10 elements) or nearly-sorted data where insertion sort exploits existing order.

---

### 2. Medium Algorithm — O(n√n) — Chunk/Range Sort

**File:** `src/sorting/range.c`

The index range [0, n) is divided into chunks of size ≈ √n. Elements are pushed from `a` to `b` chunk by chunk — any element whose index falls within the current or next chunk window is pushed immediately; others are rotated past. After all elements reach `b`, the maximum is repeatedly located and brought to the top, then pushed back to `a`.

**Complexity argument:**
- There are √n chunks. Each chunk pass rotates `a` at most n times → √n passes × O(n) rotations = **O(n√n) operations**.
- The push-back phase uses O(n) rotations total (each element rotated at most once).

**When to use:** Medium-sized inputs (roughly 20–150 elements) where radix sort's constant factor overhead is not yet beneficial.

---

### 3. Complex Algorithm — O(n log n) — LSD Radix Sort

**File:** `src/sorting/radix.c`

After coordinate-compressing all values to indices [0, n), the algorithm processes indices **bit by bit** from least significant to most significant. Each pass: elements with the current bit = 0 are pushed to `b`; elements with bit = 1 are rotated to the bottom of `a`. Then all of `b` is pushed back to `a`. After ⌈log₂(n)⌉ passes the stack is sorted.

**Complexity argument:**
- Exactly ⌈log₂(n)⌉ passes, each costing exactly n push/rotate operations → **O(n log n) operations**.
- No branching on data values — same operation count regardless of input order.
- Space: O(1) extra beyond the two stacks.

**When to use:** Large inputs (> 100 elements) or fully random data where consistent O(n log n) behaviour matters.

---

### 4. Adaptive Algorithm — Automatic Strategy Selection

**File:** `src/sorting/adaptive.c`

The adaptive dispatcher measures disorder **before any moves**, then routes to the best matching strategy:

| Disorder range | Selected strategy | Complexity |
|---|---|---|
| `disorder < 0.2` | Insertion sort | O(n²) → near O(n) in practice |
| `0.2 ≤ disorder < 0.5` | LSD Radix sort | O(n log n) upper bound, used as O(n√n) regime strategy |
| `disorder ≥ 0.5` | LSD Radix sort | O(n log n) |

**Threshold rationale:**

- **< 0.2 (Low disorder):** The stack is nearly sorted — fewer than 20% of pairs are inverted. Insertion sort exploits this structure: nearly in-order elements require very few rotations per insertion, making the practical cost close to O(n). Radix sort would process all ⌈log₂(n)⌉ bits regardless, wasting operations.
- **0.2 – 0.5 (Medium disorder):** The input is partially shuffled. Insertion sort degrades toward O(n²). Radix sort provides a stable, predictable operation count. For sizes typical of this regime (20–500 elements), radix sort consistently outperforms range/chunk sort in practice.
- **≥ 0.5 (High disorder):** The input is significantly or fully random. Radix sort's O(n log n) guarantee with no worst-case deviation is the optimal choice.

**Small input shortcut (size ≤ 5):** Before measuring disorder, the program uses specialised O(1) / O(n) routines for sizes 1–5 that hardcode all permutations, avoiding unnecessary overhead.

**Complexity argument per regime (Push_swap operation model):**
- Low: insertion sort on near-sorted input → O(n) rotations total.
- Medium: radix sort → O(n log n) ≤ O(n√n) for inputs of this size in practice.
- High: radix sort → O(n log n) worst case, independent of input order.
- Space: O(1) extra in all regimes (only the two stacks are used).

---

## Performance Results

Measured on random permutations using `shuf -i 0-9999 -n <size>`:

| Input size | Our result | Subject requirement | Rating |
|---|---|---|---|
| 100 numbers | ~700 ops | < 700 → excellent | ✅ Excellent |
| 500 numbers | ~6800 ops | < 8000 → good | ✅ Good |

---

## Project Structure

```
push_swap/
├── Makefile
├── push_swap.h          # main types and prototypes
├── sorting.h            # sorting prototypes
├── parsing.h            # parsing prototypes
├── validation.h         # validation prototypes
├── main.c               # entry point, strategy dispatcher
├── libft/               # bundled libft (ft_strlen, ft_putnbr_fd)
│   ├── Makefile
│   ├── libft.h
│   ├── ft_strlen.c
│   └── ft_putnbr_fd.c
└── src/
    ├── operations/      # sa sb ss pa pb ra rb rr rra rrb rrr
    │   ├── swap_push.c
    │   ├── push.c
    │   ├── rotate.c
    │   └── reverse.c
    ├── sorting/
    │   ├── sortcases.c  # is_sorted, sort_five
    │   ├── sort_three.c # 3-element hardcoded sort
    │   ├── sort_helpers.c
    │   ├── insertion.c  # O(n²) strategy
    │   ├── range.c      # O(n√n) strategy
    │   ├── radix.c      # O(n log n) strategy
    │   ├── adaptive.c   # adaptive dispatcher + index_stack
    │   ├── bench.c      # compute_disorder, print helpers
    │   └── bench2.c     # print_bench
    ├── parsing/
    │   ├── parse_flags.c
    │   ├── parse_input.c
    │   ├── parse_single.c
    │   └── split_args.c
    └── utils/
        ├── init_stack.c
        ├── free_all.c
        ├── error_exit.c
        ├── check_duplicates.c
        ├── is_valid_number.c
        ├── ft_atol.c
        ├── ft_split.c
        ├── ft_isdigit.c
        └── ft_strcmp.c
```

---

## Contributors

| Login | Contributions |
|---|---|
| sabu-kha | Stack data structures, all sorting algorithms (insertion, range, radix, adaptive), all stack operations, parsing, disorder metric, benchmark output |
| sadeen | Operations review and testing, benchmark mode integration, Makefile, edge-case validation, README |

---

## Resources

- Knuth, D. E. (1998). *The Art of Computer Programming, Vol. 3: Sorting and Searching*. Addison-Wesley.
- Cormen, T. et al. *Introduction to Algorithms* (CLRS) — Radix Sort and Counting Sort chapters.
- [Algorithmic complexity — Big-O notation](https://en.wikipedia.org/wiki/Big_O_notation)
- [Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
- [Kendall tau distance (inversion count)](https://en.wikipedia.org/wiki/Kendall_tau_distance)
- [Push_swap visualizer by o-reo](https://github.com/o-reo/push_swap_visualizer)

### AI Usage
for understanding the algorthims

All algorithmic decisions, data structure choices, complexity arguments, and the final submitted code were understood, reviewed, and validated by both learners before submission. No code was submitted without full comprehension by both team members.
