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
* Heap sort --> root를 pop하고 heapify 를 반복 . O (n log n )
* Priority Queue
* Graph algorithms such as shortest-paths


## Binary Search Tree

BST

## AVL Tree

AVL

## B-Tree 

B tree 
