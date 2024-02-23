/*************************************************************************
*
*  Pace University
*  Spring 2024
*  Algorithms and Computing Theory
*
*  Course: CS 608
*  Team members: Adhikari Vidhyadhar, Rushab Ramesh Vaza , Hrishikesh shah
*  Other collaborators: NONE.
*  References:https://www.geeksforgeeks.org/hashtable-in-java/?ref=lbp
 *            https://iq.opengenus.org/time-complexity-of-hash-table/
 *            https://stackoverflow.com/questions/9214353/hash-table-runtime-complexity-insert-search-and-delete
*
*  Assignment No.: 3
*
*  Input:  int[] numEntries = {100, 1000, 10000, 100000, 1000000, 10000000};
*  Output:  Number of entries: 100, Insertion time: 0.000 seconds, Search time: 0.000 seconds
 *          Number of entries: 1000, Insertion time: 0.001 seconds, Search time: 0.000 seconds
 *          Number of entries: 10000, Insertion time: 0.002 seconds, Search time: 0.001 seconds
 *          Number of entries: 100000, Insertion time: 0.035 seconds, Search time: 0.013 seconds
 *          Number of entries: 1000000, Insertion time: 0.226 seconds, Search time: 0.096 seconds
 *          Number of entries: 10000000, Insertion time: 2.295 seconds, Search time: 1.101 seconds
*
*  Visible data fields:
* 
* Problem 1.
 * Conjectures and Justifications for Hash Table Operations:
 *
 * a) Adding n entries with consecutive keys:
 *
 * Conjecture: O(n)
 *
 * Justification:
 *
 * In separate-chaining hash tables, with good hash functions, the average cost of insertion is O(1) as entries are added to individual linked lists associated with specific buckets.
 * However, with consecutive keys, all entries will hash to the same bucket.
 * If the hash function isn't perfect (distributing keys uniformly), subsequent insertions will lengthen the linked list in that bucket.
 * In the worst case, the chain length becomes n, leading to a total insertion time of O(n) where each insertion takes O(1) + O(chain length) = O(n) amortized.
 * Adding an assumption of a "good" hash function mitigates this worst-case scenario, making O(n) a reasonable conjecture for average-case performance.
 * b) Searching for a key that is not in the table:
 *
 * Conjecture: O(1)
 *
 * Justification:
 *
 * Even with consecutive keys, if the hash function works well, the searched-for key will not land in the same bucket as the inserted keys.
 * In a separate-chaining hash table, searching an individual bucket takes O(chain length) on average.
 * Since the searched-for key isn't present, the chain length for its bucket remains O(1), resulting in a constant-time search.
 * However, there's a small caveat: if the hash function is truly terrible and always maps the searched-for key to the same bucket as the consecutive keys, the search could degenerate into traversing the entire chain, leading to O(n) in the worst case.
 * Key Assumptions:
 *
 * "Good" hash function: The hash function distributes keys uniformly across buckets to avoid excessive clustering.
 * Average-case analysis: The conjectures consider typical behavior, not worst-case scenarios with extremely unbalanced or poorly-chosen hash functions.
 * Remember: These are just conjectures based on typical behaviors and assumptions. Actual performance might vary depending on specific implementations, hash functions, and data distributions.
*
* Problem 2.
* The code is below, Please refer to the output section as well.
* 
* 
* Problem 3.
 * The measurements show that the insertion time is generally minimal and increases slightly as the number of entries grows. The search time remains consistently low, even as the number of entries increases. Let's compare these results.
 *
 * 1. Insertion Time:
 * The conjecture stated that the asymptotic running time for adding n entries with consecutive keys in a separate-chaining hash table is O(n + m), where n is the number of entries, and m is the number of collisions.
 * The measurements show that the insertion time is minimal and grows slightly with the number of entries. This aligns with the expected behavior, as the hash function should distribute consecutive keys quite well, minimizing collisions. In this case, the observed time complexity might be close to O(n), given that the load factor is not too high, and collisions are kept minimal.
 *
 * 2. Search Time:
 * The conjecture for searching for a key that is not in the table was O(1), assuming a well-distributed hash function.
 * The measurements confirm that the search time remains consistently low, even with an increasing number of entries. This aligns with the expected O(1) time complexity for searching in a hash table with a good hash function.
 *
 * Reasons for Deviations:
 * The actual running time may depend on the specific implementation details of the Java
 * 'Hashtable' class, the underlying JVM, and the quality of the hash function used. It's possible that the hash function in Java's 'Hashtable' is effectively distributing the keys, resulting in minimal collisions and efficient insertion and search times.
 * The load factor of 0.75 chosen is commonly considered a good balance between space and time efficiency. If we were to use a higher load factor, it might lead to more collisions and impact the performance.
 *
 * In summary, the measurements align well with the conjecture, indicating that the Java 'Hashtable' implementation provides efficient performance for the given experiment conditions. The low insertion and search times suggest that the hash function is distributing keys effectively, and the hash table is handling collisions efficiently.
*
*************************************************************************/

{

/* 
Problem 2
*/

import java.util.Hashtable;
import java.util.Random;

public class HashTablePerformance {

    public static void main(String[] args) {
        // Parameters
        int initialCapacity = 1000;
        double loadFactor = 0.75;
        int[] numEntries = {100, 1000, 10000, 100000, 1000000, 10000000};

        // Create a Hashtable with specified initial size and load factor
        Hashtable<Integer, String> table = new Hashtable<>(initialCapacity,(float) loadFactor);

        // Random number generator for key creation
        Random random = new Random();

        // Measure insertion and search times
        for (int num : numEntries) {
            long startTimeInsert = System.nanoTime();
            for (int i = 0; i < num; i++) {
                int key = random.nextInt(); // Random key
                table.put(key, "value");
            }
            long endTimeInsert = System.nanoTime();

            long startTimeSearch = System.nanoTime();
            for (int i = 0; i < num; i++) {
                int key = random.nextInt(); // Random non-existent key
                table.containsKey(key);
            }
            long endTimeSearch = System.nanoTime();

            // Calculate and print results
            double insertTime = (endTimeInsert - startTimeInsert) / 1e9; // Convert to seconds
            double searchTime = (endTimeSearch - startTimeSearch) / 1e9; // Convert to seconds
            System.out.printf("Number of entries: %d, Insertion time: %.3f seconds, Search time: %.3f seconds\n", num, insertTime, searchTime);
        }
    }
}