/*************************************************************************
*
*  Pace University
*  Spring 2024
*  Algorithms and Computing Theory
*
*  Course: CS 608
*  Team members: Adhikari Vidhyadhar, Rushab Ramesh Vaza , Hrishikesh shah
*  Other collaborators: NONE.
*  References:https://www.geeksforgeeks.org/binary-search-tree-data-structure/
              https://www.geeksforgeeks.org/introduction-to-red-black-tree/
              https://www.geeksforgeeks.org/treemap-in-java/
*
*  Assignment No.: 2
*
*  Input:  
*  Output: n = 6^2  n = 6^3         n = 6^4         n = 6^5         n = 6^6
------------------------------------------------
SkewedBST        BalancedBST     TreeMap
2600 ns         200 ns          3600 ns
3600 ns         200 ns          1300 ns
28800 ns                600 ns          6100 ns
165900 ns               1000 ns         6800 ns
1558900 ns              9600 ns         33800 ns
*
*  Visible data fields:
*  
* 
* Problem 1. 
* The asymptotic running time of searching in a Binary Search Tree (BST) depends on the tree's structure.

  Skewed BST:
  In a skewed BST, the tree resembles a linked list, with all nodes in a single branch. The search time in the worst case would be O(n), where n is the number of nodes in the tree. This is because in the worst case, you might have to traverse the entire tree to find the desired node.
  The operations involved in searching in a BST are comparisons between the target value and the values stored in each node. In a skewed BST, since the tree is unbalanced, the comparisons will often lead to traversing the entire height of the tree.
  Asymptotic Running Time: O(n)

  Balanced BST:
  In a balanced BST, the tree is structured in a way that each node has approximately equal numbers of nodes in its left and right subtrees. This structure allows for efficient searching.
  The operations involved in searching in a balanced BST include comparisons and navigating down the tree. Since the height of a balanced BST is log(n), the overall search time is logarithmic.
  Asymptotic Running Time: O(log n)

  Justification:
  The BST class likely has methods for searching, comparisons, and traversing the tree. The key operations contributing to the search time are the comparisons between the target value and the values stored in the nodes, as well as navigating down the tree.
  In a skewed BST, the height is proportional to the number of nodes, leading to O(n) time complexity.
  In a balanced BST, the height is logarithmic, resulting in O(log n) time complexity.
  By considering the tree's structure and the logarithmic height of a balanced tree, we can estimate the asymptotic running time for searching in both scenarios.
  Based on the analysis we would like to use the Balanced BST as the running time for Balanced BST is much less than the Skewed BST.
  The analysis is based on the fact that the key factor affecting the efficiency of searching in a BST is the height of the tree.
* 
* Problem 2.
* The code is below.
*                     	|n = 6^2| n = 6^3| n = 6^4| n = 6^5| n = 6^6|
* SkewedBST         	4600      12900    23700    144900   764800
* BalancedBST       	400       600      300      600      1100
* TreeMap				5200      1900     3000     4400     4300
* 
* 
* Problem 3.
For the Skewed BST:
We observe that the running time grows linearly with the input size. This is expected because the Skewed BST is essentially a linked list, and the worst-case time complexity for searching in a linked list is O(n).
As the input size grows by a digit, the running time also grows by a digit, and the rate of growth is linear.

For the Balanced BST:
The running time for searching in a Balanced BST is expected to be logarithmic, as the tree is balanced.
In our case, we create a roughly balanced BST, and the measured running times reflect a logarithmic growth as the input size increases.
As the input size grows by a digit, the running time does not grow by a digit; instead, it grows by a fraction of a digit, indicating the logarithmic behavior.
*
* 
* Problem 4.
* CODE IS SHOWN BELOW.

Analysis and Comparison:
The running times for Tree-map are expected to be different from the Skewed BST and Balanced BST.
Tree-map is implemented as a balanced red-black tree, which should result in logarithmic search times, similar to a balanced BST.

Results:
The running times for Tree-map are relatively low and stable, consistent with logarithmic growth.
The running times for Tree-map are closer to the Balanced BST than the Skewed BST.
This aligns with the argument that Tree-map is implemented as a balanced tree, providing efficient search times.
The differences in running times are likely due to implementation details, but in general, the Tree-map's performance is close to the theoretical expectations for a balanced tree.

Summary:
The running times for Tree-map are similar to the Balanced BST, indicating that the Tree-map class effectively maintains a balanced structure.
The running times for Tree-map are significantly better than the Skewed BST, demonstrating the impact of tree structure on search efficiency.
The results support the argument that data structures with balanced structures, whether implemented by hand or through Java API classes like Tree-map, provide efficient search operations compared to completely skewed structures.
*************************************************************************/



