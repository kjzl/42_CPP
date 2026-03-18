# On the Average Case of MergeInsertion

Florian Stober and Armin Weiß [ 0000-0002-7645-5867 ]

###### Abstract

MergeInsertion, also known as the Ford-Johnson algorithm, is a sorting algorithm which, up to today, for many input sizes achieves the best known upper bound on the number of comparisons. Indeed, it gets extremely close to the information-theoretic lower bound. While the worst-case behavior is well understood, only little is known about the average case. This work takes a closer look at the average case behavior. In particular, we establish an upper bound of $n\log n-1.4005n+o(n)$ comparisons. We also give an exact description of the probability distribution of the length of the chain a given element is inserted into and use it to approximate the average number of comparisons numerically. Moreover, we compute the exact average number of comparisons for $n$ up to 148. Furthermore, we experimentally explore the impact of different decision trees for binary insertion. To conclude, we conduct experiments showing that a slightly different insertion order leads to a better average case and we compare the algorithm to the recent combination with (1,2)-Insertionsort by Iwama and Teruyama.

###### Keywords:

MergeInsertion Minimum-comparison sort Average case analysis.

## 1 Introduction

Sorting a set of elements is an important operation frequently performed by many computer programs. Consequently there exist a variety of algorithms for sorting, each of which comes with its own advantages and disadvantages.

Here we focus on comparison based sorting and study a specific sorting algorithm known as MergeInsertion. It was discovered by Ford and Johnson in 1959 *[5]*. Before D. E. Knuth coined the term MergeInsertion in his study of the algorithm in his book “The Art of Computer Programming, Volume 3: Sorting and Searching” *[7]*, it was known only as Ford-Johnson Algorithm, named after its creators. The one outstanding property of MergeInsertion is that the number of comparisons it requires is close to the information-theoretic lower bound of $\log(n!)\approx n\log n-1.4427n$ (for sorting $n$ elements). This sets it apart from many other sorting algorithms. MergeInsertion can be described in three steps: first pairs of elements are compared; in the second step the larger elements are sorted

recursively; as a last step the elements belonging to the smaller half are inserted into the already sorted larger half using binary insertion.

In the worst case the number of comparisons of MergeInsertion is quite well understood *[7]* – it is $n\log n+b(n)\cdot n+o(n)$ where $b(n)$ oscillates between $-1.415$ and $-1.3289$. Moreover, for many $n$ MergeInsertion is proved to be the optimal algorithm in the worst case (in particular, for $n\leq 15$ *[9, 10]*). However, there are also $n$ where it is not optimal *[8, 2]*. One reason for this is the oscillating linear term in the number of comparisons, which allowed Manacher *[8]* to show that for certain $n$ it is more efficient to split the input into two parts, sort both parts with MergeInsertion, and then merge the two parts into one array.

Regarding the average case not much is known: in *[7]* Knuth calculated the number of comparisons required on average for $n\in\{1,\ldots,8\}$; an upper bound of $n\log n-1.3999n+o(n)$ has been established in *[3]*. Most recently, Iwama and Teruyama *[6]* showed that in the average case MergeInsertion can be improved by combining it with their (1,2)-Insertion algorithm resulting in an upper bound of $n\log n-1.4106n+O(\log n)$. This reduces the gap to the lower bound by around 25%. It is a fundamental open problem how close one can get to the information-theoretic lower bound of $n\log n-1.4427n$ (see e. g. *[6, 11]*).

The goal of this work is to study the number of comparisons required in the average case. In particular, we analyze the insertion step of MergeInsertion in greater detail. In general, MergeInsertion achieves its good performance by inserting elements in a specific order that in the worst case causes each element to be inserted into a sorted list of $2^{k}-1$ elements (thus, using exactly $k$ comparisons). When looking at the average case elements are often inserted into less than $2^{k}-1$ elements which is slightly cheaper. By calculating those small savings we seek to achieve our goal of a better upper bound on the average case. Our results can be summarized as follows:

- We derive an exact formula for the probability distribution into how many elements a given element is inserted (Theorem 2). This is the crucial first step in order to obtain better bounds for the average case of MergeInsertion.
- We experimentally examine different decision trees for binary insertion. We obtain the best result when assigning shorter decision paths to positions located further to the left.
- We use Theorem 2 in order to compute quite precise numerical estimates for the average number of comparisons for $n$ up to roughly 15000.
- We compute the exact average number of comparisons for $n$ up to 148 – thus, going much further than *[7]*.
- We improve the bound of *[3]* to $n\log n-1.4005n+o(n)$ (Theorem 3). This partially answers a conjecture from *[11]* which asks for an in-place algorithm with $n\log n+1.4n$ comparisons on average and $n\log n-1.3n$ comparisons in the worst case. Although MergeInsertion is not in-place, the the techniques from *[3]* or *[11]* can be used to make it so.
- We evaluate a slightly different insertion order decreasing the gap between the lower bound and the average number of comparisons of MergeInsertion by roughly 30% for $n\approx 2^{k}/3$.

On the Average Case of MergeInsertion

- We compare MergeInsertion to the recent combination by Iwama and Teruyama [6] showing that, in fact, their combined algorithm is still better than the analysis and with the different insertion order can be further improved.

Most proofs as well as additional explanations and experimental results can be found in the appendix. The code used in this work and the generated data is available on [12].

# 2 Preliminaries

Throughout, we assume that the input consists of  $n$  distinct elements. The average case complexity is the mean number of comparisons over all input permutations of  $n$  elements.

Description of MergeInsertion The MergeInsertion algorithm consists of three phases: pairwise comparison, recursion, and insertion. Accompanying the explanations we give an example where  $n = 21$ . We call such a set of relations between individual elements a configuration.

1. Pairwise comparison. The elements are grouped into  $\left\lfloor \frac{n}{2} \right\rfloor$  pairs. Each pair is sorted using one comparison. After that, the elements are called  $a_1$  to  $a_{\left\lfloor \frac{n}{2} \right\rfloor}$  and  $b_1$  to  $b_{\left\lceil \frac{n}{2} \right\rceil}$  with  $a_i &gt; b_i$  for all  $1 \leq i \leq \left\lfloor \frac{n}{2} \right\rfloor$ .

![img-0.jpeg](img-0.jpeg)

2. Recursion. The  $\left\lfloor \frac{n}{2} \right\rfloor$  larger elements, i.e.,  $a_1$  to  $a_{\left\lfloor \frac{n}{2} \right\rfloor}$  are sorted recursively. Then all elements (the  $\left\lfloor \frac{n}{2} \right\rfloor$  larger ones as well as the corresponding smaller ones) are renamed accordingly such that  $a_i &lt; a_{i+1}$  and  $a_i &gt; b_i$  still holds.

![img-1.jpeg](img-1.jpeg)

3. Insertion. The  $\left\lceil \frac{n}{2} \right\rceil$  small elements, i.e., the  $b_{i}$ , are inserted into the main chain using binary insertion. The term "main chain" describes the set of elements containing  $a_{1}, \ldots, a_{t_{k}}$  as well as the  $b_{i}$  that have already been inserted.

The elements are inserted in batches starting with  $b_{3}, b_{2}$ . In the  $k$ -th batch the elements  $b_{t_k}, b_{t_{k-1}}, \ldots, b_{t_{k-1}+1}$  where  $t_k = \frac{2^{k+1} + (-1)^k}{3}$  are inserted in that order. Elements  $b_j$  where  $j &gt; \left\lceil \frac{n}{2} \right\rceil$  (which do not exist) are skipped. Note that technically  $b_1$  is the first batch; but inserting  $b_1$  does not need any comparison.

Florian Stober and Armin Weiβ

Because of the insertion order, every element $b_{i}$ which is part of the $k$-th batch is inserted into at most $2^{k}-1$ elements; thus, it can be inserted by binary insertion using at most $k$ comparisons.

![img-2.jpeg](img-2.jpeg)

Regarding the average number of comparisons $F(n)$ we make the following observations: the first step always requires $\left\lfloor \frac{n}{2} \right\rfloor$ comparisons. The recursion step does not do any comparisons by itself but depends on the other steps. The average number of comparisons $G(n)$ required in the insertion step is not obvious. It will be studied closer in following chapters. Following [7], we obtain the recurrence (which is the same as for the worst-case number of comparisons)

$$
F(n) = \left\lfloor \frac{n}{2} \right\rfloor + F \left(\left\lfloor \frac{n}{2} \right\rfloor\right) + G \left(\left\lceil \frac{n}{2} \right\rceil\right). \tag{1}
$$

# 3 Average Case Analysis of the Insertion Step

In this section we have a look at different probabilities when inserting one batch of elements, i.e., the elements $b_{t_k}$ to $b_{t_{k-1}+1}$. We assume that all elements of previous batches, i.e., $b_1$ to $b_{t_{k-1}}$, have already been inserted and together with the corresponding $a_i$ they constitute the main chain and have been renamed to $x_1$ to $x_{2t_{k-1}}$ such that $x_i &lt; x_{i+1}$. The situation is shown in Fig. 1.

We will look at the element $b_{t_k + i}$ and want to answer the following questions: what is the probability of it being inserted between $x_j$ and $x_{j+1}$? And what is the probability of it being inserted into a specific number of elements?

![img-3.jpeg](img-3.jpeg)
Fig. 1: Configuration where a single batch of elements remains to be inserted

We can ignore batches that are inserted after the batch we are looking at since those do not affect the probabilities we want to obtain.

First we define a probability space for the process of inserting one batch of elements: let $\Omega_{k}$ be the set of all possible outcomes (i.e., linear extensions) when sorting the partially ordered elements shown in Fig. 1 by inserting $b_{t_k}$ to $b_{t_{k-1}+1}$. Each $\omega \in \Omega_{k}$ can be viewed as a function that maps an element $e$ to its final position, i.e., $\omega(e) \in \{1,2,\ldots,2t_k\}$. While the algorithm mandates a specific order for inserting the elements $b_{t_{k-1}+1}$ to $b_{t_k}$ during the insertion step, using a different order does not change the outcome, i.e., the elements are still sorted correctly. For this reason we can assume a different insertion in order to simplify calculating the likelihood of relations between individual elements.

On the Average Case of MergeInsertion

Let us look at where an element will end up after it has been inserted. Not all positions are equally likely. For this purpose we define the random variable  $X_{i}$  as follows. To simplify notation we define  $x_{t_{k - 1} + j} \coloneqq a_{j}$  for  $t_{k - 1} &lt; j \leq t_{k}$  (hence, the main chain consists of  $x_{1},\ldots ,x_{2^{k}}$ ).

