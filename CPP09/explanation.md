# CPP Module 09 — Explanation and Analysis

## The Big Picture

Module 09 is the capstone of the C++ STL series (modules 08-09). It is entirely about **applying STL containers to solve real problems** — not just knowing what a `map` or `stack` is, but choosing the right container for the right job, parsing real-world data formats, and implementing a non-trivial algorithm using container abstractions.

The three exercises form a progression:

1. **Ex00 (Bitcoin Exchange):** Associative container + file parsing. You need a container that maps dates to prices and supports "find the closest key less than or equal to X" — a perfect fit for `std::map` and its `lower_bound`/`upper_bound` operations.

2. **Ex01 (Reverse Polish Notation):** Stack-based evaluation. RPN is the canonical use case for a stack (LIFO) data structure. Simple, focused, and elegant.

3. **Ex02 (PmergeMe):** Sequence containers + a complex sorting algorithm. You must implement the Ford-Johnson (merge-insertion) sort using two different sequence containers and compare their performance.

The **module-specific constraint** that ties everything together: once you use a container in one exercise, you cannot use it again in a later exercise. This forces you to think about container selection strategically and understand what makes each container suited to different tasks.

A useful mental model: think of this module as a "container toolbox challenge." You have a toolbox full of STL containers, and each exercise is a job that needs the right tool. Once you use a tool, you put it away. The challenge is matching tools to jobs wisely.

---

## Exercise 00: Bitcoin Exchange

### Purpose

This exercise teaches **associative container usage** (specifically ordered maps), **file I/O and parsing**, **date handling**, and **error handling for messy real-world input**. It is the most "practical programming" exercise in the module — the kind of data processing task you encounter constantly in real software.

### Conceptual Foundation

**Associative containers** store key-value pairs and allow efficient lookup by key. In C++98, the primary associative containers are:

- `std::map<K,V>` — sorted by key, unique keys, O(log n) lookup/insert
- `std::multimap<K,V>` — sorted by key, duplicate keys allowed
- `std::set<K>` — sorted unique keys (no values)
- `std::multiset<K>` — sorted, duplicates allowed

`std::map` is the natural choice here because:
- You need to map dates (keys) to exchange rates (values)
- You need to find the closest date less than or equal to a given date
- `std::map::lower_bound()` returns an iterator to the first element whose key is **not less than** the given key
- `std::map::upper_bound()` returns an iterator to the first element whose key is **greater than** the given key

To find "the closest date that is less than or equal to the query date":
1. Call `lower_bound(date)`
2. If the iterator points to an element with key == date, use it directly
3. If the iterator points to an element with key > date (or end()), decrement the iterator to get the previous (lower) date
4. If the iterator is `begin()` and key > date, there is no valid earlier date — this is an error

**CSV parsing** is straightforward: read lines, split on delimiters (`,` for the database, ` | ` for the input file), convert strings to dates and numbers.

### Requirements

- **Program name:** `btc`
- **Files:** `Makefile`, `main.cpp`, `BitcoinExchange.cpp`, `BitcoinExchange.hpp`
- **Input:** Takes a file as command-line argument
- **Database:** A CSV file (`data.csv`) provided with the subject, containing `date,exchange_rate` pairs
- **Input file format:** Each line is `date | value`
  - Header line: `date | value`
  - Date format: `Year-Month-Day`
  - Value: float or positive integer, between 0 and 1000
- **Output format:** `date => value = result` where result = value * exchange_rate
- **Date lookup:** If the exact date is not in the DB, use the closest **lower** date
- **Error messages:**
  - No argument: `Error: could not open file.`
  - Negative number: `Error: not a positive number.`
  - Number > 1000: `Error: too large a number.`
  - Bad date/format: `Error: bad input => <input>`

### Design Decisions

**Class design:** The `BitcoinExchange` class should encapsulate the database. A clean approach:
- Constructor loads `data.csv` into a `std::map<std::string, double>` (or `std::map<std::string, float>`)
- A public method takes a filename, reads each line, validates it, looks up the rate, and prints the result
- Using `std::string` as the key for dates works because the `YYYY-MM-DD` format sorts lexicographically in chronological order

**Validation approach:** Parse each input line carefully:
- Check the ` | ` separator exists
- Validate the date format (correct number of digits, valid month 01-12, valid day 01-31, accounting for month lengths and leap years)
- Validate the value (parseable as a number, >= 0, <= 1000)
- Handle each error independently — one bad line should not stop processing

**Database file location:** The subject says the database is "provided with this subject." You should include `data.csv` in your `ex00/` directory. The program can look for it in a fixed relative path or accept it as a hardcoded path.

