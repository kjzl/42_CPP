# Merge-Insertion Sort (Ford–Johnson) — Detailed Learning Notes  
*Focus: Jacobsthal / Ford–Johnson insertion order, why it saves comparisons, and how to reason about it.*

## 0. What this algorithm is (and why people care)

**Merge-Insertion sort**, also called the **Ford–Johnson algorithm**, is a classic **comparison-based sorting algorithm** designed to use *very few comparisons*—often extremely close to the **information-theoretic lower bound** `log2(n!) ≈ n log2 n − 1.4427 n`.

It is mostly studied for:
- **Minimum-comparison sorting** (decision-tree optimality questions).
- Understanding how to “spend” comparisons more efficiently than standard mergesort/quicksort.

It is *not* mainly used in production libraries, because real performance also depends heavily on memory access patterns, constant factors, and implementation complexity. But as a *comparison-count* benchmark, it is famous.

---

## 1. High-level idea in one paragraph

Ford–Johnson works in three phases:

1. **Pair elements** and compare within each pair to get a “winner” (larger) and “loser” (smaller).
2. **Recursively sort the winners** (the larger elements).
3. **Insert the losers** into the already-sorted winners using **binary insertion**, but in a *special order* (determined by the Jacobsthal sequence) so that many insertions happen into lists of size `2^k − 1`, which guarantees **exactly `k` comparisons in the worst case** for that insertion.

The *magic* is the insertion order: it ensures strong worst-case guarantees and also tends to be good on average.

---

## 2. Phase 1: Pairing (tournament step)

Given `n` distinct elements.

- Form `⌊n/2⌋` pairs.
- Compare each pair once.
- For pair `i`, call the larger element `a_i` and smaller `b_i`, so `a_i > b_i`.

If `n` is odd, one element is unpaired; it becomes an extra `b` element (conceptually, `b_{⌈n/2⌉}`).

**Comparisons used:** `⌊n/2⌋` always.

### Why pairing is useful
Each comparison creates a *known relation* (`a_i > b_i`). Those relations shrink uncertainty and let later steps insert elements into restricted ranges with fewer comparisons.

---

## 3. Phase 2: Recursively sort the `a`’s

Recursively sort the list:
- `A = [a_1, a_2, ..., a_{⌊n/2⌋}]`

After sorting, relabel so:
- `a_1 < a_2 < ... < a_m` where `m = ⌊n/2⌋`
- each `b_i` stays attached to its original `a_i` (because we still know `a_i > b_i`)

This is important: after recursion, the `a_i` are in increasing order, and each `b_i` is known to be **less than its associated** `a_i`.

---

## 4. Phase 3: Insert the `b`’s — the core of Ford–Johnson

### 4.1 Main chain idea
We build a sorted structure called the **main chain**.

Start with:
- `b_1` and `a_1` can be placed without a comparison because we know `b_1 < a_1`.
So initial chain:  
`[b_1, a_1, a_2, ..., a_m]`  
(then we insert more `b`’s into it)

### 4.2 Key constraint: where can `b_i` go?
Because `b_i < a_i`, when inserting `b_i` we **never need to compare it against elements ≥ a_i**.

So `b_i` is inserted into the prefix ending right before `a_i`.

If we know the prefix length, we can binary-insert in that prefix.

### 4.3 The Jacobsthal-based insertion order
The algorithm inserts the `b`’s in carefully chosen **batches**.

Define a sequence (related to Jacobsthal numbers) via:
\[
t_k = \frac{2^{k+1} + (-1)^k}{3}
\]
For `k = 1,2,3,4,...` this gives:
- `t_1 = 1`
- `t_2 = 3`
- `t_3 = 5`
- `t_4 = 11`
- `t_5 = 21`
- `t_6 = 43`
- ...

These `t_k` values define batch boundaries.

**Insertion order (batch k):** insert  
`b_{t_k}, b_{t_k-1}, ..., b_{t_{k-1}+1}`  
(i.e., descending indices within the batch)

The first non-trivial batch is `b_3, b_2` (since `t_2=3, t_1=1`).

### 4.4 Why this order matters (intuition)
Ford–Johnson wants many inserts to happen into lists with lengths close to:
\[
2^k - 1
\]
because binary insertion into `2^k - 1` elements costs **exactly `k` comparisons** in the worst case (a perfectly full decision tree).

The Jacobsthal scheduling is designed so that:
- every `b_i` in batch `k` is inserted into **at most** `2^k − 1` elements.

That gives tight control over worst-case comparisons.

---

## 5. Binary insertion details (and decision trees)

