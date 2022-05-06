#include "syntaxtree.hpp"
#pragma once
//Use Singleton Design pattern
class privateHeap
{
public:
  ~privateHeap();
  static privateHeap* get_Heap(void);
  void* allocate(std::size_t sizeOfMemory);
  bool deallocate(void* memoryToDeallocate);
  void clear_heap();
  void dump_heap();
private:
  privateHeap();
  static void* operator new(std::size_t size);
  struct memory_block
  {
    struct memory_block *next;
    size_t size;
    bool is_free;
  };
  memory_block *NodeRoot;
  memory_block *VariableRoot;
  syntaxNode *NodeHeapEnd;
  Variable *VariableHeapEnd;
  std::unordered_map<syntaxNode*> _syntaxNodeStore;
  std::unordered_map<Variable*> _variableStore;
}