### Gotchas and Common Mistakes

1. **Date validation depth:** Simply checking format (`YYYY-MM-DD`) is not enough. You should validate that months are 1-12, days are valid for the given month, and handle February/leap years. The example shows `2001-42-42` as invalid — this is a format-valid but semantically-invalid date.

2. **The ` | ` separator:** Note the spaces around the pipe. Lines without this exact format are errors. Don't just split on `|` — require the spaces.

3. **Header line:** The first line of the input file is `date | value` — this is a header, not data. Skip it or handle it gracefully.

4. **lower_bound vs upper_bound:** Be precise. `lower_bound(key)` returns the first element >= key. If the key matches exactly, it returns that element. If not, it returns the next higher one, and you need to decrement to get the lower date. But check that you're not at `begin()` before decrementing.

5. **Edge case: date before all DB dates:** If someone queries a date earlier than any date in your database, there is no valid lower date. This should be an error.

6. **Floating-point precision:** The output `0.9`, `0.6`, `0.36` etc. from the example suggests you should not add excessive decimal places. Use default stream formatting or be mindful of precision.

7. **Empty lines / whitespace:** Handle gracefully without crashing.

8. **Value of 0:** Zero is valid (between 0 and 1000). Don't reject it.

### Connections

This exercise is self-contained. The key takeaway for the module constraint: if you use `std::map` here (the natural choice), you cannot use it in ex01 or ex02.

---

## Exercise 01: Reverse Polish Notation

### Purpose

This exercise teaches **stack-based evaluation**, which is one of the most classic applications of the stack data structure. RPN (postfix notation) is foundational in computer science — it is how many calculators work internally, how expression trees are evaluated, and how stack-based virtual machines (like the JVM bytecode interpreter) process instructions.

### Conceptual Foundation

**Reverse Polish Notation (RPN)**, also called **postfix notation**, places operators after their operands:

- Infix: `3 + 4` becomes RPN: `3 4 +`
- Infix: `(1 + 2) * 3` becomes RPN: `1 2 + 3 *`
- Infix: `3 + 4 * 5` becomes RPN: `3 4 5 * +` (because `*` has higher precedence)

**Evaluation algorithm** using a stack:
1. Read tokens left to right
2. If the token is a number, push it onto the stack
3. If the token is an operator (`+`, `-`, `*`, `/`):
   a. Pop two operands from the stack (the first popped is the right operand, the second is the left)
   b. Apply the operator: `left op right`
   c. Push the result back onto the stack
4. At the end, the stack should contain exactly one element — the result

**Why RPN needs no brackets:** The order of operations is entirely determined by the position of operators relative to operands. There is no ambiguity, no precedence rules needed.

**Stack** (`std::stack`): A LIFO (Last In, First Out) adapter. In C++98, `std::stack` is a container adapter (not a container itself) that wraps an underlying container (default: `std::deque`). Key operations: `push()`, `pop()`, `top()`, `empty()`, `size()`.

**Note on the examples in the subject:** The examples use `*` as multiplication, but the subject shows some unusual notation. Looking at the examples:
```
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"  => 42
./RPN "7 7 * 7 -"                    => 42
./RPN "1 2 * 2 / 2 * 2 4 - +"       => 0
```
The `=` characters in the subject's example output appear to be OCR artifacts or formatting issues — they should be `*` (multiplication). Verify: `8*9=72, 72-9=63, 63-9=54, 54-9=45, 45-4=41, 41+1=42`. Yes, that checks out.

### Requirements

- **Program name:** `RPN`
- **Files:** `Makefile`, `main.cpp`, `RPN.cpp`, `RPN.hpp`
- **Input:** Takes an RPN expression as a single command-line argument (string)
- **Numbers:** Always less than 10 (single digits). Intermediate results and the final result can be any value.
- **Operators:** `+`, `-`, `/`, `*`
- **No brackets or decimal numbers** need to be handled
- **Output:** The result on stdout
- **Errors:** Display error message on stderr (e.g., `Error`)

### Design Decisions

**Container choice:** `std::stack` is the obvious and correct choice. It is a container adapter, and the underlying container it uses (by default `std::deque`) is considered a separate container. Using `std::stack` should be fine.

If you used `std::map` in ex00, then `std::stack` (backed by `std::deque`) is a clean choice for ex01. Note: `std::stack` is an adapter, not technically a "container" in the STL classification, but it adapts an underlying container. The subject says "at least one container" — `std::stack` satisfies this since it uses `std::deque` internally, or you could use `std::deque` directly or `std::list`.

**Parsing:** Split the input string by spaces. Each token is either a single-digit number (0-9) or an operator (+, -, *, /). Anything else is an error.