/* 
Problem 2 and 4 SkewedBST/ BalancedBST/ TreeMap
*/

import java.util.Random;
import java.util.TreeMap;

class BinarySearchTree {
    static class Node {
        int data;
        Node left, right;

        public Node(int item) {
            data = item;
            left = right = null;
        }
    }

    Node root;

    BinarySearchTree() {
        root = null;
    }

    void insertSkewed(int key) {
        root = insertSkewedIterative(root, key);
    }

    Node insertSkewedIterative(Node root, int key) {
        Node newNode = new Node(key);
        if (root == null) {
            return newNode;
        }

        Node current = root;
        Node parent = null;
        while (current != null) {
            parent = current;
            if (key < current.data) {
                current = current.left;
            } else if (key > current.data) {
                current = current.right;
            } else {
                // Duplicate values are not allowed
                return root;
            }
        }

        if (key < parent.data) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
        }

        return root;
    }

    void insertBalanced(int key) {
        root = insertBalancedRec(root, key);
    }

    Node insertBalancedRec(Node root, int key) {
        if (root == null) {
            root = new Node(key);
            return root;
        }

        Random rand = new Random();
        if (rand.nextInt(2) == 0) {
            root.left = insertBalancedRec(root.left, key);
        } else {
            root.right = insertBalancedRec(root.right, key);
        }

        return root;
    }

    boolean search(int key) {
        return searchIterative(root, key);
    }

    boolean searchIterative(Node root, int key) {
        while (root != null) {
            if (root.data == key) {
                return true;
            } else if (key < root.data) {
                root = root.left;
            } else {
                root = root.right;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        int[] nValues = { (int) Math.pow(6, 2), (int) Math.pow(6, 3), (int) Math.pow(6, 4), (int) Math.pow(6, 5), (int) Math.pow(6, 6) };

        System.out.println("n = 6^2\t n = 6^3\t n = 6^4\t n = 6^5\t n = 6^6");
        System.out.println("------------------------------------------------");
        System.out.println("SkewedBST\t BalancedBST\t TreeMap");

        for (int n : nValues) {
            BinarySearchTree skewedBST = new BinarySearchTree();
            BinarySearchTree balancedBST = new BinarySearchTree();
            TreeMap<Integer, Integer> treeMap = new TreeMap<>();

            for (int i = 1; i <= n; i++) {
                skewedBST.insertSkewed(i);
                balancedBST.insertBalanced(i);
                treeMap.put(i, i);
            }

            long startTimeSkewed = System.nanoTime();
            skewedBST.search(n + 1); // Search for a number not in the tree
            long endTimeSkewed = System.nanoTime();
            long timeElapsedSkewed = endTimeSkewed - startTimeSkewed;

            long startTimeBalanced = System.nanoTime();
            balancedBST.search(n + 1); // Search for a new random number
            long endTimeBalanced = System.nanoTime();
            long timeElapsedBalanced = endTimeBalanced - startTimeBalanced;

            long startTimeTreeMap = System.nanoTime();
            treeMap.get(n + 1); // Search for a number not in the TreeMap
            long endTimeTreeMap = System.nanoTime();
            long timeElapsedTreeMap = endTimeTreeMap - startTimeTreeMap;

            System.out.print(timeElapsedSkewed + " ns\t\t");
            System.out.print(timeElapsedBalanced + " ns\t\t");
            System.out.print(timeElapsedTreeMap + " ns\t\t");

            System.out.println();
        }
    }
}
