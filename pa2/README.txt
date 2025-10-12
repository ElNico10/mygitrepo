AVL tree implementation uses Olog(n) for read and write.
AVL trees maintain Olog(n) by performing rotations to keep the tree at a manageable height, which means keeping Olog(n).
Their performance is different depending on what you are trying to do. AVL trees have faster lookup times as they are balanced actively, while std::maps are faster at inserting as they don't rotate afterward. The reliability is what matters, since std::maps are tried and true, while the custom implementation of AVL trees can result in bugs. They do somewhat maintain the same Olog(n) time complexity though.