**Error conditions:**
- Invalid token (not a digit or operator)
- Not enough operands on the stack when an operator is encountered (need at least 2)
- More than one value left on the stack after processing all tokens (too many operands)
- Division by zero
- Brackets or multi-digit numbers (subject says these are not handled — treat as errors)
- Empty input

**Operand order matters for subtraction and division:** When you pop two values, the first popped is the RIGHT operand and the second is the LEFT. So `5 3 -` means `5 - 3 = 2`, not `3 - 5`.

### Gotchas and Common Mistakes

1. **Operand order:** `a b -` means `a - b`, not `b - a`. When popping: first pop = right operand, second pop = left operand.

2. **Division by zero:** Must be handled. Output an error.

3. **Single number input:** `"42"` — wait, numbers must be less than 10. But `"5"` alone is valid: the stack has one element, and that's the result. Actually, the subject says numbers "passed as arguments" must be less than 10, so multi-digit numbers in the input are errors.

4. **Negative numbers in input:** The subject says numbers less than 10. A negative number like `-3` could be ambiguous with the minus operator. Since the subject doesn't require handling negative input numbers and says numbers < 10 (which could mean 0-9), treat `-` always as an operator.

5. **Error output goes to stderr** (`std::cerr`), not stdout.

6. **The subject's example `(1 + 1)` shows `Error`** — brackets are not handled and should produce an error.

### Connections