$$
X _ {i}: \omega \mapsto \left\{ \begin{array}{l l} 0 &amp; \text {i f} \omega (b _ {t _ {k - 1} + i}) &lt;   \omega (x _ {1}) \\ j &amp; \text {i f} \omega (x _ {j}) &lt;   \omega (b _ {t _ {k - 1} + i}) &lt;   \omega (x _ {j + 1}) \text {f o r} j \in \{1, \ldots , 2 ^ {k} - 2 \} \\ 2 ^ {k} - 1 &amp; \text {i f} \omega (x _ {2 ^ {k} - 1}) &lt;   \omega (b _ {t _ {k - 1} + i}). \end{array} \right.
$$

We are interested in the probabilities  $P(X_{i} = j)$ . These values follow a simple pattern (for  $k = 4$  these are given in Table 2 in the appendix).

Theorem 1. The probability of  $b_{t_{k-1} + i}$  being inserted between  $x_j$  and  $x_{j+1}$  is given by

$$
P (X _ {i} = j) = \left\{ \begin{array}{l l} 2 ^ {2 i - 2} \left(\frac {(t _ {k - 1} + i - 1) !}{(t _ {k - 1}) !}\right) ^ {2} \frac {(2 t _ {k - 1}) !}{(2 t _ {k - 1} + 2 i - 1) !} &amp; \text {i f} 0 \leq j \leq 2 t _ {k - 1} \\ 2 ^ {4 t _ {k - 1} - 2 j + 2 i - 2} \left(\frac {(t _ {k - 1} + i - 1) !}{(j - t _ {k - 1}) !}\right) ^ {2} \frac {(2 j - 2 t _ {k - 1}) !}{(2 t _ {k - 1} + 2 i - 1) !} &amp; \text {i f} 2 t _ {k - 1} &lt;   j &lt;   2 t _ {k - 1} + i \\ 0 &amp; \text {o t h e r w i s e} \end{array} \right.
$$

Next, our aim is to compute the probability that  $b_{i}$  is inserted into a particular number of elements. This is of particular interest because the difference between average and worst case comes from the fact that sometimes we insert into less than  $2^{k} - 1$  elements. For that purpose we define the random variable  $Y_{i}$ .

$$
Y _ {i}: \omega \mapsto \left| \left\{v \in \left\{x _ {1}, \dots , x _ {2 ^ {k}} \right\} \cup \left\{b _ {t _ {k - 1} + i + 1}, \dots , b _ {t _ {k}} \right\} \mid \omega (v) &lt;   \omega \left(a _ {t _ {k - 1} + i}\right) \right\} \right|
$$

The elements in the main chain when inserting  $b_{t_k + i}$  are  $x_1$  to  $x_{2t_{k - 1} + i - 1}$  and those elements out of  $b_{t_{k - 1} + i + 1},\ldots ,b_{t_k}$  which have been inserted before  $a_{t_{k - 1} + i}$  (which is  $x_{2t_{k - 1} + i}$ ). For computing the number of these, we introduce random variables  $\tilde{Y}_{i,q}$  counting the elements in  $\{b_{t_{k - 1} + i + 1},\dots ,b_{t_{k - 1} + i + q}\}$  that are inserted before  $a_{t_{k - 1} + i}$ :

$$
\tilde {Y} _ {i, q}: \omega \mapsto \left| \left\{v \in \left\{b _ {t _ {k - 1} + i + 1}, \dots , b _ {t _ {k - 1} + i + q} \right\} \mid \omega (v) &lt;   \omega \left(a _ {t _ {k - 1} + i}\right) \right\} \right|.
$$

By setting  $q = t_k - t_{k-1} - i$ , we obtain  $Y_i = \tilde{Y}_{i,t_k - t_{k-1} - i} + 2t_{k-1} + i - 1$ . For an illustration see Figure 16 in the appendix. Clearly we have  $P\big(\tilde{Y}_{i,0} = j\big) = 1$  if  $j = 0$  and  $P\big(\tilde{Y}_{i,0} = j\big) = 0$  otherwise. For  $q &gt; 0$  there are two possibilities:

1.  $\tilde{Y}_{i,q - 1} = j - 1$  and  $X_{i + q} &lt; 2t_{k - 1} + i$ : out of  $\{b_{t_{k - 1} + i + 1},\ldots ,b_{t_{k - 1} + i + q - 1}\}$  there have been  $j - 1$  elements inserted before  $a_{t_{k - 1} + i}$  and  $b_{t_{k - 1} + i + q}$  is inserted before  $a_{t_{k - 1} + i}$ .
2.  $\tilde{Y}_{i,q - 1} = j$  and  $X_{i + q}\geq 2t_{k - 1} + i$ : out of  $\{b_{t_{k - 1} + i + 1},\ldots ,b_{t_{k - 1} + i + q - 1}\}$  there have been  $j$  elements inserted before  $a_{t_{k - 1} + i}$  and  $b_{t_{k - 1} + i + q}$  is inserted after  $a_{t_{k - 1} + i}$ .

From these we obtain the following recurrence:

$$
P (\tilde {Y} _ {i, q} = j) = P (X _ {i + q} &lt;   2 t _ {k - 1} + i \mid \tilde {Y} _ {i, q - 1} = j - 1) \cdot P (\tilde {Y} _ {i, q - 1} = j - 1)
$$

Florian Stober and Armin Weiβ

![img-4.jpeg](img-4.jpeg)
Fig. 2: Probability distribution of  $Y_{i}$ . Fig. 3: Mean of  $Y_{i}$  for different  $i$ .  $k = 7$ .

![img-5.jpeg](img-5.jpeg)

$$
+ P \left(X _ {i + q} \geq 2 t _ {k - 1} + i \mid \tilde {Y} _ {i, q - 1} = j\right) \cdot P \left(\tilde {Y} _ {i, q - 1} = j\right)
$$

The probability  $P(X_{i + q} &lt; 2t_{k - 1} + i \mid \tilde{Y}_{i,q - 1} = j - 1)$  can be obtained by looking at Fig. 1 and counting elements. When  $b_{t_{k - 1} + i + q}$  is inserted, the elements on the main chain which are smaller than  $a_{t_{k - 1} + i}$  are  $x_{1}$  to  $x_{2t_{k - 1}}$ ,  $a_{t_{k - 1} + 1}$  to  $a_{t_{k - 1} + i - 1}$  and  $j - 1$  elements out of  $\{b_{t_{k - 1} + i + 1},\ldots ,b_{t_{k - 1} + i + q - 1}\}$  which is a total of  $2t_{k - 1} + 2i + j - 2$  elements. Combined with the fact that the main chain consists of  $2t_{k - 1} + 2i + 2q - 2$  elements smaller than  $a_{t_{k - 1} + i + q}$  we obtain the probability  $\frac{2t_{k - 1} + 2i + j - 1}{2t_{k - 1} + 2i + 2q - 1}$ . We can calculate  $P(X_{i + q} \geq 2t_{k - 1} + i \mid \tilde{Y}_{i,q - 1} = j)$  similarly leading to

$$
P (\tilde {Y} _ {i, q} = j) = \frac {2 t _ {k - 1} + 2 i + j - 1}{2 t _ {k - 1} + 2 i + 2 q - 1} \cdot P (\tilde {Y} _ {i, q - 1} = j - 1) + \frac {2 q - j - 1}{2 t _ {k - 1} + 2 i + 2 q - 1} \cdot P (\tilde {Y} _ {i, q - 1} = j).
$$

By solving the recurrence, we obtain a closed form for  $P(\tilde{Y}_{i,q} = j)$  and, thus, for  $P(Y_{i} = j)$ . The complete proof is given in Appendix B.2.

Theorem 2. For  $1 \leq i \leq t_k - t_{k-1}$  and  $2t_{k-1} + i - 1 \leq j \leq 2^k - 1$  the probability  $P(Y_i = j)$ , that  $b_{t_{k-1} + i}$  is inserted into  $j$  elements is given by

$$
P (Y _ {i} = j) = 2 ^ {j - 2 t _ {k - 1} - i + 1} \frac {(2 t _ {k} - i - j - 1) !}{(j - 2 t _ {k - 1} - i + 1) ! (2 ^ {k} - j - 1) !} \frac {(i + j) !}{(2 t _ {k} - 1) !} \frac {(t _ {k} - 1) !}{(t _ {k - 1} + i - 1)}.
$$

Figure 2 shows the probability distribution for  $Y_{1}$ ,  $Y_{21}$  and  $Y_{42}$  where  $k = 7$ .  $Y_{42}$  corresponds to the insertion of  $b_{t_k}$  (the first element of the batch).  $Y_{1}$  corresponds to the insertion of  $b_{t_{k-1}+1}$  (the last element of the batch). In addition to those three probability distributions Fig. 3 shows the mean of all  $Y_{i}$  for  $k = 7$ .

Binary Insertion and different decision trees The Binary Insertion step is an important part of MergeInsertion. In the average case many elements are inserted in less than  $2^{k} - 1$  (which is the worst case). This leads to ambiguous decision trees where at some positions inserting an element requires only  $k - 1$  instead of  $k$  comparisons. Since not all positions are equally likely (positions on the left have a slightly higher probability), this results in different average

On the Average Case of MergeInsertion

![img-6.jpeg](img-6.jpeg)
(a) center-left

![img-7.jpeg](img-7.jpeg)
(b) center-right

![img-8.jpeg](img-8.jpeg)
(c) left
Fig. 4: Different strategies for binary insertion.

![img-9.jpeg](img-9.jpeg)
(d) right

insertion costs. We compare four different strategies all satisfying that the corresponding decision trees have their leaves distributed across at most two layers. For an example with five elements see Figure 4.

First there are the center-left and center-right strategies (the standard options for binary insertion): they compare the element to be inserted with the middle element, rounding down(up) in case of an odd number. The left strategy chooses the element to compare with in a way such that the positions where only  $k - 1$  comparisons are required are at the very left. The right strategy is similar, here the positions where one can insert with just  $k - 1$  comparisons are at the right. To summarize, the element to compare with is

|  |n+1/2 | strategy center-left  |
| --- | --- | --- |
|  |n+1/2 | strategy center-right  |
|  max{n-2k+1,2k-1} | strategy left  |
|  min{2k,n-2k-1+1} | strategy right  |

where  $k = \lfloor \log n \rfloor$ . Notice that the left strategy is also used in [6], where it is called right-hand-binary-search. Figure 5 shows experimental results comparing the different strategies for binary insertion regarding their effect on the average-case of MergeInsertion. As we can see the left strategy performs the best, closely followed by center-left and center-right. right performs the worst. The left strategy performing best is no surprise since the probability that an element is inserted into one of the left positions is higher than it being inserted to the right. Therefore, in all further experiments we use the left strategy.

# 4 Improved Upper Bounds for MergeInsertion

Numeric upper bound The goal of this section is to combine the probability given by Theorem 2 that an element  $b_{t_{k-1}+i}$  is inserted into  $j$  elements with an upper bound for the number of comparisons required for binary insertion.

By [4], the number of comparisons required for binary insertion when inserting into  $m - 1$  elements is  $T_{\mathrm{InsAvg}}(m) = \lceil \log m \rceil + 1 - \frac{2^{\lceil \log m \rceil}}{m}$ . While only being exact in case of a uniform distribution, this formula acts as an upper bound in our case, where the probability is monotonically decreasing with the index.

This leads to an upper bound for the cost of inserting  $b_{t_{k-1}+i}$  of  $T_{\mathrm{Ins}}(i,k) = \sum_j P(Y_i = j) \cdot T_{\mathrm{InsAvg}}(j+1)$ . From there we calculated an upper bound for MergeInsertion. Figure 6 compares those results with experimental data on the number of comparisons required by MergeInsertion. We observe that the difference is rather small.

Florian Stober and Armin Wei

![img-10.jpeg](img-10.jpeg)
Fig. 5: Experimental results on the effect of different strategies for binary insertion on the number of comparisons.

![img-11.jpeg](img-11.jpeg)
Fig. 6: Comparing our upper bound with experimental data on the number of comparisons required by MergeInsertion.

Computing the Exact Number of Comparisons In this section we explore how to numerically calculate the exact number of comparisons required in the average case. The most straightforward way of doing this is to compute the external path length of the decision tree (sum of lengths of all paths from the root to leaves) and dividing by the number of leaves ( $n!$  when sorting  $n$  elements), which unfortunately is only feasible for very small  $n$ . Instead we use Equation (1), which describes the number of comparisons. The only unknown in that formula is  $G(n)$  the number of comparisons required in the insertion step of the algorithm. Since the insertion step of MergeInsertion works by inserting elements in batches, we write  $G(n) = \left(\sum_{1 &lt; k \leq k_n} \text{Cost}(t_{k-1}, t_k)\right) + \text{Cost}(t_{k_n}, n)$  for  $t_{k_n} \leq n &lt; t_{k_n+1}$ . Here  $\text{Cost}(s, e)$  is the cost of inserting one batch of elements starting from  $b_{s+1}$  up to  $b_e$ . The idea for computing  $\text{Cost}(s, e)$  is to calculate the external path length of the decision tree corresponding to the insertion of that batch of elements and then dividing by the number of leaves. As this is still not feasible, we apply some optimizations which we describe in detail in Appendix C.

On the Average Case of MergeInsertion

For  $n \in \{1, \ldots, 15\}$  the computed values are shown in Table 1, for larger  $n$ . Fig. 7 shows the values we computed. The complete data set is provided in the file exact.csv in [12]. Our results match up with the values for  $n \in \{1, \ldots, 8\}$  calculated in [7]. Note that for these values the chosen insertion strategy does not affect the average case (we use the left strategy).

![img-12.jpeg](img-12.jpeg)
Fig. 7: Computed values of  $F(n)$ .

![img-13.jpeg](img-13.jpeg)
Table 1: Computed values of  $F\left( n\right)  \cdot  n$  !.

Improved theoretical upper bounds In this section we improve upon the upper bound from [3] leading to the following result:

Theorem 3. The number of comparisons required in the average case of Merge-Insertion is at most  $n \log n - c(x_n) \cdot n \pm \mathcal{O}(\log^2 n)$  where  $x_n$  is the fractional part of  $\log(3n)$ , i.e., the unique value in  $[0,1)$  such that  $n = 2^{k - \log 3 + x_n}$  for some  $k \in \mathbb{Z}$  and  $c: [0,1) \to \mathbb{R}$  is given by the following formula:

$$
c (x) = (3 - \log 3) - (2 - x - 2 ^ {1 - x}) + (1 - 2 ^ {- x}) \left(\frac {3}{2 ^ {x} + 1} - 1\right) + \frac {2 ^ {\log 3 - x}}{2 2 9 2} \geq 1. 4 0 0 5
$$

Hence we have obtained a new upper bound for the average case of MergeInsertion which is  $n \log n - 1.4005n + \mathcal{O}(\log^2 n)$ . A visual representation of  $c(x)$  is provided in Fig. 8. The worst case is near  $x = 0.6$  (i.e.,  $n$  roughly a power of two) where  $c(x)$  is just slightly larger than 1.4005.

The proof of Theorem 3 analyzes the insertion of one batch of elements more carefully than in [4]. The exact probability that  $b_{t_{k-1}+i}$  is inserted into  $j$  elements is given by Theorem 2. We are especially interested in the case of  $b_{t_{k-1}+u}$  where  $u = \left\lfloor \frac{t_k - t_{k-1}}{2} \right\rfloor$ , because, if we know  $P(Y_u &lt; m)$ , then we can use that for all  $q &lt; u$  we have  $P(Y_q &lt; m) \geq P(Y_u &lt; m)$ .

However, the equation from Theorem 2 is hard to work with, so we approximate it with the binomial distribution  $p(j) = \left(\left\lceil \frac{q}{q} \right\rceil\right)\left(\frac{\lfloor \frac{q}{2} \rfloor}{2t_k - 1}\right)^q\left(\frac{2t_k - 1 - \lfloor \frac{q}{2} \rfloor}{2t_k - 1}\right)\left\lceil \frac{q}{2} \right\rceil - q$  with  $q = 2^k - 1 - j$ , that by construction fulfills  $\sum_{j=0}^{j_0} p(j) \leq \sum_{j=0}^{j_0} P(Y_u = j) = P(Y_u \leq j_0)$  for all  $j_0$ . By using the approximation  $P(Y_u = j) \approx p(j)$  we can calculate a lower bound for the median of  $Y_{\frac{t_k - t_{k-1}}{2}}$  which is  $2^k - 1 - \lfloor n_B \cdot p_B \rfloor \in 2^k - 1 - \frac{2^{k-6}}{3} + \mathcal{O}(1)$ . Thus, with a probability of one half the elements  $b_{t_{k-1}+i}$

Florian Stober and Armin Weiß

![img-14.jpeg](img-14.jpeg)
Fig. 8: Plot of  $c(x)$ .

![img-15.jpeg](img-15.jpeg)
Fig. 9:  $n$  used in Fig. 10.

![img-16.jpeg](img-16.jpeg)
Fig. 10: Effects of replacing  $t_k$  with  $\hat{t}_k$ .

for  $1 \leq i \leq u$  are inserted in  $\frac{2^{k-6}}{3}$  elements less compared to the worst case. Combining that with the bounds from [4] we obtain Theorem 3. The complete proof is given in Appendix B.3.

# 5 Experiments

In this section we discuss our experiment, which consist of two parts: first, we evaluate how increasing  $t_k$  by some constant factor can reduce the number of comparisons, then we examine how the combination with the (1,2)-Insertion algorithm as proposed in [6] improves MergeInsertion.

We implemented MergeInsertion using a tree based data structure, similar to the Rope data structure[1] used in text processing, resulting in a comparably "fast" implementation. Implementation details can be found in Appendix D. All experiments use the left strategy for binary insertion (see Section 3). The number of comparisons has been averaged over 10 to 10000 runs, depending on the size of the input.

Increasing  $t_k$  by a Constant Factor In this section we modify MergeInsertion by replacing  $t_k$  with  $\hat{t}_k = \lfloor f \cdot t_k \rfloor$  - otherwise the algorithm is the same. Originally the numbers  $t_k$  have been chosen, such that each element  $b_i$  with  $t_{k-1} &lt; i \leq t_k$  is inserted into at most  $2^k - 1$  elements (which is optimal for the

On the Average Case of MergeInsertion

![img-17.jpeg](img-17.jpeg)
Fig. 11: Comparison of different factors  $f$  for  $\hat{t}_k$ .

worst case). As we have seen in previous sections many elements are inserted into slightly less than  $2^k - 1$  elements. The idea behind increasing  $t_k$  by a constant factor  $f$  is to allow more elements to be inserted into close to  $2^k - 1$  elements.

Figure 10 shows how different factors  $f$  affect the number of comparisons required by MergeInsertion. The different lines represent different input lengths. For instance,  $n = 21845$  is an input size for which MergeInsertion works best. An overview of the different input lengths and how original MergeInsertion performs for these can be seen in Figure 9. The chosen values are assumed to be representative for the entire algorithm. We observe that for all shown input lengths, multiplying  $t_k$  by a factor  $f$  between 1.02 and 1.05, leads to an improvement.

Figure 11 compares different factors from 1.02 to 1.05. The factor 1.0 (i.e., the original algorithm) is included as a reference. We observe that all the other factors lead to a considerable improvement compared to 1.0. The difference between the factors in the chosen range is rather small. However, 1.03 appears to be best out of the tested values. At  $n \approx 2^k / 3$  the difference to the information-theoretic lower bound is reduced to  $0.007n$ , improving upon the original algorithm, which has a difference of  $0.01n$  to the optimum.

Another observation we make from Figure 11 is that the plot periodically repeats itself with each power of two. Thus, we conclude that replacing  $t_k$  with  $\hat{t}_k = \lfloor f \cdot t_k \rfloor$  with  $f \in [1.02, 1.05]$  reduces the number of comparisons required per element by some constant.

Combination with (1,2)-Insertion (1,2)-Insertion is a sorting algorithm presented in [6]. It works by inserting either a single element or two elements at once into an already sorted list. On its own (1,2)-Insertion is worse than MergeInsertion; however, it can be combined with MergeInsertion. The combined algorithm works by sorting  $m = \max \{u_k \mid u_k \leq n\}$  elements with MergeInsertion. Then the remaining elements are inserted using (1,2)-Insertion. Let  $u_k = \left\lfloor \left(\frac{4}{3}\right) 2^k \right\rfloor$  denote a point where MergeInsertion is optimal.

In Fig. 12 we can see that at the point  $u_{k}$  MergeInsertion and the combined algorithm perform the same. However, in the values following  $u_{k}$  the combined algorithm surpasses MergeInsertion until at one point close to the next optimum

Florian Stober and Armin Weiβ

![img-18.jpeg](img-18.jpeg)
Fig. 12: Experimental results comparing MergeInsertion, (1,2)-Insertion and the combined algorithm.

MergeInsertion is better once again. In their paper Iwama and Teruyama calculated that for  $0.638 \leq \frac{n}{2^{\lceil \log n \rceil}} \leq \frac{2}{3}$  MergeInsertion is better than the combined algorithm. The fraction  $\frac{2}{3}$  corresponds to the point where MergeInsertion is optimal. They derived the constant 0.638 from their theoretical analysis using the upper bound for MergeInsertion from [3]. Comparing this to our experimental results we observe that the range where MergeInsertion is better than the combined algorithm starts at  $n \approx 2^{17.242}$ . This yields  $\frac{2^{17.242}}{2^{18}} = 2^{17.242 - 18} = 2^{-0.758} \approx 0.591$ . Hence the range where MergeInsertion is better than the combined algorithm is  $0.591 \leq \frac{n}{2^{\lceil \log n \rceil}} \leq \frac{2}{3}$ , which is slightly larger than the theoretical analysis suggested. Also shown in Fig. 12 is the combined algorithm where we additionally apply our suggestion of replacing  $t_k$  by  $\hat{t}_k = \lfloor f \cdot t_k \rfloor$  with  $f = 1.03$ . This leads to an additional improvement and comes even closer to the lower bound of  $\log(n!)$ .

Conclusion and Outlook We improved the previous upper bound of  $n \log n - 1.3999n + o(n)$  to  $n \log n - 1.4005n + o(n)$  for the average number of comparisons of MergeInsertion. However, there still is a gap between the number of comparisons required by MergeInsertion and this upper bound.

In Section 4 we used a binomial distribution to approximate the probability of an element being inserted into a specific number of elements during the insertion step. However, the difference between our approximation and the actual probability distribution is rather large. Finding an approximation which reduces that gap while still being simple to analyze with respect to its mean would facilitate further improvements to the upper bound.

Our suggestion of increasing  $t_k$  by a constant factor  $f$  reduced the number of comparisons required per element by some constant. However, we do not have a proof for this. Thus, future research could try to determine the optimal value for the factor  $f$  as well as to study how this suggestion affects the worst-case.

On the Average Case of MergeInsertion

# References

- [1] Boehm, H.J., Atkinson, R., Plass, M.: Ropes: An alternative to strings. Softw. Pract. Exper. 25(12), 1315–1330 (Dec 1995)
- [2] Bui, T., Thanh, M.: Significant improvements to the Ford-Johnson algorithm for sorting. BIT Numerical Mathematics 25(1), 70–75 (1985)
- [3] Edelkamp, S., Weiß, A.: Quickxsort: Efficient Sorting with $n\log n-1.399n+o(n)$ Comparisons on Average. In: CSR 2014 Proc. pp. 139–152 (2014)
- [4] Edelkamp, S., Weiß, A., Wild, S.: Quickxsort - A fast sorting scheme in theory and practice. CoRR abs/1811.01259 (2018)
- [5] Ford, L.R., Johnson, S.M.: A tournament problem. The American Mathematical Monthly 66(5), 387–389 (1959)
- [6] Iwama, K., Teruyama, J.: Improved average complexity for comparison-based sorting. In: Workshop on Algorithms and Data Structures. pp. 485–496. Springer (2017)
- [7] Knuth, D.E.: The Art of Computer Programming, Volume 3: (2Nd Ed.) Sorting and Searching. Addison Wesley Longman, Redwood City, CA, USA (1998)
- [8] Manacher, G.K.: The Ford-Johnson sorting algorithm is not optimal. J. ACM 26(3), 441–456 (Jul 1979)
- [9] Peczarski, M.: New results in minimum-comparison sorting. Algorithmica 40(2), 133–145 (2004)
- [10] Peczarski, M.: The Ford-Johnson algorithm still unbeaten for less than 47 elements. Inf. Process. Lett. 101(3), 126–128 (2007)
- [11] Reinhardt, K.: Sorting *In-Place* with a *Worst Case* complexity of $n$ log $n$-1.3$n+O$(log$n$) comparisons and epsilon $n$ log $n+O$(1) transports. In: Algorithms and Computation, ISAAC ’92, Proc. pp. 489–498 (1992)
- [12] Stober, F.: Source code and generated data (2018), https://github.com/CodeCrafter47/merge-insertion

Florian Stober and Armin Weiß

# A Tables and Figures

![img-19.jpeg](img-19.jpeg)

![img-20.jpeg](img-20.jpeg)

![img-21.jpeg](img-21.jpeg)
(a) Batch  $k = 2$
(b) Batch  $k = 3$
(c) Batch  $k = 4$

![img-22.jpeg](img-22.jpeg)
Fig. 13: Batches of the elements  $b_{t_k}$  to  $b_{t_{k-1}+1}$  for  $k \in \{2,3,4\}$
Fig. 14: Probabilities of different positions when inserting  $b_{t_k}$  where  $k = 6$ .

On the Average Case of MergeInsertion

|  i | 1 | 2 | 3 | 4 | 5 | 6  |
| --- | --- | --- | --- | --- | --- | --- |
|  P(Xi=0) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=1) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=2) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=3) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=4) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=5) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=6) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=7) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=8) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=9) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=10) | 1/11 | 1/11 | 12/13 | 1/11 | 12/13 | 14/15  |
|  P(Xi=11) | 0 | 1/15 | 1/13 | 1/13 | 1/13 | 1/13  |
|  P(Xi=12) | 0 | 0 | 1/15 | 1/15 | 1/15 | 1/15  |
|  P(Xi=13) | 0 | 0 | 0 | 1/17 | 1/17 | 1/17  |
|  P(Xi=14) | 0 | 0 | 0 | 0 | 1/15 | 1/15  |
|  P(Xi=15) | 0 | 0 | 0 | 0 | 0 | 1/21  |

