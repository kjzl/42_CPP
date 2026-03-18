# Merge-Insertion Sort (Ford–Johnson) — Implementation-Focused Notes  
*Goal: enough understanding to implement from scratch.*

## 1. What you’re implementing
A comparison sort that minimizes comparisons by:

1) Pairing elements  
2) Recursively sorting the larger elements  
3) Inserting the smaller elements using **binary insertion** in a special **Jacobsthal-based order**

---

## 2. Step-by-step algorithm

### Step A — Pair up and split into winners/losers
Input: array `d` of length `n` (all distinct for simplicity).

1. Make `m = floor(n/2)` pairs: `(d[i], d[i+m])` for `i=0..m-1`
2. For each pair, compare once:
   - `a[i] = max(pair)`
   - `b[i] = min(pair)`
3. If `n` is odd, the last element becomes an extra `b`:
   - `b[m] = d[n-1]`
So:
- `a` has length `m`
- `b` has length `ceil(n/2)`

---

### Step B — Recursively sort the winners
Sort `a` using Merge-Insertion recursively.

Important: after sorting `a`, you must reorder the `b`’s to keep the relation  
**“this b belongs to this a”**.

Implementation approach:
- Store pairs `(a_i, b_i)` before recursion.
- After recursion returns sorted `a`, rebuild `b` by looking up each `a_i`’s partner.

---

### Step C — Insert the losers in Ford–Johnson order
Start the main chain with:
- `[b1, a1, a2, ..., a_m]` (1-indexed conceptually)
Because `b1 < a1`, you place it without comparisons.

Now insert `b2..b_{ceil(n/2)}` in **Jacobsthal batch order**.

#### Batch boundary numbers `t_k`
Compute:
\[
t_k = \frac{2^{k+1} + (-1)^k}{3}
\]
This gives: `1, 3, 5, 11, 21, 43, ...`

You will insert `b`’s in batches:
- batch 2 inserts `b3, b2`
- batch 3 inserts `b5, b4`
- batch 4 inserts `b11, b10, ..., b6`
- etc.

General batch `k`:
- indices `t_{k-1}+1 ... t_k`
- insert in descending order: `b[t_k], b[t_k-1], ..., b[t_{k-1}+1]`
Skip indices beyond `ceil(n/2)`.

#### Where to insert `b_i`
Because you know `b_i < a_i`, when inserting `b_i` you only search in the prefix **before `a_i`** in the current main chain.

So you need:
- find the current position (rank) of `a_i` inside the main chain,
- binary-insert `b_i` into the subarray `[0 .. pos(a_i)-1]`.

---

## 3. Binary insertion (what you actually code)

Binary insertion into a sorted list segment `[L..R)`:
- returns the insertion position `p` such that after inserting, order is preserved.

You can implement standard binary search style insertion:
- compare with a “middle” element repeatedly.

Optional (average-case improvement): use a slightly **left-biased** binary insertion tree, but standard binary insertion is fine for a correct first implementation.

---

## 4. Data structure choice (important)

During Step C you insert many elements into the middle.

If you use a plain array/vector:
- insertion costs `O(n)` shifting each time (works fine for learning / small inputs)

If you want better asymptotic time:
- use a structure supporting “insert at index” in ~`O(log n)`:
  - balanced tree with subtree sizes (order-statistics tree),
  - rope-like tree,
  - Fenwick tree with indirect placement, etc.

For “implement from scratch” learning, an array-based approach is acceptable.

---

## 5. Pseudocode skeleton

### Helper: generate `t_k` values up to needed range
- Keep computing `t_k` until `t_k >= ceil(n/2)`.

### MergeInsertion(d)
1. if `n <= 1`: return d
2. Pairing step: build arrays `a`, `b`
3. Recursively sort `a`
4. Reorder `b` to match sorted `a`
5. Build main chain `chain = [b1] + a`
6. Insert remaining `b`’s in Jacobsthal order:
   - for each batch k:
     - for i from min(t_k, |b|) down to t_{k-1}+1:
       - insert `b[i]` into prefix before `a[i]` using binary insertion
7. return chain

---

## 6. Common mistakes checklist

- You forget to reorder `b` after sorting `a`.
- You insert `b_i` into the *entire chain* instead of stopping before `a_i`.
- Your Jacobsthal batch boundaries are wrong (off-by-one / indexing mixups).
- You implement insertion order ascending instead of descending inside each batch.
- You mishandle odd `n` (extra `b` without a partner `a`).

---

## 7. What you should understand after reading this
- Why pairing is done (creates `a_i > b_i` constraints).
- Why we sort only the `a`’s recursively.
- Why we can restrict insertion of `b_i` to the prefix before `a_i`.
- How Jacobsthal-based batching gives a good comparison bound.
- How to implement the algorithm end-to-end.