This is independent from ex00. The container constraint means: if you used `std::map` in ex00 and `std::stack` (or its underlying `std::deque`) in ex01, you need different containers for ex02. This naturally leads to `std::vector` and `std::list` for ex02 (or `std::deque` if you didn't use it via `std::stack`).

---

## Exercise 02: PmergeMe

### Purpose

This is the most challenging exercise in the module — and arguably one of the hardest in the entire C++ curriculum. It teaches:

1. **Algorithm implementation from specification** — translating a published algorithm (Ford-Johnson merge-insertion sort) into working code
2. **Container performance comparison** — implementing the same algorithm with two different containers and measuring the difference
3. **Sequence container operations** — deep understanding of how `std::vector` and `std::list` (or `std::deque`) differ in insertion, access, and iteration performance

### Conceptual Foundation

#### The Ford-Johnson (Merge-Insertion) Sort Algorithm

This algorithm, described in Knuth's "The Art of Computer Programming" Vol. 3, is designed to minimize the **number of comparisons** needed to sort a sequence. It is not the fastest in wall-clock time (due to overhead), but it uses fewer comparisons than quicksort or mergesort in many cases.

**The algorithm in three phases:**

**Phase 1 — Pair and Compare:**
- Given `n` elements, form `floor(n/2)` pairs
- Compare each pair: the larger becomes a "winner" (`a_i`), the smaller a "loser" (`b_i`)
- If `n` is odd, the leftover element becomes an extra loser
- Cost: `floor(n/2)` comparisons

**Phase 2 — Recursively Sort Winners:**
- Recursively apply merge-insertion sort to the array of winners `[a_1, a_2, ..., a_m]`
- After sorting, maintain the association: each `b_i` still knows which `a_i` it was paired with
- This is the "merge" part of "merge-insertion"

**Phase 3 — Insert Losers Using Jacobsthal Order:**
- Start the "main chain" as `[b_1, a_1, a_2, ..., a_m]` (b_1 < a_1 is known, so no comparison needed)
- Insert remaining `b_i` values into the main chain using binary insertion
- The insertion order follows **Jacobsthal-derived batch boundaries** `t_k = (2^(k+1) + (-1)^k) / 3`, giving: 1, 3, 5, 11, 21, 43, ...
- Within each batch, insert in **descending index order**
- When inserting `b_i`, only search the prefix of the main chain before `a_i`'s current position (since we know `b_i < a_i`)

**Why Jacobsthal order?** The key insight is that binary insertion into a list of `2^k - 1` elements uses exactly `k` comparisons in the worst case (the binary search tree is perfectly balanced). The Jacobsthal batching ensures each `b_i` is inserted into a prefix of size at most `2^k - 1` for the appropriate `k`, minimizing wasted comparisons.

#### Sequence Container Trade-offs

**`std::vector`:**
- Contiguous memory (cache-friendly)
- O(1) random access (good for binary search)
- O(n) insertion in the middle (must shift elements)
- Best when: you need fast random access and mostly append

**`std::list`:**
- Doubly-linked list (non-contiguous memory)
- O(1) insertion/deletion anywhere (given an iterator)
- O(n) access by index (must traverse)
- Best when: you need frequent insertions/deletions in the middle

**`std::deque`:**
- Segmented array (partially contiguous)
- O(1) random access (slightly slower than vector)
- O(n) insertion in the middle, O(1) at both ends
- A middle ground

For merge-insertion sort:
- `std::vector` benefits from fast binary search (random access) but pays for element shifting during insertion
- `std::list` benefits from fast insertion but cannot do efficient binary search (no random access)
- The performance comparison is genuinely interesting and depends on input size

### Requirements

- **Program name:** `PmergeMe`
- **Files:** `Makefile`, `main.cpp`, `PmergeMe.cpp`, `PmergeMe.hpp`
- **Input:** Positive integers as command-line arguments
- **Algorithm:** Ford-Johnson merge-insertion sort (explicitly required)
- **Containers:** Must use **at least two different containers**
- **Capacity:** Must handle at least 3000 different integers
- **Output format (4 lines):**
  1. `Before:` followed by the unsorted sequence
  2. `After:` followed by the sorted sequence
  3. `Time to process a range of N elements with std::[container1]: X.XXXXX us`
  4. `Time to process a range of N elements with std::[container2]: X.XXXXX us`
- **Errors:** Invalid input (negative numbers, non-numbers) should display error on stderr
- **Duplicates:** Handling is left to your discretion (you may reject or allow them)

**Important note from the subject:** "The indication of the time is deliberately strange in this example. Of course you have to indicate the time used to perform all your operations, both the sorting part and the data management part." This means the timing should include loading data into the container, not just the sort itself.

### Design Decisions

**Container choices:** The natural pair is `std::vector` and `std::deque` (or `std::list`). Since you've likely used `std::map` in ex00 and `std::stack`/`std::deque` in ex01:
- If you used `std::stack` (which wraps `std::deque` by default) in ex01, you may need to argue whether `std::deque` is "used" or not. To be safe, use `std::vector` and `std::list`.
- If you used a `std::stack<int, std::list<int>>` in ex01, then `std::deque` is free for ex02.

**Recommended safe combination:** `std::vector` and `std::list` (assuming `std::map` was used in ex00 and `std::stack` in ex01). Alternatively, `std::vector` and `std::deque`.

**Implementation strategy — "implement for each container":** The subject says "It is strongly advised to implement your algorithm for each container and thus to avoid using a generic function." This means: write the sort algorithm twice, once for `std::vector<int>` and once for `std::list<int>` (or `std::deque<int>`). Do NOT use templates. This is intentional — it forces you to deal with the different APIs and performance characteristics of each container.

**Timing:** Use `clock()` from `<ctime>` for C++98-compatible timing. Compute elapsed time as `(double)(end - start) / CLOCKS_PER_SEC * 1000000.0` for microseconds. Alternatively, use `gettimeofday()` from `<sys/time.h>` for higher resolution.

**Recursive implementation:** The Ford-Johnson algorithm is naturally recursive. The recursion depth is O(log n), so stack overflow is not a concern for 3000 elements.

**Maintaining pair associations:** This is the trickiest implementation detail. When you recursively sort the winners, you must track which loser belongs to which winner. Approaches:
- Use indices: store pairs as `(winner_index, loser_index)` and sort by winner value
- Use parallel arrays: maintain a `winners[]` and `losers[]` array, and when you swap/move winners during the recursive sort, move the corresponding losers too
- Use pairs: store `std::pair<int, int>` where first is the winner and second is the loser

### Gotchas and Common Mistakes

1. **Forgetting to reorder losers after sorting winners:** This is the #1 bug. After recursively sorting the winners array, the losers must be permuted to maintain the pairing. If `a[2]` moved to position `a[0]` in the sorted result, then `b[2]` must also move to position `b[0]`.

2. **Wrong Jacobsthal batch boundaries:** Off-by-one errors in computing `t_k` or in the batch index ranges. Double-check: batch 2 inserts indices 3 down to 2, batch 3 inserts 5 down to 4, etc. (1-indexed).

3. **Inserting `b_i` into the entire chain instead of the prefix before `a_i`:** The whole point of the algorithm is that you ONLY search the elements before `a_i`'s current position. This is what keeps comparison counts low.

4. **Descending order within batches:** Within each batch, insert from the highest index down to the lowest. Inserting in ascending order breaks the comparison count guarantees.

5. **Handling odd-length sequences:** When `n` is odd, the last element has no partner. It becomes an extra loser that gets inserted at the end (in the last batch, or after all batches).

6. **Binary search on `std::list`:** `std::list` does not support random access iterators, so you cannot use `std::lower_bound` efficiently (it degrades to O(n)). You must implement your own traversal-based binary search or accept the performance penalty. This is part of the exercise — understanding WHY vector is faster for binary search.

7. **Timing includes data management:** The subject explicitly says timing should include loading data into the container, not just the sort. Time the entire operation from parsing arguments into the container through to having the sorted result.

8. **Negative numbers and non-numeric input:** Must be detected and reported as errors. Zero is typically considered valid (it is a non-negative integer), though the subject says "positive integer sequence" — strictly, 0 is not positive. Check your evaluator's interpretation, but rejecting 0 is the safer choice given "positive."

9. **Integer overflow:** With values up to `INT_MAX` and 3000+ elements, be careful with parsing. Use `strtol` or similar and check for overflow.

10. **The output says `std::[.]`** — you should replace `[.]` with the actual container name, e.g., `std::vector` or `std::list`.

### Connections

This exercise uses the remaining containers not consumed by ex00 and ex01. It is the culmination of the module — bringing together container knowledge, algorithm implementation, and performance analysis.

---

## Deeper Lessons

### 1. Container Selection Is a Design Decision

The entire module is structured around the idea that different containers have different strengths. A `std::map` excels at ordered key-value lookup. A `std::stack` is perfect for LIFO processing. A `std::vector` offers cache-friendly random access. A `std::list` offers cheap insertion. There is no "best" container — only the best container for a given problem. This is the **principle of fitness for purpose**.

### 2. Algorithms and Data Structures Are Inseparable

Exercise 02 makes this viscerally clear. The same algorithm (Ford-Johnson) behaves differently depending on the underlying container. Binary search is O(log n) on a vector but O(n) on a list. Insertion is O(n) on a vector but O(1) on a list (given an iterator). The total performance depends on the interplay between algorithm and data structure — you cannot analyze one without the other.

### 3. Parsing and Validation Are First-Class Engineering Concerns

Exercises 00 and 01 are fundamentally about **robust input handling**. Real-world programs spend enormous effort on parsing, validation, and error reporting. The subject demands specific error messages for specific failure modes — this mirrors production software where clear error messages are essential for debugging and user experience.

### 4. The Value of Knowing Classic Algorithms

Ford-Johnson sort is not used in production, but understanding it teaches you:
- How to read and implement an algorithm from a formal specification
- How comparison complexity differs from time complexity
- How clever ordering (Jacobsthal batches) can optimize seemingly simple operations
- The gap between theoretical optimality and practical performance

### 5. Separation of Concerns

Each exercise naturally separates: data loading, validation, processing, and output. The `BitcoinExchange` class encapsulates the database. The `RPN` class encapsulates evaluation logic. The `PmergeMe` class encapsulates sorting. This is the **Single Responsibility Principle** in action.

### 6. Understanding Performance Requires Measurement

Exercise 02 requires you to **measure** performance, not just theorize. This is a core engineering principle: profile before optimizing, measure before claiming. The fact that `std::vector` often outperforms `std::list` despite having worse theoretical insertion complexity (due to cache effects and memory locality) is a lesson that Big-O notation tells only part of the story.

### 7. Constraints Drive Creativity

The "no container reuse" rule forces you to think about alternatives you might never consider otherwise. Constraints — whether imposed by a school project or by real-world requirements (memory limits, API restrictions, backward compatibility) — often lead to deeper understanding and more creative solutions.


Check out the existing subject and explanation. Then check out my current manual implementation of ex02. This must be polished and refactored, ready for my eval. There are many complicated methods/functions that would benefit from explanations, please take care of that. All parsing functions must be in the main file. Adjust parsing so that the parsing function takes a reference to a vec and a deque and fills both at the same time. Parsing must happen outside of any performance measurements. Make sure everything follows the subjects and our own rules from CLAUDE.md, and if not, refactor it. Especially the public variables can all be made private with public getters, for example those of WinnerNode. We must only have a public function `unsigned int sort(const &in, &out) const` that is overloaded with both vec and deque as in & out. This will call the appropriate internal recursive sorting function, which must also be overloaded for both vec and deque. We must not use templates for this exercise. The PmergeMe class becomes a non-instantiable class with only static member functions. The WinnerNode container is created via a utility function which is called in the public static sort method. The sort function returns the comparison count for the whole sort operation. There must be a debug rule added to the Makefile building the exercise with the DEBUG def. In DEBUG builds we enable the enable the expectedFordJohnsonComparisons function. Debug mode the main can be an entirely different main. It must make tests to confidently say that our implementation is correct. Outputs must be verified against correct sorted list and the expected maximum sort count. It must print a log of what was tested. Tests need to cover hardcoded cases and randomly generated cases.