Table 2: Values of  $P\left( {{X}_{i} = j}\right)$  for  $k = 4$  .

Algorithm 1 Binary Insertion
1: procedure INSERT(a,x1,...,xn)
2: if n = 0 then
3: return a
4: end if
5: k ← [log n]
6: c ← { [n+1/2] strategy center-left
[ n+1/2] strategy center-right
max{n-2^k+1,2^{k-1}} strategy left
min{2^k,n-2^{k-1}+1} strategy right
7: if a &lt; x_c then
8: y1,...,yc ← INSERT(a,x1,...,xc-1)
9: return y1,...,yc,xc,...,xn
10: else
11: yc,...,yn ← INSERT(a,xc+1,...,xn)
12: return x1,...,xc,yc,...,yn
13: end if
14: end procedure

Florian Stober and Armin Weiß

![img-23.jpeg](img-23.jpeg)
Fig. 15: Comparing experimental results with the upper bound from Theorem 3.

On the Average Case of MergeInsertion

# B Missing Proofs

# B.1 Proof of Theorem 1

For an arbitrary  $k$  we can calculate the probabilities  $P(X_{i} = j)$  with the following recursive scheme. We start with  $P(X_{1} = j)$ . This corresponds to the insertion of  $b_{t_{k - 1} + 1}$  into  $x_{1},\ldots ,x_{2t_{k - 1}}$ . The probability of all those is uniformly distributed, so  $P(X_{1} = j) = \frac{1}{2t_{k - 1} + 1}$  for  $0\leq j\leq 2t_{k - 1}$ .

For  $i &gt; 1$  we can express  $P(X_{i} = j)$  in terms of  $P(X_{i - 1} = j)$ . Observe that when inserting  $b_{t_{k - 1} + i}$  there are  $2t_{k - 1} + 2i - 2$  elements known to be smaller than  $a_{t_{k - 1} + i}$ . These are  $x_{1},\ldots ,x_{2t_{k - 1}}$  and  $a_{t_{k - 1} + 1},\ldots ,a_{t_{k - 1} + i - 1}$  as well as the corresponding  $b$ 's. The number of elements known to be smaller than  $a_{t_{k - 1} + i - 1}$  is one less: just  $2t_{k - 1} + 2i - 3$ . As a result the probability that  $b_{t_{k - 1} + i}$  is inserted between  $a_{t_{k - 1} + i - 1}$  and  $a_{t_{k - 1} + i}$  is  $P(X_{i} = 2t_{k - 1} + i - 1) = \frac{1}{2t_{k - 1} + 2i - 1}$ . The probability that is ends up in one of the other positions consequently is  $P(0\leq X_i &lt; 2t_{k - 1} + i - 1) = \frac{2t_{k - 1} + 2i - 2}{2t_{k - 1} + 2i - 1}$ . If we know that  $b_{t_{k - 1} + i}$  is inserted into one of those other positions, then it is inserted into exactly the same elements as  $b_{t_{k - 1} + i - 1}$ , thus we can write  $P(X_{i} = j) = \frac{2t_{k - 1} + 2i - 2}{2t_{k - 1} + 2i - 1} P(X_{i - 1} = j)$ . This leads to Eq. (2).

$$
P \left(X _ {i} = j\right) = \left\{ \begin{array}{l l} \left(\prod_ {l = 1} ^ {i - 1} 2 t _ {k - 1} + 2 l\right) \cdot \left(\prod_ {l = 1} ^ {i} 2 t _ {k - 1} + 2 l - 1\right) ^ {- 1} &amp; \text {i f} 0 \leq j \leq 2 t _ {k - 1} \\ \left(\prod_ {l = j - 2 t _ {k - 1} + 1} ^ {i - 1} 2 t _ {k - 1} + 2 l\right) \cdot \left(\prod_ {l = j - 2 t _ {k - 1} + 1} ^ {i} 2 t _ {k - 1} + 2 l - 1\right) ^ {- 1} &amp; \text {i f} 2 t _ {k - 1} &lt;   j &lt;   2 t _ {k - 1} + i \\ 0 &amp; \text {o t h e r w i s e .} \end{array} \right. \tag {2}
$$

It remains to simplify Eq. (2). We begin with the first case:

$$
\begin{array}{l} \left(\prod_ {l = 1} ^ {i - 1} 2 t _ {k - 1} + 2 l\right) \cdot \left(\prod_ {l = 1} ^ {i} 2 t _ {k - 1} + 2 l - 1\right) ^ {- 1} \\ = \left(\prod_ {l = t _ {k - 1} + 1} ^ {t _ {k - 1} + i - 1} 2 l\right) \cdot \left(\prod_ {l = 2 t _ {k - 1} + 1} ^ {2 t _ {k - 1} + 2 i - 1} l\right) ^ {- 1} \cdot \left(\prod_ {l = t _ {k - 1} + 1} ^ {t _ {k - 1} + i - 1} 2 l\right) \\ = \left(\prod_ {l = 1} ^ {t _ {k - 1} + i - 1} 2 l\right) \cdot \left(\prod_ {l = 1} ^ {t _ {k - 1}} 2 l\right) ^ {- 1} \cdot \left(\prod_ {l = 1} ^ {2 t _ {k - 1} + 2 i - 1} l\right) ^ {- 1} \tag {3} \\ \cdot \left(\prod_ {l = 1} ^ {2 t _ {k - 1}} l\right) \cdot \left(\prod_ {l = 1} ^ {t _ {k - 1} + i - 1} 2 l\right) \cdot \left(\prod_ {l = 1} ^ {t _ {k - 1}} 2 l\right) ^ {- 1} \\ = 2 ^ {2 i - 2} \left(\frac {(t _ {k - 1} + i - 1) !}{(t _ {k - 1}) !}\right) ^ {2} \frac {(2 t _ {k - 1}) !}{(2 t _ {k - 1} + 2 i - 1) !} \\ \end{array}
$$

Florian Stober and Armin Weiß

For the second case we have

$$
\begin{aligned}
&amp; \left(\prod_{l=j-2t_{k-1}+1}^{i-1} 2t_{k-1} + 2l\right) \cdot \left(\prod_{l=j-2t_{k-1}+1}^{i} (2t_{k-1} + 2l - 1)\right)^{-1} \\
&amp; = \left(\prod_{l=j-t_{k-1}+1}^{t_{k-1}+i-1} 2l\right) \cdot \left(\prod_{l=2j-2t_{k-1}+1}^{2t_{k-1}+2i-1} l\right)^{-1} \cdot \left(\prod_{l=j-t_{k-1}+1}^{t_{k-1}+i-1} 2l\right) \\
&amp; = \left(\prod_{l=1}^{t_{k-1}+i-1} 2l\right) \cdot \left(\prod_{l=1}^{j-t_{k-1}} 2l\right)^{-1} \cdot \left(\prod_{l=1}^{2t_{k-1}+2i-1} l\right)^{-1} \tag{4} \\
&amp; \quad \cdot \left(\prod_{l=1}^{2j-2t_{k-1}} l\right) \cdot \left(\prod_{l=1}^{t_{k-1}+i-1} 2l\right) \cdot \left(\prod_{l=1}^{j-t_{k-1}} 2l\right)^{-1} \\
&amp; = 2^{4t_{k-1}-2j+2i-2} \left(\frac{(t_{k-1}+i-1)!}{(j-t_{k-1})!}\right)^2 \frac{(2j-2t_{k-1})!}{(2t_{k-1}+2i-1)!}
\end{aligned}
$$

By substitution of (3) and (4) in (2) we obtain Theorem 1.

## B.2 Proof of Theorem 2

![img-24.jpeg](img-24.jpeg)
Fig. 16: Configuration where one batch of $t_k - t_{k-1}$ elements remains to be inserted. The elements $b_{t_{k-1}+i}$ and $b_{t_{k-1}+i+q}$ are drawn.

Recall the definitions of $Y_{i}$, $\tilde{Y}_{i,q}$ and their relation:

$$
Y_{i}: \omega \mapsto \left| \left\{v \in \left\{x_{1}, \dots, x_{2^{k}} \right\} \cup \left\{b_{t_{k-1}+i+1}, \dots, b_{t_{k}} \right\} \mid \omega(v) &lt; \omega(a_{t_{k-1}+i}) \right\} \right| \tag{5}
$$

$$
\tilde{Y}_{i,q}: \omega \mapsto \left| \left\{v \in \left\{b_{t_{k-1}+i+1}, \dots, b_{t_{k-1}+i+q} \right\} \mid \omega(v) &lt; \omega(a_{t_{k-1}+i}) \right\} \right| \tag{6}
$$

$$
Y_{i} = \tilde{Y}_{i,t_{k}-t_{k-1}-i} + 2t_{k-1} + i - 1 \tag{7}
$$

On the Average Case of MergeInsertion

To proof Theorem 2 we start with the following closed form for the probability $P(\tilde{Y}_{i,q} = j)$.

$$
P \left(\tilde {Y} _ {i, q} = j\right) = \frac {(2 q - j) !}{2 ^ {q - j} j ! (q - j) !} 2 ^ {q} \frac {\left(2 t _ {k - 1} + 2 i + j - 1\right) !}{\left(2 t _ {k - 1} + 2 i + 2 q - 1\right) !} \frac {\left(t _ {k - 1} + i + q - 1\right) !}{\left(t _ {k - 1} + i - 1\right) !} \tag {8}
$$

From the definition of $\tilde{Y}_{i,q}$ we can see that $0\leq \tilde{Y}_{i,q}\leq q$ thus $P(\tilde{Y}_{i,0} = 0) = 1$. This also holds for Eq. (8).

$$
P \left(\tilde {Y} _ {i, 0} = 0\right) = \frac {0 !}{2 ^ {0} \cdot 0 ! \cdot 0 !} 2 ^ {0} \frac {\left(2 t _ {k - 1} + 2 i - 1\right) !}{\left(2 t _ {k - 1} + 2 i - 1\right) !} \frac {\left(t _ {k - 1} + i - 1\right) !}{\left(t _ {k - 1} + i - 1\right) !} = 1 \tag {9}
$$

Recall that for $q &gt; 0$ there are two possibilities:

1. $\tilde{Y}_{i,q-1} = j - 1$ and $X_{i+q} &lt; 2t_{k-1} + i$. Informally speaking that means out of $\{b_{t_{k-1} + i+1}, \ldots, b_{t_{k-1} + i+q-1}\}$ there have been $j - 1$ elements inserted before $a_{t_{k-1} + i}$ and $b_{t_{k-1} + i+q}$ is inserted before $a_{t_{k-1} + i}$.
2. $\tilde{Y}_{i,q-1} = j$ and $X_{i+q} \geq 2t_{k-1} + i$. Informally speaking that means out of $\{b_{t_{k-1} + i+1}, \ldots, b_{t_{k-1} + i+q-1}\}$ there have been $j$ elements inserted before $a_{t_{k-1} + i}$ and $b_{t_{k-1} + i+q}$ is inserted after $a_{t_{k-1} + i}$.

Note that the first case requires $j &gt; 0$ and the second case requires $j &lt; q$ so we look at $j = 0$ and $j = q$ separately.

Using Bayes' theorem we obtain the following identities:

$$
\begin{array}{l}
P \left(X _ {i + q} \geq 2 t _ {k - 1} + i \wedge \tilde {Y} _ {i, q - 1} = 0\right) = P \left(X _ {i + q} \geq 2 t _ {k - 1} + i \mid \tilde {Y} _ {i, q - 1} = 0\right) \cdot P \left(\tilde {Y} _ {i, q - 1} = 0\right) \\
P \left(X _ {i + q} &lt; 2 t _ {k - 1} + i \wedge \tilde {Y} _ {i, q - 1} = q - 1\right) = P \left(X _ {i + q} &lt; 2 t _ {k - 1} + i \mid \tilde {Y} _ {i, q - 1} = q - 1\right) \cdot P \left(\tilde {Y} _ {i, q - 1} = q - 1\right) \tag {10}
\end{array}
$$

The probability $P(X_{i + q} &lt; 2t_{k - 1} + i \mid Y_{i,q - 1} = d)$ can be obtained by looking at Fig. 16 and counting elements. When $b_{t_{k - 1} + i + q}$ is inserted, the elements on the main chain which are smaller than $a_{t_{k - 1} + i}$ are $x_{1}$ to $x_{2t_{k - 1}}$, $a_{t_{k - 1} + 1}$ to $a_{t_{k - 1} + i - 1}$ and $d$ elements out of $\{b_{t_{k - 1} + i + 1}, \ldots, b_{t_{k - 1} + i + q - 1}\}$ which is a total of $2t_{k - 1} + 2i - 1 + d$ elements. Combined with the fact that the main chain consists of $2t_{k - 1} + 2i + 2q - 2$ elements smaller than $a_{t_{k - 1} + i + q}$ we obtain the following formula

$$
P \left(X _ {i + q} &lt; 2 t _ {k - 1} + i \mid Y _ {i, q - 1} = d\right) = \frac {2 t _ {k - 1} + 2 i + d}{2 t _ {k - 1} + 2 i + 2 q - 1} \tag {11}
$$

1 The first part of Eq. (8): $\frac{(2q-j)!}{2^{q-j}j!(q-j)!}$, when substituting $q = n$ and $j = n-k$ yields $a(n,k) = \frac{(n+k)!}{2^k(n-k)!k!}$ which is the number sequence A001498 from The On-Line Encyclopedia of Integer Sequences https://oeis.org/A001498.

Florian Stober and Armin Weiß

From that we can calculate

$$
\begin{array}{l}
P \left(X _ {i + q} \geq 2 t _ {k - 1} + i \mid Y _ {i, q - 1} = d\right) \\
= 1 - P \left(X _ {i + q} &lt; 2 t _ {k - 1} + i \mid Y _ {i, q - 1} = d\right) \\
= 1 - \frac {2 t _ {k - 1} + 2 i + d}{2 t _ {k - 1} + 2 i + 2 q - 1} \tag {12} \\
= \frac {2 t _ {k - 1} + 2 i + 2 q - 1 - 2 t _ {k - 1} - 2 i - d}{2 t _ {k - 1} + 2 i + 2 q - 1} \\
= \frac {2 q - d - 1}{2 t _ {k - 1} + 2 i + 2 q - 1}
\end{array}
$$

Now we have all the necessary ingredients to proof Eq. (8) using induction.

1. Proof of Eq. (8) where $j = 0$ using $\tilde{Y}_{i,q} = 0 \Leftrightarrow X_{i + q} \geq 2t_{k - 1} + i \wedge \tilde{Y}_{i,q - 1} = 0$

$$
\begin{array}{l}
P \left(X _ {i + q} \geq 2 t _ {k - 1} + i \wedge \tilde {Y} _ {i, q - 1} = 0\right) \\
= P \left(X _ {i + q} \geq 2 t _ {k - 1} + i \mid \tilde {Y} _ {i, q - 1} = 0\right) \cdot P \left(\tilde {Y} _ {i, q - 1} = 0\right)
\end{array}
$$

$$
\begin{array}{l}
\stackrel {2. (1 2)} {=} \frac {2 q - 1}{2 t _ {k - 1} + 2 i + 2 q - 1} \cdot \frac {(2 q - 2) !}{2 ^ {q - 1} 0 ! (q - 1) !} 2 ^ {q - 1} \frac {(2 t _ {k - 1} + 2 i - 1) !}{(2 t _ {k - 1} + 2 i + 2 q - 3) !} \frac {(t _ {k - 1} + i + q - 2) !}{(t _ {k - 1} + i - 1) !} \\
= (2 q - 1) \left(2 t _ {k - 1} + 2 i + 2 q - 2\right) \cdot \frac {(2 q - 2) !}{2 ^ {q - 1} 0 ! (q - 1) !} 2 ^ {q - 1} \frac {(2 t _ {k - 1} + 2 i - 1) !}{(2 t _ {k - 1} + 2 i + 2 q - 1) !} \frac {(t _ {k - 1} + i + q - 2) !}{(t _ {k - 1} + i - 1) !} \\
= (2 q - 1) 2 \left(t _ {k - 1} + i + q - 1\right) \cdot \frac {(2 q - 2) !}{2 ^ {q} 0 ! (q - 1) !} 2 ^ {q} \frac {(2 t _ {k - 1} + 2 i - 1) !}{(2 t _ {k - 1} + 2 i + 2 q - 1) !} \frac {(t _ {k - 1} + i + q - 2) !}{(t _ {k - 1} + i - 1) !} \\
= (2 q - 1) 2 \cdot \frac {(2 q - 2) !}{2 ^ {q} 0 ! (q - 1) !} 2 ^ {q} \frac {(2 t _ {k - 1} + 2 i - 1) !}{(2 t _ {k - 1} + 2 i + 2 q - 1) !} \frac {(t _ {k - 1} + i + q - 1) !}{(t _ {k - 1} + i - 1) !} \\
= (2 q - 1) 2 \cdot \frac {q}{(2 q) (2 q - 1)} \cdot \frac {(2 q - 0) !}{2 ^ {q} 0 ! (q - 0) !} 2 ^ {q} \frac {(2 t _ {k - 1} + 2 i - 1) !}{(2 t _ {k - 1} + 2 i + 2 q - 1) !} \frac {(t _ {k - 1} + i + q - 1) !}{(t _ {k - 1} + i - 1) !} \\
= \frac {(2 q - 0) !}{2 ^ {q} 0 ! (q - 0) !} 2 ^ {q} \frac {(2 t _ {k - 1} + 2 i - 1) !}{(2 t _ {k - 1} + 2 i + 2 q - 1) !} \frac {(t _ {k - 1} + i + q - 1) !}{(t _ {k - 1} + i - 1) !} \\
= P \left(\tilde {Y} _ {i, q} = 0\right) \tag {13}
\end{array}
$$

2. Proof of Eq. (8) where $j = q$ using $\tilde{Y}_{i,q} = q \Leftrightarrow X_{i + q} &lt; 2t_{k - 1} + i \wedge \tilde{Y}_{i,q - 1} = q - 1$

$$
\begin{array}{l}
P \left(X _ {i + q} &lt; 2 t _ {k - 1} + i \wedge \tilde {Y} _ {i, q - 1} = q - 1\right) \\
= P \left(X _ {i + q} &lt; 2 t _ {k - 1} + i \mid \tilde {Y} _ {i, q - 1} = q - 1\right) \cdot P \left(\tilde {Y} _ {i, q - 1} = q - 1\right)
\end{array}
$$

$$
\begin{array}{l}
\stackrel {2. (1 1)} {=} \frac {1}{2 t _ {k - 1} + 2 i + q - 1} \cdot \frac {(q - 1) !}{2 ^ {0} (q - 1) ! 0 !} 2 ^ {q - 1} \frac {(2 t _ {k - 1} + 2 i + q - 2) !}{(2 t _ {k - 1} + 2 i + 2 q - 3) !} \frac {(t _ {k - 1} + i + q - 2) !}{(t _ {k - 1} + i - 1) !} \\
= \left(2 t _ {k - 1} + 2 i + q - 1\right) \cdot \frac {(q - 1) !}{2 ^ {0} (q - 1) ! 0 !} 2 ^ {q} \frac {(2 t _ {k - 1} + 2 i + q - 2) !}{(2 t _ {k - 1} + 2 i + 2 q - 1) !} \frac {(t _ {k - 1} + i + q - 1) !}{(t _ {k - 1} + i - 1) !} \\
= \frac {(q - 1) !}{2 ^ {0} (q - 1) ! 0 !} 2 ^ {q} \frac {(2 t _ {k - 1} + 2 i + q - 1) !}{(2 t _ {k - 1} + 2 i + 2 q - 1) !} \frac {(t _ {k - 1} + i + q - 1) !}{(t _ {k - 1} + i - 1) !} \\
= \frac {(q) !}{2 ^ {0} (q) ! 0 !} 2 ^ {q} \frac {(2 t _ {k - 1} + 2 i + q - 1) !}{(2 t _ {k - 1} + 2 i + 2 q - 1) !} \frac {(t _ {k - 1} + i + q - 1) !}{(t _ {k - 1} + i - 1) !} \\
= P \left(\tilde {Y} _ {i, q} = q\right) \tag {14}
\end{array}
$$

On the Average Case of MergeInsertion

3. Proof of Eq. (8) where $0 &lt; j &lt; q$ using

$$
\tilde{Y}_{i,q} = j \Leftrightarrow (X_{i+q} &lt; 2t_{k-1} + i \wedge \tilde{Y}_{i,q-1} = j - 1) \vee (X_{i+q} \geq 2t_{k-1} + i \wedge \tilde{Y}_{i,q-1} = j)
$$

$$
\begin{aligned}
P(X_{i+q} &amp;&lt; 2t_{k-1} + i \wedge \tilde{Y}_{i,q-1} = j - 1) \\
&amp;\quad + P(X_{i+q} \geq 2t_{k-1} + i \wedge \tilde{Y}_{i,q-1} = j) \\
&amp;= P\left(X_{i+q} &lt; 2t_{k-1} + i \mid \tilde{Y}_{i,q-1} = j - 1\right) \cdot P(\tilde{Y}_{i,q-1} = j - 1) \\
&amp;\quad + P\left(X_{i+q} \geq 2t_{k-1} + i \mid \tilde{Y}_{i,q-1} = j\right) \cdot P(\tilde{Y}_{i,q-1} = j)
\end{aligned}
$$

$$
\begin{aligned}
\text{Thm. 2. (11)} &amp; \left(\frac{122t_{k-1} + 2i + j - 1}{2t_{k-1} + 2i + 2q - 1} \cdot \frac{(2q - j - 1)!}{(2q - j)!} 2^{q - 1} \frac{(2t_{k-1} + 2i + j - 2)!}{(2t_{k-1} + 2i + 2q - 3)!} \frac{(t_{k-1} + i + q - 2)!}{(t_{k-1} + i - 1)!}\right) \\
&amp;\quad + \frac{2q - j - 1}{2t_{k-1} + 2i + 2q - 1} \cdot \frac{(2q - j - 2)!}{2^{q - j}(j - 1)!(q - j)!} 2^{q - 1} \frac{(2t_{k-1} + 2i + j - 1)!}{(2t_{k-1} + 2i + 2q - 3)!} \frac{(t_{k-1} + i + q - 2)!}{(t_{k-1} + i - 1)!} \\
&amp;= (2t_{k-1} + 2i + j - 1) \cdot \frac{(2q - j - 1)!}{2^{q - j}(j - 1)!(q - j)!} 2^{q} \frac{(2t_{k-1} + 2i + j - 2)!}{(2t_{k-1} + 2i + 2q - 1)!} \frac{(t_{k-1} + i + q - 1)!}{(t_{k-1} + i - 1)!} \\
&amp;\quad + (2q - j - 1) \cdot \frac{(2q - j - 2)!}{2^{q - j}(j - 1)!(q - j)!} 2^{q} \frac{(2t_{k-1} + 2i + j - 1)!}{(2t_{k-1} + 2i + 2q - 1)!} \frac{(t_{k-1} + i + q - 1)!}{(t_{k-1} + i - 1)!} \\
&amp;= \left(\frac{(2q - j - 1)!}{2^{q - j}(j - 1)!(q - j)!} + \frac{(2q - j - 1)!}{2^{q - j}(j - 1)!(q - j)!}\right) 2^{q} \frac{(2t_{k-1} + 2i + j - 1)!}{(2t_{k-1} + 2i + 2q - 1)!} \frac{(t_{k-1} + i + q - 1)!}{(t_{k-1} + i - 1)!} \\
&amp;= \left(\frac{j}{2q - j} + \frac{2(q - j)}{2q - j}\right) \frac{(2q - j)!}{2^{q - j}j!(q - j)!} 2^{q} \frac{(2t_{k-1} + 2i + j - 1)!}{(2t_{k-1} + 2i + 2q - 1)!} \frac{(t_{k-1} + i + q - 1)!}{(t_{k-1} + i - 1)!} \\
&amp;= \frac{(2q - j)!}{2^{q - j}j!(q - j)!} 2^{q} \frac{(2t_{k-1} + 2i + j - 1)!}{(2t_{k-1} + 2i + 2q - 1)!} \frac{(t_{k-1} + i + q - 1)!}{(t_{k-1} + i - 1)!} \\
&amp;= P(\tilde{Y}_{i,q} = j)
\end{aligned}
\tag{15}
$$

From Eq. (8) we can derive Theorem 2 using the Eq. (7).

$$
\begin{aligned}
P(Y_i = j) \\
&amp;= P(\tilde{Y}_{i,t_k - t_{k-1} - i} + 2t_{k-1} + i - 1 = j) \\
&amp;= P(\tilde{Y}_{i,t_k - t_{k-1} - i} = j - 2t_{k-1} - i + 1) \\
&amp;= \frac{(2t_k - 2t_{k-1} - 2i - j + 2t_{k-1} + i - 1)!}{2^{t_k - t_{k-1} - i - j + 2t_{k-1} + i - 1}(j - 2t_{k-1} - i + 1)! (t_k - t_{k-1} - i - j + 2t_{k-1} + 1 - 1)!} \\
&amp;\quad \cdot 2^{t_k - t_{k-1} - i} \frac{(2t_{k-1} + 2i + j - 2t_{k-1} - i + 1 - 1)!}{(2t_{k-1} + 2i + 2t_k - 2t_{k-1} - 2i - 1)!} \frac{(t_{k-1} + i + t_k - t_{k-1} - i - 1)!}{(t_{k-1} + i - 1)!} \\
&amp;= \frac{(2t_k - i - j - 1)!}{2^{2^k - j - 1} (-2t_{k-1} - 1 + j + 1)! (2^k - j - 1)!} \cdot 2^{t_k - t_{k-1} - i} \frac{(i + j)!}{(2t_k - 1)!} \frac{(t_k - 1)!}{(t_{k-1} + i - 1)!} \\
&amp;= 2^{j - 2t_{k-1} - i + 1} \frac{(2t_k - i - j - 1)!}{(-2t_{k-1} - 1 + j + 1)! (2^k - j - 1)!} \frac{(i + j)!}{(2t_k - 1)!} \frac{(t_k - 1)!}{(t_{k-1} + i - 1)!}
\end{aligned}
\tag{16}
$$

## B.3 Proof of Theorem 3

The exact probability that $b_{t_{k-1}+i}$ is inserted into $j$ elements is given by Theorem 2. We are especially interested in the case of $b_{t_{k-1}+u}$ where $u = \left\lfloor \frac{t_k - t_{k-1}}{2} \right\rfloor$, because if we know $P(Y_u &lt; m)$ then we can use that for all $q &lt; u$ the probability of $b_{t_{k-1}+q}$ being inserted into less than $m$ elements is at least $P(Y_u &lt; m)$,

Florian Stober and Armin Weiβ

![img-25.jpeg](img-25.jpeg)
Fig. 17: Configuration where one batch is to be inserted.

i.e.  $P(Y_{q} &lt; m) \geq P(Y_{u} &lt; m)$ . This is because when  $b_{t_{k-1}+i}$  is inserted into  $m$  elements, then no matter which position it is inserted into, the next element,  $b_{t_{k-1}+i-1}$ , is inserted into at most  $m$  elements.

However Theorem 2 is hard to work with, so we approximate it with a binomial distribution. For a given  $k$  let  $d = t_k - t_{k-1}$  be the number of elements that are inserted as part of the batch. This configuration is illustrated in Fig. 17. Remember  $u = \frac{t_k - t_{k-1}}{2} = \frac{d}{2}$ . To calculate into how many elements  $b_{t_{k-1} + u} = b_{t_{k-1} + \frac{d}{2}}$  is inserted, we ask how many elements out of  $b_{t_{k-1} + \left\lfloor \frac{3}{4} d \right\rfloor}$  to  $b_{t_k}$  (marked as section B in Fig. 17) are inserted between  $a_{t_{k-1} + \frac{d}{2} + 1}$  and  $a_{t_{k-1} + \left\lfloor \frac{3}{4} d \right\rfloor - 1}$  (marked as section A).

The rationale is that for each element from section B that is inserted into section A,  $b_{t_{k-1} + u}$  is inserted into one less element. As a lower bound for the probability that an element from section B is inserted into one of the positions in section A we use the probability that  $b_{t_k}$  is inserted between  $a_{t_k - 1}$  and  $a_{t_k}$  which is  $\frac{1}{2t_k - 1}$ .

That is because if we assume that all  $b_{i}$  with  $i &lt; t_{k}$  are inserted before inserting  $b_{t_k}$ , then  $b_{t_k}$  is inserted into  $2t_{k} - 2$  elements, so the probability for each position is  $\frac{1}{2t_k - 1}$ . Since none of the  $b_{i}$  with  $i &lt; t_{k}$  can be inserted between  $a_{t_k - 1}$  and  $a_{t_k}$  because they are all smaller than  $a_{t_k - 1}$ , the probability that  $b_{t_k}$  is inserted between  $a_{t_k - 1}$  and  $a_{t_k}$  does not change when we insert it first as the algorithm demands.

To calculate the probability that an element  $b_{t_k - q}$  with  $q &gt; 0$  is inserted into the rightmost position we assume that all  $b_i$  with  $i &lt; t_k - q$  are inserted before inserting  $b_{t_k - q}$ . Then  $b_{t_k - q}$  is inserted into at most  $2t_k - q - 2$  elements, i.e., the elements  $x_1$  to  $x_{2t_k - 1}$ ,  $a_{t_k - 1 + 1}$  to  $a_{t_k - q - 1}$ ,  $b_{t_k - 1 + 1}$  to  $b_{t_k - q - 1}$  and at most  $q$  elements out of  $b_{t_k - q + 1}$  to  $b_{t_k}$ .

Hence the probability for each position is greater than  $\frac{1}{2t_k - q - 1}$  which is greater than  $\frac{1}{2t_k - 1}$ . Since none of the  $b_i$  with  $i &lt; t_k - q$  can be inserted to the right of  $a_{t_k - q - 1}$ , the probability that  $b_{t_k} - q$  is inserted into any of the positions between  $a_{t_k - q - 1}$  and  $a_{t_k - q}$  remains unchanged when inserting the elements in the correct order.

The probability that an element is inserted at a specific position is monotonically decreasing with the index. This is because if an element  $b_{i}$  is inserted to the left of an element  $a_{i - h}$  then  $b_{i - h}$  is inserted into one more element than it would be if  $b_{i}$  had been inserted to the right of  $a_{i - h}$ . As a result any position

On the Average Case of MergeInsertion

further to the left is more likely than the right-most position, so we can use that as a lower bound.

There are $\left\lfloor \frac{d}{4} \right\rfloor - 1$ elements in section A, i.e., there are at least $\left\lfloor \frac{d}{4} \right\rfloor$ positions where an element can be inserted. Hence the probability that an element from section B is inserted into section A is at least $\frac{\left\lfloor \frac{d}{4} \right\rfloor}{2t_k - 1}$ and consequently the probability that it is not inserted before $b_{t_{k-1} + u}$ is at least $\frac{\left\lfloor \frac{d}{4} \right\rfloor}{2t_k - 1}$. That is because all positions part of section A are after $a_{t_{k-1} + u}$.

Section B contains $\left\lceil \frac{d}{2} \right\rceil$ elements. Using that and substituting $u = \frac{d}{2}$ we obtain the binomial distribution with the parameters $n_B = \left\lceil \frac{u}{2} \right\rceil$ and $p_B = \frac{\left\lfloor \frac{d}{4} \right\rfloor}{2t_k - 1}$. As a result we have

$$
p(j) = \binom{\left\lceil \frac{u}{2} \right\rceil}{q} \left(\frac{\left\lfloor \frac{u}{2} \right\rfloor}{2t_k - 1}\right)^q \left(\frac{2t_k - 1 - \left\lfloor \frac{u}{2} \right\rfloor}{2t_k - 1}\right)^{\left\lceil \frac{u}{2} \right\rceil - q} \tag{17}
$$

with $q = 2^k - 1 - j$, that by construction fulfills the property given in Equation (18) for all $j_0$.

$$
\sum_{j = 0}^{j_0} p(j) \leq \sum_{j = 0}^{j_0} P(Y_u = j) = P(Y_u \leq j_0) \tag{18}
$$

Fig. 18 compares our approximation $p(j)$ with real distribution $P(Y_u = j)$. We observe that the maximum of our approximation is further to the right than the one of the real distribution.

![img-26.jpeg](img-26.jpeg)
Fig. 18: Difference between the real distribution and our approximation for $k = 8$ and $u = 43$.

Florian Stober and Armin Weiβ

By using the approximation $P(Y_{u} = j) \approx p(j)$ we can calculate a lower bound for the median of $Y_{\frac{t_k - t_{k-1}}{2}}$

$$
\begin{array}{l}
2^{k} - 1 - \left\lfloor n_{B} \cdot p_{B} \right\rfloor \\
= 2^{k} - 1 - \left\lfloor \left\lceil \frac{t_{k} - t_{k-1}}{4} \right\rceil \frac{\left\lfloor \frac{t_{k} - t_{k-1}}{4} \right\rfloor}{2 t_{k} - 1} \right\rfloor \\
= 2^{k} - 1 - \left\lfloor \left(\frac{2^{k-2} + (-1)^{k} - 3}{3} + \frac{1}{2} (-1)^{k} + \frac{1}{2}\right) \left(\frac{2^{k-2} + (-1)^{k} - 3}{3} + \frac{1}{2} (-1)^{k} - \frac{1}{2}\right) \frac{1}{2 t_{k} - 1} \right\rfloor \\
= 2^{k} - 1 - \left\lfloor \left(\frac{2^{k-2}}{3} + \frac{1}{6} (-1)^{k} + \frac{1}{2}\right) \left(\frac{2^{k-2}}{3} + \frac{1}{6} (-1)^{k} - \frac{1}{2}\right) \frac{1}{2 t_{k} - 1} \right\rfloor \\
= 2^{k} - 1 - \left\lfloor \left(\frac{2^{2k-4}}{9} + \frac{2^{k-2}}{9} (-1)^{k} + \frac{1}{36} - \frac{1}{4}\right) \frac{1}{2 t_{k} - 1} \right\rfloor \\
= 2^{k} - 1 - \left\lfloor \left(\frac{2^{2k-4}}{9} + \frac{2^{k-2}}{9} (-1)^{k} + \frac{1}{36} - \frac{1}{4}\right) \left(\frac{1}{2 \frac{2^{k+1} + (-1)^{k}}{3} - 1}\right) \right\rfloor \\
= 2^{k} - 1 - \left\lfloor \left(\frac{2^{2k-4}}{9} + \frac{2^{k-2}}{9} (-1)^{k} + \frac{1}{36} - \frac{1}{4}\right) \left(\frac{1}{2 \frac{2^{k+1}}{3}} \pm \mathcal{O}(2^{-k})\right) \right\rfloor \\
= 2^{k} - 1 - \left\lfloor \left(\frac{2^{2k-4}}{9} + \frac{2^{k-2}}{9} (-1)^{k} + \frac{1}{36} - \frac{1}{4}\right) \frac{1}{2 \frac{2^{k+1}}{3}} \pm \mathcal{O}(1) \right\rfloor \\
= 2^{k} - 1 - \left\lfloor \frac{2^{k-6}}{3} + \frac{1}{3} (-1)^{k} \right\rfloor \pm \mathcal{O}(1) \Bigg\rfloor \\
\in 2^{k} - 1 - \frac{2^{k-6}}{3} + \mathcal{O}(1)
\end{array}
$$

This tells us that with a probability $\geq 50\%$, $b_{t_{k-1} + u}$ is inserted into $2^k - 1 - \frac{2^{k-6}}{3} \pm \mathcal{O}(1)$ or less elements. In conclusion all $b_i$ with $i \leq u = \frac{t_k - t_{k-1}}{2}$ are inserted into less than $2^k - 1 - \frac{2^{k-6}}{3} \pm \mathcal{O}(1)$ elements with a probability $\geq 50\%$.

Using that result we can calculate a better upper bound for the average case performance of the entire algorithm.

According to Knuth [7] in its worst case MergeInsertion requires $W(n) = n\log n - (3 - \log 3)n + n(y + 1 - 2^y) + \mathcal{O}(\log n)$ comparisons where $y = y(n) = \lceil \log (3n / 4) \rceil - \log (3n / 4) \in [0,1)$.

We calculate the number of comparisons required in the average case in a similar fashion to [4]. Recall Eq. (1) which is the number of comparisons required by the algorithm.

$$
F(n) = \left\lfloor \frac{n}{2} \right\rfloor + F\left(\left\lfloor \frac{n}{2} \right\rfloor\right) + G\left(\left\lceil \frac{n}{2} \right\rceil\right)
$$

$G(m)$ corresponds to the work done in the third step of the algorithm and is given by

$$
G(m) = (k_{m} - \alpha_{m})(m - t_{k_{m}-1}) + \sum_{1 \leq k &lt; k_{m}} (k - \beta_{k})(t_{k} - t_{k-1})
$$

where $t_{k_m - 1} \leq m &lt; t_{k_m}$ and $\alpha_{m}, \beta \in [0,1]$. Inserting an element $b_i$ with $t_{k_{i-1}} &lt; i \leq t_{k_i}$ requires at most $k_i$ comparisons. However, since we are looking at the

On the Average Case of MergeInsertion

average case we need to consider that in some cases $b_{i}$ can be inserted using just $k_{i} - 1$ comparisons. This is reflected by $\alpha_{m}$ and $\beta_{k}$, the first of which has already been studied by [4].

To estimate the cost of an insertion we use the formula $T_{\mathrm{InsAvg}}(m) = \lceil \log m \rceil + 1 - \frac{2^{\lceil \log m \rceil}}{m}$ by [4]. Technically this formula is only correct if the probability of an element being inserted is the same for each position. This is not the case with MergeInsertion. Instead the probability is monotonically decreasing with the index. Binary insertion can be implemented to take advantage of this property, as explained in Section 3, in which case $T_{\mathrm{InsAvg}}(m)$ acts as an upper bound on the cost of an insertion.

Using our result from above that on average $\frac{1}{4}$ of the elements are inserted in less than $2^{k} - 1 - \frac{2^{k-4}}{9} \pm \mathcal{O}(1)$ elements we can calculate $\beta_{k}$ as the difference of the cost of an insertion in the worst-case $(k)$ and in the average case.

$$
\begin{array}{l}
\beta_{k} \geq k - \left(\frac{3}{4} T_{\mathrm{InsAvg}} \left(2^{k}\right) + \frac{1}{4} T_{\mathrm{InsAvg}} \left(2^{k} - \frac{2^{k-6}}{3} \pm \mathcal{O}(1)\right)\right) \\
= k - \left(\frac{3}{4} \left(k + 1 - \frac{2^{k}}{2^{k}}\right) + \frac{1}{4} \left(k + 1 - \frac{2^{k}}{2^{k} - \frac{2^{k-6}}{3} \pm \mathcal{O}(1)}\right)\right) \\
= -1 + \frac{3}{4} + \frac{1}{4} \cdot \frac{1}{1 - \frac{1}{1 - \frac{2^{-6}}{3}} \pm \mathcal{O}(2^{-k})} \\
= -\frac{1}{4} + \frac{1}{4} \cdot \frac{1}{1 - \frac{1}{192}} \pm \mathcal{O}(2^{-k}) \\
= -\frac{1}{4} + \frac{1}{4} \cdot \frac{1}{\frac{191}{192}} \pm \mathcal{O}(2^{-k}) \\
= -\frac{1}{4} + \frac{1}{4} \cdot \frac{192}{191} \pm \mathcal{O}(2^{-k}) \\
= \frac{1}{764} \pm \mathcal{O}(2^{-k})
\end{array}
$$

Combining this with Appendix B.3 we can calculate the difference between the worst-case and the average-case as

$$
\begin{array}{l}
G_{\text{worst-case}}(m) - G_{\text{average-case}}(m) \\
= k_{m}(m - t_{k_{m}-1}) + \sum_{1 \leq k &lt; k_{m}} k(t_{k} - t_{k-1}) \\
\quad - (k_{m} - \alpha_{m})(m - t_{k_{m}-1}) - \sum_{1 \leq k &lt; k_{m}} (k - \beta_{k})(t_{k} - t_{k-1}) \\
= \alpha_{m}(m - t_{k_{m}-1}) + \sum_{1 \leq k &lt; k_{m}} \beta_{k}(t_{k} - t_{k-1}) \\
\geq \alpha_{m}(m - t_{k_{m-1}}) + \sum_{1 \leq k &lt; k_{m}} \left(\frac{1}{764} \pm \mathcal{O}(2^{-k})\right)(t_{k} - t_{k-1})
\end{array}
$$

Florian Stober and Armin Weiß

$$
\begin{array}{l}
= \alpha_{m} (m - t_{k_{m}-1}) + \frac{1}{764} (t_{k_{m-1}} - t_{1}) \pm \mathcal{O}(\log m) \\
= \alpha_{m} (m - t_{k_{m}-1}) + \frac{1}{764} t_{k_{m-1}} \pm \mathcal{O}(\log m) \\
= \alpha_{m} (m - t_{k_{m}-1}) + \frac{1}{764} \frac{2_{m}^{k} + (-1)^{k_{m}-1}}{3} \pm \mathcal{O}(\log m) \\
= \alpha_{m} (m - t_{k_{m}-1}) + \frac{1}{764} \frac{2^{k_{m}}}{3} \pm \mathcal{O}(\log m) \tag{19}
\end{array}
$$

By writing $m$ as $m = 2^{l_m - \log 3 + x}$ with $x \in [0,1)$ we get $l_m = \lfloor \log 3m \rfloor$. To approximate $k_m$ with $l_m$ we need to show that $k_m \geq l_m$. Recall that $t_{k_m - 1} \leq m &lt; t_{k_m}$. For all $t_{k_m - 1} &lt; m &lt; t_{k_m}$ we have

$$
\frac{2^{k_{m}} + (-1)^{k_{m}-1}}{3} &lt; m &lt; \frac{2^{k_{m}+1} + (-1)^{k_{m}}}{3}
$$

Since $m \in \mathbb{N}$ and $t_k \in \mathbb{N}$ adding/subtracting $\frac{1}{3}$ does not alter the relation, so we obtain

$$
\frac{2^{k_{m}}}{3} &lt; m &lt; \frac{2^{k_{m}+1}}{3}
$$

which resolves to

$$
k_{m} &lt; \log 3n &lt; k_{m} + 1
$$

Thus $k_{m} = \lfloor \log 3m \rfloor = l_{m}$.

For $m = t_{k_m - 1}$ we get

$$
\begin{array}{l}
\frac{2^{k_{m}} + (-1)^{k_{m}-1}}{3} = m \\
\Longleftrightarrow \quad 2^{k_{m}} = 3m + (-1)^{k_{m}} \\
\Longleftrightarrow \quad k_{m} = \log \left(3m + (-1)^{k_{m}}\right) \\
\end{array}
$$

If $k_m = \log (3m + 1)$ that resolves to $k_m = \log (3m + 1) &gt; \log (3m) &gt; \lfloor \log 3m \rfloor = l_m$.

If instead $k_m = \log (3m - 1)$ using $k_m \in \mathbb{N}$ we have $k_m = \lfloor \log (3m - 1) \rfloor$ and for all $m \geq 1$ this is equal to $\lfloor \log 3m \rfloor = l_m$.

Hence in all cases $l_m \leq k_m$ holds. Therefore we can replace $k_m$ with $l_m$ in Eq. (19):

$$
G_{\text{worst-case}}(m) - G_{\text{average-case}}(m) \geq \alpha_{m} (m - t_{k_{m}-1}) + \frac{1}{764} \frac{2^{l_{m}}}{3} \pm \mathcal{O}(\log m)
$$

From [4] we know that the $\alpha_{m}(m - t_{k_{m}-1})$ term can be approximated with $(m - 2^{l_{m} - \log 3})\left(\frac{2^{l_{m}}}{m + 2^{l_{m} - \log 3}} - 1\right)$.

$$
\begin{array}{l}
G_{\text{worst-case}}(m) - G_{\text{average-case}}(m) \\
\geq \left(m - 2^{l_{m} - \log 3}\right) \left(\frac{2^{l_{m}}}{m + 2^{l_{m} - \log 3}} - 1\right) + \frac{1}{764} \frac{2^{l_{m}}}{3} \pm \mathcal{O}(\log m) \\
\end{array}
$$

On the Average Case of MergeInsertion

Now we calculate

$$
\begin{array}{l}
S (n) = F _ {\text {w o r s t - c a s e}} (m) - F _ {\text {a v e r a g e - c a s e}} (m) \\
= \left\lfloor \frac {n}{2} \right\rfloor + F _ {\text {w o r s t - c a s e}} \left(\left\lfloor \frac {n}{2} \right\rfloor\right) + G _ {\text {w o r s t - c a s e}} \left(\left\lceil \frac {n}{2} \right\rceil\right) \\
- \left\lfloor \frac {n}{2} \right\rfloor - F _ {\text {a v e r a g e - c a s e}} \left(\left\lfloor \frac {n}{2} \right\rfloor\right) - G _ {\text {a v e r a g e - c a s e}} \left(\left\lceil \frac {n}{2} \right\rceil\right) \\
= S \left(\left\lfloor \frac {n}{2} \right\rfloor\right) + G _ {\text {w o r s t - c a s e}} \left(\left\lceil \frac {n}{2} \right\rceil\right) - G _ {\text {a v e r a g e - c a s e}} \left(\left\lceil \frac {n}{2} \right\rceil\right) \\
\geq S \left(\left\lfloor \frac {n}{2} \right\rfloor\right) + \left(m - 2 ^ {l _ {m} - \log 3}\right) \left(\frac {2 ^ {l _ {m}}}{m + 2 ^ {l _ {m} - \log 3}} - 1\right) + \frac {1}{7 6 4} \frac {2 ^ {l _ {m}}}{3} \pm \mathcal {O} (\log m) \tag {20}
\end{array}
$$

We split  $S(n)$  into  $S_{\alpha}(n) + S_{\beta}(n)$  with

$$
S _ {\alpha} (n) \geq S _ {\alpha} \left(\left\lfloor \frac {n}{2} \right\rfloor\right) + \left(m - 2 ^ {l _ {m} - \log 3}\right) \left(\frac {2 ^ {l _ {m}}}{m + 2 ^ {l _ {m} - \log 3}} - 1\right)
$$

$$
S _ {\beta} (n) \geq S _ {\beta} \left(\left\lfloor \frac {n}{2} \right\rfloor\right) + \frac {1}{7 6 4} \frac {2 ^ {l _ {m}}}{3} \pm \mathcal {O} (\log m)
$$

From [4] we know  $S_{\alpha}(n) \geq \left(n - 2^{l_n - \log 3}\right)\left(\frac{2^{l_n}}{n + 2^{l_n - \log 3}} - 1\right) + \mathcal{O}(1)$ .

For  $S_{\beta}(n)$  we obtain

$$
\begin{array}{l}
S _ {\beta} (n) \geq \sum_ {i = 1} ^ {l _ {n} - 1} \frac {2 ^ {i}}{7 6 4 \cdot 3} \pm \mathcal {O} (\log 2 ^ {i}) \\
= \frac {2 ^ {l _ {n}}}{2 2 9 2} \pm \mathcal {O} \left(\log^ {2} n\right)
\end{array}
$$

We can represent  $n$  as  $2^{k - \log 3 + x_n}$  with  $x_{n}\in [0,1)$ . This leads to

$$
\begin{array}{l}
\frac {S (n)}{n} = \frac {S _ {\alpha} (n) + S _ {\beta} (n)}{n} \\
= \frac {2 ^ {k - \log 3 + x _ {n}} - 2 ^ {k - \log 3}}{2 ^ {k - \log 3 + x _ {n}}} \left(\frac {2 ^ {k}}{2 ^ {k - \log 3 + x _ {n}} + 2 ^ {k - \log 3}} - 1\right) + \frac {2 ^ {k}}{2 2 9 2 \cdot 2 ^ {k - \log 3 + x _ {n}}} \pm \mathcal {O} \left(\frac {\log^ {2} n}{n}\right) \\
= \left(1 - 2 ^ {- x _ {n}}\right) \left(\frac {3}{2 ^ {x _ {n}} + 1} - 1\right) + \frac {2 ^ {\log 3 - x _ {n}}}{2 2 9 2} \pm \mathcal {O} \left(\frac {\log^ {2} n}{n}\right)
\end{array}
$$

By writing  $F(n)$  as  $F(n) = n\log n - c(x_{n})\cdot n\pm \mathcal{O}(\log^{2}n)$  we get

$$
\begin{array}{l}
c \left(x _ {n}\right) \geq - \frac {\left(F (n) - n \log n\right)}{n} \\
= - \frac {\left(W (n) - S (n) - n \log n\right)}{n} \\
= (3 - \log 3) - (y + 1 - 2 ^ {y}) + (1 - 2 ^ {- x _ {n}}) \left(\frac {3}{2 ^ {x _ {n}} + 1} - 1\right) + \frac {2 ^ {\log 3 - x _ {n}}}{2 2 9 2}
\end{array}
$$

With  $y = 1 - x_{n}$  we obtain Theorem 3.

Florian Stober and Armin Wei

![img-27.jpeg](img-27.jpeg)
Fig. 19: Configuration where one batch of  $e - s$  elements,  $b_{s + 1}$  to  $b_{e}$ , remains to be inserted.

# C Details on Computing the Exact Number of Comparisons

The code for calculating  $F(n)$  and  $G(n)$  is shown in Algorithm 2 and Algorithm 3 respectively.

$\mathrm{Cost}(s,e)$  is the number of comparisons required for inserting the batch of elements that consists of  $b_{s+1}$  to  $b_e$ . Such a configuration can be seen in Fig. 19.  $\mathrm{Cost}(s,e)$  is computed by calculating the external path length of the decision tree and dividing by the number of leaves. To improve performance we apply the following optimization: We collapse "identical" branches of the decision tree. E.g. whether  $b_e$  is inserted between  $x_1$  and  $x_2$  or between  $x_2$  and  $x_3$  does not influence the number of comparisons required to insert the subsequent elements. So we can neglect that difference. However, if  $b_e$  is inserted between  $a_{e-1}$  and  $a_e$  then the next element (and all thereafter) is inserted into one less element. So this is a difference we need to acknowledge. Same if an element is inserted between any  $a_i$  and  $a_{i+1}$ . By the time we insert  $b_i$  the element inserted between  $a_i$  and  $a_{i+1}$  is known to be larger than  $b_i$  and thus is no longer part of the main chain, resulting in  $b_i$  being inserted into one element less. In conclusion that means that our algorithm needs to keep track of the elements inserted between any  $a_i$  and  $a_{i+1}$  as well as those inserted at any position before  $a_{s+1}$  as two branches of the decision tree that differ in any of these cannot be collapsed. Algorithm 4 shows how this is implemented.

Algorithm 2 Computation of  $F(n)$
1: procedure COMPUTEF(n)
2: if  $n = 1$  then
3: return 0
4: else
5: return  $\lfloor \frac{n}{2} \rfloor + \text{COMPUTEF}(\lfloor \frac{n}{2} \rfloor) + \text{COMPUTEG}(\lceil \frac{n}{2} \rceil)$
6: end if
7: end procedure

On the Average Case of MergeInsertion

Algorithm 3 Computation of  $G(n)$
1: procedure COMPUTEG(n)
2:  $k \gets 2$
3:  $c \gets 0$
4: while  $t_k &lt; n$  do
5:  $c \gets c + \mathrm{COST}(t_{k-1}, t_k)$
6:  $k \gets k + 1$
7: end while
8:  $c \gets c + \mathrm{COST}(t_{k-1}, n)$
9: return  $c$
10: end procedure

Algorithm 4 Computation of  $\mathrm{Cost}(s,e)$
1: procedure COST(s, e)
2:  $r \gets e - s$  ▷ next element to be inserted is  $b_r$
3:  $q_1 \gets 2s$  ▷ number of elements on the main chain that are  $&lt; a_{s+1}$
4:  $q_2, \ldots, q_r \gets 0$  ▷  $q_i$  is the number of elements between  $as + i - 1$  and  $a_{s+i}$
5:  $(p, l) \gets \mathrm{COSTINSERT}(r, q_1, \ldots, q_r)$
6: return  $\frac{p}{r}$
7: end procedure
8:
9: procedure COSTINSERT(r,  $q_1, \ldots, q_r$ )
10: if  $r = 0$  then
11: return (0, 1) ▷ We reached a leave
12: end if
13: elements  $\gets r - 1 + \sum q_i$  ▷ number of elements  $b_r$  is inserted into
14:  $k \gets [\log(\text{elements} + 1)]$
15: cheap_insertions  $\gets 2^k - \text{elements} - 1$
16:  $p \gets 0$  ▷ external path length
17:  $l \gets 0$  ▷ number of leaves
18: index  $\gets 0$  ▷ We iterate over all indices where  $b_r$  can be inserted
19: for all  $0 &lt; i \leq r$  do
20:  $(p_c, l_c) \gets \mathrm{COSTINSERT}(r - 1, q_1, \ldots, q_{i-1}, q_i + 1, q_{i+1}, \ldots, q_{r-1})$
21: repeat  $q_i + 1$  times ▷  $q_i + 1$  positions between  $a_{s+i-1}$  and  $a_{s+i}$
22: if index &lt; cheap_insertions then
23:  $p \gets p + p_c + (k - 1) \cdot l_c$
24: else
25:  $p \gets p + p_c + k \cdot l_c$
26: end if
27:  $l \gets l + l_c$
28: index  $\gets$  index + 1
29: end
30: end for
31: return (p, l)
32: end procedure

Florian Stober and Armin Weiß

# D Implementing MergeInsertion

To perform experiments we first need to implement the algorithm. For the purpose of our implementation we assume that each element is unique. This condition is easy to fulfill for synthetic test data. You can see our implementation in Algorithm 5. We now go over some of the key challenges when implementing MergeInsertion.

Algorithm 5 MergeInsertion
1: procedure MERGEINSERTION(d: array of  $n$  elements)
2: Step 1: Pairwise comparison
3: for all  $1 \leq i \leq \left\lfloor \frac{n}{2} \right\rfloor$  do ▷ Split into larger and smaller half
4:  $a_i \gets \max \left\{d_i, a_{i + \left\lfloor \frac{n}{2} \right\rfloor} \right\}$
5:  $b_i \gets \min \left\{d_i, a_{i + \left\lfloor \frac{n}{2} \right\rfloor} \right\}$
6: end for
7: if  $n \mod 2 = 1$  then
8:  $b_{\left\lceil \frac{n}{2} \right\rceil} \gets d_n$
9: end if
10: Step 2: Recursion and Renaming
11:  $m \gets \{(a_i, b_i) \mid 1 \leq i \leq \left\lfloor \frac{n}{2} \right\rfloor \}$ ▷ Store mapping
12:  $a \gets \text{MERGEINSERTION}(a)$
13: for all  $1 \leq i \leq \left\lfloor \frac{n}{2} \right\rfloor$  do ▷ Permute smaller half
14:  $b_i \gets e$  where  $(a_i, e) \in m$
15: end for
16: Step 3: Insertion
17:  $d \gets b_1, a_1, \ldots, a_{\left\lfloor \frac{n}{2} \right\rfloor}$
18:  $k \gets 2$
19: while  $t_{k-1} &lt; \left\lceil \frac{n}{2} \right\rceil$  do
20:  $m \gets \min \left\{t_k, \left\lceil \frac{n}{2} \right\rceil \right\}$ ▷ first element of the batch
21:  $u \gets t_{k-1} + m$ ▷ position of  $a_m$  in  $d$
22: for  $i$  in  $m$  down to  $t_{k-1} + 1$  do
23:  $d \gets \text{BINARYINSERTION}(b_i, d_1, \ldots, d_{u-1}), d_u, \ldots, d_{2m + t_{k-1}-i}$
24: while  $d_u \neq a_{i-1}$  do ▷ adjust  $u$
25:  $u \gets u - 1$
26: end while
27: end for
28:  $k \gets k + 1$
29: end while
30: return  $d$
31: end procedure

1. MergeInsertion requires elements to be inserted into arbitrary positions. When using a simple array to store the elements this operation requires moving  $\mathcal{O}(n)$  elements. Since MergeInsertion inserts each element exactly

On the Average Case of MergeInsertion

once this results in a complexity of $\mathcal{O}(n^{2})$. To avoid this we store the elements in a custom data structure inspired by the Rope data structure*[1]* used in text processing. Being based on a tree it offers $\mathcal{O}(\log n)$ performance for lookup, insertion and deletion operations, thus putting our Algorithm in $\mathcal{O}(n\log^{2}n)$.
2. In the second step of the algorithm we need to rename the $b_{i}$ after the recursive call. Our chosen solution is to store which $a_{i}$ corresponds to which $b_{i}$ in a hash map(line 11) before the recursive call and use the information to reorder the $b_{i}$ afterwards(line 13). The disadvantage of this solution is that it requires each element to be unique and the hash map might introduce additional comparisons.

An alternative would be to have the recursive call generate the permutation it applies to the larger elements and then apply that to the smaller ones. That is a cleaner solution as it does not require the elements to be unique and it avoids potentially introducing additional comparisons. It is also potentially faster, though not by much. However, we stuck with using a hash map as that solution is easier to implement.
3. In the insertion step we need to know into how many elements a specific $b_{i}$ is inserted. For $b_{t_{k}}$ this is $2^{k}-1$ elements. However, for other elements that number can be smaller depending on where the previous elements have been inserted. To account for that we create the variable $u$ in line 21. It holds the position of the $a_{i}$ corresponding to the element $b_{i}$ that is inserted next. Thus $b_{i}$ is inserted into $u-1$ elements (since $b_{i}&lt;a_{i}$). After the insertion of $b_{i}$, we decrease $u$ in line 25 until it matches the position of $a_{i-1}$, which is what we want as $b_{i-1}$ is the next element to be inserted. This step also makes use of the requirement that each element is unique.

At this point we have to be aware that testing whether the element at position $u$ is $a_{i-1}$ might introduce additional comparisons to the algorithm. This is acceptable because we do not count these comparisons. Also these are not necessary. We could keep track of the positions of the elements $a_{i}$ however we choose not to, in order to keep the implementation simple.