### 5.1 Binary insertion is not unique
When inserting into a sorted list of length `m`, the *worst case* is `⌈log2(m+1)⌉` comparisons.

But in the **average case**, the exact number depends on:
- which positions (gaps) are more likely,
- and which positions get shorter paths in the decision tree.

### 5.2 “Left-biased” binary insertion can be better here
In Merge-Insertion, insertion positions are **not uniformly likely**—the paper “On the Average Case of MergeInsertion” observes **left positions are slightly more likely**.

Therefore, choose a binary insertion decision tree that assigns **shorter paths to left positions**.  
This is often called **left strategy** (or *right-hand binary search* in some literature).

Practical takeaway:
- If you want best average comparisons, implement binary insertion so that the `(k−1)`-comparison leaves lie on the left side whenever the decision tree isn’t perfectly balanced.

---

## 6. Comparison counting: the recurrence

Let:
- `F(n)` = average (or worst-case) comparisons to sort `n`
- `G(m)` = comparisons spent in the insertion phase when inserting `m = ⌈n/2⌉` smaller elements into the winners

Then (standard Ford–Johnson recurrence):
\[
F(n) = \left\lfloor \frac{n}{2} \right\rfloor \;+\; F\!\left(\left\lfloor \frac{n}{2} \right\rfloor\right)\;+\;G\!\left(\left\lceil \frac{n}{2} \right\rceil\right)
\]

- `⌊n/2⌋` is the pairing cost
- recursion sorts the winners
- insertion cost is the hard part

---

## 7. Concrete “how the insertion works” example (conceptual)

Suppose after sorting the `a`’s you have:

- Sorted winners: `a1 < a2 < a3 < a4 < a5 ...`
- Each `bi < ai`

Start chain:
- `[b1, a1, a2, a3, a4, a5, ...]`

Insert in Jacobsthal order:
- batch 2: `b3, b2`
  - insert `b3` into prefix before `a3`
  - insert `b2` into prefix before `a2`
- batch 3: `b5, b4`
- batch 4: `b11, b10, ..., b6`
- ...

Important operational detail:
- after each insertion, positions shift; implement using a data structure that supports insertion efficiently (e.g., linked structure, balanced tree, Fenwick/bit-indexed “order statistics” structure, etc.)

---

## 8. Implementation considerations (practical engineering)

### 8.1 Data structure choice
A naive array insertion is `O(n)` movement per insert, leading to `O(n^2)` time, which defeats the point.

Common approaches:
- **Linked list**: easy insertion, but binary search is hard (no random access).
- **Balanced binary tree / order-statistics tree**: supports “insert at rank” and “compare along path” patterns.
- **Fenwick tree / BIT**: if you store positions indirectly.
- **Rope-like tree**: good if you want near-log insertion and indexing.

If your goal is “learn the algorithm” rather than fastest wall-clock performance, you can:
- implement using arrays but accept `O(n^2)` moves for small `n`, OR
- implement using a list + manual binary search by traversing (but then insertion search becomes slower), OR
- implement using a balanced tree library structure if available.

### 8.2 Carrying pair associations correctly
After recursively sorting the `a`’s, you must permute the associated `b`’s accordingly.  
You can do this by storing pairs `(a_i, b_i)` and then reordering `b` after sorting `a`.

---

## 9. One-line summaries of “proof facts” you usually rely on
(We don’t include full proofs here.)

- **Correctness:** Sorting winners + inserting losers into correct restricted prefixes yields a fully sorted sequence.
- **Worst-case comparison control:** Jacobsthal batch boundaries ensure each `b` in batch `k` inserts into at most `2^k − 1` elements ⇒ at most `k` comparisons for that insertion.
- **Near-optimality:** Total comparisons come close to `log2(n!)` for many `n`.

---

## 10. Summary: what to remember

- Pairing creates `a_i > b_i` constraints.
- Recursively sort `a`’s.
- Insert `b`’s in Jacobsthal (Ford–Johnson) order, inserting each `b_i` only into the prefix before its associated `a_i`.
- Use a binary insertion strategy (often left-biased) that matches the non-uniform insertion position distribution.

---

## 11. Mini glossary

- **Main chain:** the sorted structure containing all `a`’s plus already-inserted `b`’s.
- **Binary insertion:** insert into a sorted list using a binary-search-like comparison tree.
- **Jacobsthal sequence / schedule:** used to define batch boundaries `t_k` in Ford–Johnson insertion order.
- **Information-theoretic lower bound:** at least `⌈log2(n!)⌉` comparisons are needed by any comparison sort in the worst case.
