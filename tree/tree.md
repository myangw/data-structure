# Tree

- Heap
- Binary Search Tree (BST)
- AVL
- B-tree

> Branching factor: 뻗어나가는 줄기의 개수
Binary tree: 모든 노드의 branching factor가 2이하(자식노드가 2개이하) 

> traverse: 노드들을 방문하는것 .
> traverse하는 순서에 따라
> --Preorder (first traverse the root node)
> --Postorder 
> --Inorder (traverse the root node in the middle) 
> 


## Heap

### Binary Heap 특성
* **Complete** :  왼쪽에서부터 꽉꽉 채워나간다, bottom level을 제외하고는 모두 꽉차있음. ---> array로 구현할 수 있다! 

* **Partially ordered**: 
(1) 자식노드보다 부모노드가 반드시 크거나같다(max heap)
or 
(2) 자식노드보다 부모노드가 반드시 작거나 같다 (min heap)

(c.f.  full :  모든 노드가 leaf노드이거나 children 둘다 가진 노드만 있다) 

### 구현
- 행렬의 1번째 인덱스부터 사용 
- heapify: partially ordered 하게 부모와 자식노드끼리 swap, swap...  O(log n) 
- build max_heap or min_heap : O(n)
- max heap 에서 max_deletion은 A[1]과 A[n]을 바꾸고, A[n]을 delete, 나머지 heapify.


### 응용
* Heap sort --> root를 pop하고 heapify 를 반복 . O(nlog n)
* Priority Queue --> 우선순위 큐 는 큐이긴한데 우선순위가 높은 순으로 빠져나가는 큐. 
그래서 우선순위 체계를 heap으로 구현하고, pop할때 root 노드를 빼는 식으로 하면 우선순위큐가 됨.
* Graph algorithms such as shortest-paths


## Binary Search Tree

### BST 특징
* 어떤 노드 x에 대해 왼쪽 subtree는 x보다 작고, 오른쪽 subtree는 x보다 크다.
* 순회할 때 inorder 방식.
* Binary Search의 빠른 access + 효율적인 insertion/deletion.

#### 시간복잡도
* 최악의 경우: O(n) -- linear tree
* 최상의 경우: O(log n) -- comeplete binary tree일때 
* 'Binary search' 와 다름!: 반으로 나눠서 탐색하는 거라서 O(log n)

## AVL Tree

### AVL 특징
* 정의 : 모든 노드에 대해 left subtree와 right subtree의 height 차이가 1 이하인 BST.
* Binary Search Tree이며, height를 일정하게(O(log n)) 함.
* Insertion 할 때 unbalanced상태면 rotate함- rotating은 상수시간 걸림.
* 최악의 경우, deletion은 rotating을 여러번 해야해서 O(log n)이 걸림.


## B-Tree 

B tree 
